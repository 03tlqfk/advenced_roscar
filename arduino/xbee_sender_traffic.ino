#include <SoftwareSerial.h> 
#define Rx    6                // DOUT to pin 6
#define Tx    7                // DIN to pin 7
SoftwareSerial Xbee (Rx, Tx);

void setup(){
  Serial.begin(57600);
  Xbee.begin(57600);
}

void loop(){
  Xbee.print("TRAFFIC");
  Serial.print("TRAFFIC");
  delay(600);
}
