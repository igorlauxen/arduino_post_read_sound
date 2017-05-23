#include <Bridge.h>
#include <Process.h>

//services setups     
String INUMBER_TRIAL = "i841640"; 
String DEVICE_ID = "32b9f043-8569-464e-8bc4-95c567d98d00";
String MESSAGE_TYPE = "e0a6c3bab615e97310f0";
String URL_TO_SERVICE = "";
String USER_AUTHENTICATION = "Bearer YOUR_DEVICE_TOKEN";

// The SAP proxy is handled in the file /etc/profile
//export http_proxy=http://proxy.wdf.sap.corp:8080
//export https_proxy=http://proxy.wdf.sap.corp:8080 

String createCurlCommand (String url, String authentication, String messageType) {
    
  String curlCmd = "curl ";
  //header parameters
  curlCmd += "--insecure -H  \"Authorization: "+ authentication +"\" ";
  curlCmd += "-H  \"Content-Type: application/json\" ";
  //type of request
  curlCmd += " -X POST ";
  //body parameters 
  curlCmd += "-d '{";
  curlCmd += " \"mode\": \"async\"";
  //close -d
  curlCmd += "}' ";
  //backend url
  curlCmd += url;
  return curlCmd;
}

void post(){
  String curlCmd = createCurlCommand( URL_TO_SERVICE, USER_AUTHENTICATION, MESSAGE_TYPE );
  Serial.println("Curl Cmd Command being saved: ");
  Serial.println(curlCmd);
  Process process;
  process.runShellCommandAsynchronously(curlCmd);
  while (process.running());
}

void setup(){
  Bridge.begin();
  while(!Serial);
  Serial.println("Starting...");
}

/*
RED = 3.3V
BLACK = GND
BLUE = A0 (Analog 0 entry)
*/

void loop(){
  double value = analogRead(0);
  Serial.println(value);
  URL_TO_SERVICE = "https://iotmms"+INUMBER_TRIAL+"trial.hanatrial.ondemand.com/com.sap.iotservices.mms/v1/api/http/data/"+DEVICE_ID+"/"+MESSAGE_TYPE+"?test="+value;
  post();
}
