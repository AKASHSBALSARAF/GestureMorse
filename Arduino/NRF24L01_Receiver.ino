#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 10); // NRF24L01 CE and CSN pins

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    char receivedMessage[32]; // Buffer to store received data
    radio.read(&receivedMessage, sizeof(receivedMessage));
    Serial.print("Message: ");
    Serial.println(receivedMessage); // Print the received message
  }
}
