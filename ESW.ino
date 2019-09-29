#include <ArduinoWebsockets.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#define SSID "esw"
#define PASS "esw1234"
#define HOST "esw5009.p-e.kr"
uint16_t port = 5009;
int busCode = 1;
int button = 9;
int led = 13;
SoftwareSerial serial(2,3);
using namespace websockets;
WebsocketsClient client;
bool connected = false;
void setup() {

 pinMode(button,INPUT_PULLUP);
 pinMode(led,OUTPUT);
 initialize();
}
void initialize(){
  Serial.begin(9600);
  WiFi.begin(SSID,PASS);
  while(WiFi.status() != WL_CONNECTED)

  connected = client.connect(HOST,port,"/");
  client.onMessage([&](WebsocketsMessage msg){
    String cmd = msg.data();
    if(cmd.equals("RESET_BUTTON")){
        digitalWrite(led,HIGH);
    }
    
  });
}

void loop() {
  if(client.available()){
    client.poll();
  }
  if(digitalRead(button) == LOW){
  if(connected){
    String cmd = "REG_BUTTON";
      client.send(cmd);}
  }
  delay(3000);
}
