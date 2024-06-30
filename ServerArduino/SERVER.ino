#include <SPI.h>
#include <RH_RF95.h>

RH_RF95 rf95;
bool first = true;

int led = 13;

void setup() {
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
}

void loop() {
  Serial.println("Ready to receive");

  while(!rf95.available());

  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
  if (rf95.recv(buf, &len)) {
    if (first == true) {
      Serial.print("Received sync request: ");
      Serial.println((char*)buf);
      first = false;
    } else {
      Serial.print("Received request: ");
      Serial.println((char*)buf);
    }

    uint8_t data[] = "ACK";
    rf95.send(data, sizeof(data));
    rf95.waitPacketSent();
    Serial.println("Sent a reply");
  }

  delay(10000);
}
