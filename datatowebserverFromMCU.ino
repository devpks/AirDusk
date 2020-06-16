//PagerDuty Hackathon 2020

int inputPin = 5; // Input pin which will be used for Industrial parameter recording sensors(for Infrared sensor) 
int val = 0; // variable for reading the pin status
//libraries
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "Workstation";  //personal note to self - never use " or ' in ssid
const char *password = "*****"; //

//Web/Server address to read/write from 
const char *host = "https://pagerduty.com";  
#define LED D0 

//=======================================================================
//                    Power on setup
//=======================================================================

void setup() {
  pinMode(LED, OUTPUT);  
 pinMode(inputPin, INPUT);
pinMode(13,OUTPUT);
  
  delay(1000);
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);        
  delay(1000);
  WiFi.mode(WIFI_STA);        
  
  WiFi.begin(ssid, password);  
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

   Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  
pinMode(D0, OUTPUT);
}

//=======================================================================
//                    Main Program Loop
//=======================================================================
void loop() {
  digitalWrite(LED, HIGH);// turn the LED off.(Note that LOW is the voltage level but actually 
                        //the LED is on; this is because it is acive low on the ESP8266.
delay(1000);            // wait for 1 second.
digitalWrite(LED, LOW); // turn the LED on.
delay(1000); // wait for 1 second.
  val = digitalRead(inputPin); 
   if (val == HIGH) {

  Serial.print("DETECTED");
  HTTPClient http;   

  String ADCData, station, postData;
  int adcvalue=random(1,50); 
  ADCData = String(adcvalue);   
  station =random(1,10); //value to be sent
  int pks = random(1,10); // status of the string
  //Post Data post data
  postData = "entering=" + ADCData + "$leaving=" + station + "&occupancy=" + pks  ;
  
  http.begin("http://www.airdusk.com/postdemo.php");     //website URL         //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    

  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payloaddd
  digitalWrite(D0, HIGH);

  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload

  http.end();  //Close connection
  
    
  delay(5000);  //Post Data at every 5 second
  
  }

  else {
    Serial.print("NOT DETECTED");
    delay(1000);
    digitalWrite(13,HIGH);
    delay(1000);
    digitalWrite(13,LOW);
    digitalWrite(13,HIGH);
    delay(1000);
    digitalWrite(13,LOW);
    digitalWrite(13,HIGH);
    delay(1000);
    digitalWrite(13,LOW);
    digitalWrite(13,HIGH);
    delay(1000);
    digitalWrite(13,LOW);
    digitalWrite(13,HIGH);
    delay(1000);
    digitalWrite(13,LOW);
    
    
    }
  
}
//=======================================================================
