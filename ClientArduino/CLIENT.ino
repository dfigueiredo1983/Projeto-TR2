#include <SPI.h>
#include <RH_RF95.h>

RH_RF95 rf95;

const int trigPin = 3;  
const int echoPin = 4; 
float duration, distance;

void setup() {
  pinMode(trigPin, OUTPUT);  
	pinMode(echoPin, INPUT);  

  Serial.begin(9600);
  while (!Serial);

  Serial.println();
  if (!rf95.init()) {
    Serial.println("LoRa initialization failed");
    while(1);
  } else {
    Serial.println("LoRa initialized successfully");
  }

  rf95.setTxPower(14, true); 

  delay(10000);

  Serial.println("Syncing...");
  uint8_t data[] = "SYN";
  rf95.send(data, sizeof(data));
  rf95.waitPacketSent();

  while (!rf95.available()){
    Serial.println("Trying to sync...");
  }
  Serial.println("Synced");

  delay(10000);
}

void loop() {
  digitalWrite(trigPin, LOW);  
	delayMicroseconds(2);  
	digitalWrite(trigPin, HIGH);  
	delayMicroseconds(10);  
	digitalWrite(trigPin, LOW);  

  duration = pulseIn(echoPin, HIGH);  
  distance = (duration*.0343)/2;

  Serial.println("Sending request...");

  String distanceStr = String(distance);
  uint8_t data[distanceStr.length() + 1];
  distanceStr.toCharArray((char *)data, distanceStr.length() + 1);

  rf95.send(data, sizeof(data));
  rf95.waitPacketSent();

  delay(15000); 
}
