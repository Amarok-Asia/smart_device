#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
 
const char* ssid = "amarock";
const char* password = "123a123b";
int randnum = 12;
int cr = 979869;






void setup () {
 
Serial.begin(115200);
WiFi.begin(ssid, password);


 
while (WiFi.status() != WL_CONNECTED) {
 
delay(1000);
Serial.println("Connecting..");
 
}
 
}
void getrequest(){
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
  Serial.println("Connected..");
  HTTPClient http;  //Declare an object of class HTTPClient
 
  http.begin("http://class-card-marking-system-api.herokuapp.com/api/posts");  //Specify request destination
  int httpCode = http.GET();                                                   //Send the request
 
  if (httpCode > 0) { //Check the returning code
 
  String payload = http.getString();   //Get the request response payload
  Serial.println(payload);            //Print the response payload
 
  }

  else{
    Serial.print("http code is: " + httpCode);
  }
 
  http.end();   //Close connection
 
  }
 
  delay(30000);    //Send a request every 30 seconds
  
  }

 
void loop() {
  
if(randnum < 10){
  Serial.println(randnum);
   getrequest();
}
else{
  Serial.println(randnum);
  postrequest();
}
 
 
}
void postrequest(){
 
   Serial.println("posting request");
   if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
 
   HTTPClient http;    //Declare object of class HTTPClient
   cr+=1;
   String C = String(cr);

   

 
   http.begin("http://class-card-marking-system-api.herokuapp.com/api/posts");   //Specify request destination
   http.addHeader("Content-Type", "application/json");
   int httpCode = http.POST("{\"title\":\"Index: "+C+"\",\"body\":\"Welcome....!\"}");
  
   String payload = http.getString();//Get the response payload
 
   Serial.println(httpCode);   //Print HTTP return code
   Serial.println(payload);    //Print request response payload
 
   http.end();  //Close connection
 
 }else{
 
    Serial.println("Error in WiFi connection");   
 
 }
 
  delay(3000);  //Send a request every 3 seconds
 
}

 
