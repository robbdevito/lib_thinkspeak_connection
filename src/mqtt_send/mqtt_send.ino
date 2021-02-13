#include <ESP8266WiFi.h>
 
String apiKey = "V3VYXB1ADM9360A5";     //  Enter your Write API key from ThingSpeak

const char* ssid =  "ELIL-1860";     // replace with your wifi ssid and wpa2 key
const char* password =  "976764542267995454467053270947";
const char* server = "api.thingspeak.com";

WiFiClient client;


void setup() {

/*WIFI connection set --> Can be replaced with LIB*/  
  WiFi.mode(WIFI_STA);    //disconnect all WIFI connections
  WiFi.disconnect();
  delay(100);

  Serial.begin(115200);   //beginn communication with Baudrate 115200
  delay(10);

  Serial.println();
  Serial.println("Connecting to following network:");
  Serial.println(ssid);

/* Start WiFi connection, for not established connection print ...
   after successfully connecting to WiFi, print success Message 
   and IP of ESP module*/
   
  WiFi.begin(ssid, password);       
  while (WiFi.status() != WL_CONNECTED) {
    delay(1500);
    Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi Connection successful"); 
    Serial.print("IP of own ESP-Module: ");
    Serial.println(WiFi.localIP());
/*End of WIFI connection process*/

}

void loop() {

   float h = 15.0;
   float t = 20.0;
      

if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
{
  String postStr = apiKey;
  postStr +="&field1=";
  postStr += String(t);
  postStr +="&field2=";
  postStr += String(h);
  postStr += "\r\n\r\n";
  
  client.print("POST /update HTTP/1.1\n");
  client.print("Host: api.thingspeak.com\n");
  client.print("Connection: close\n");
  client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
  client.print("Content-Type: application/x-www-form-urlencoded\n");
  client.print("Content-Length: ");
  client.print(postStr.length());
  client.print("\n\n");
  client.print(postStr);
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" degrees Celcius, Humidity: ");
  Serial.print(h);
  Serial.println("%. Send to Thingspeak.");
}
client.stop();

Serial.println("Waiting...");

delay(30000);
}
