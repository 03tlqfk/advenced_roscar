#include <ros.h>
#include <std_msgs/Int32.h>
#include <SoftwareSerial.h> 
#define Rx    6                // DOUT to pin 6
#define Tx    7                // DIN to pin 7
SoftwareSerial Xbee (Rx, Tx);

ros::NodeHandle nh;
std_msgs::Int32 x_rssi;
std_msgs::Int32 x_rssi_car;
ros::Publisher p1("x_rssi", &x_rssi);
ros::Publisher p2("x_rssi_car", &x_rssi_car);

void setup() {
  Serial.begin(57600);
  Serial.flush();
  Xbee.begin(57600);
  nh.initNode();
  nh.advertise(p1);
  nh.advertise(p2);
  delay(50);

}

byte rssi = 0x00;
byte data = 0x00;
void loop() {
  if (Xbee.available()) {
    byte in = Xbee.read();
    
    if (in == (byte) 0x7E) {
      int i = 0;
      while (true) {
        if (Xbee.available()) {
          in = Xbee.read();
          if (i == 5)rssi = in;
          if (i == 7)data = in;
          Serial.print(in);
          Serial.print(" ");
          i++;

        }
        if (i > 13)break;
      }
      //84:TRAFFIC 1 
      //67:CAR 2
      Serial.print("/ ");
      Serial.print("data:");
      Serial.print(data);
      Serial.print(" RSSI:");
      Serial.print(rssi);
      Serial.println(" ");
      if(data == 84)
      {
        x_rssi.data = (int)rssi;
        p1.publish(&x_rssi);
        nh.spinOnce();
        delay(10);
      }
      else if(data == 67)
      {
        x_rssi_car.data = (int)rssi;
        p2.publish(&x_rssi_car);
        nh.spinOnce();
        delay(10);
      }
      
    }
  }
  
}
