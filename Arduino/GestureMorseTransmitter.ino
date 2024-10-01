#include <SPI.h>
#include <RF24.h>

const int dotPin = A0;  // Potentiometer for dot input
const int dashPin = A1; // Potentiometer for dash input
const int spacePin = A2; // Potentiometer for space input

RF24 radio(9, 10); // NRF24L01 CE and CSN pins

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  int dotValue = analogRead(dotPin);
  int dashValue = analogRead(dashPin);
  int spaceValue = analogRead(spacePin);
  
  // Threshold for dot, dash, and space
  if (dotValue > 800) {
    const char text[] = ".";
    radio.write(&text, sizeof(text));
    Serial.println("Dot sent");
  }
  else if (dashValue > 800) {
    const char text[] = "-";
    radio.write(&text, sizeof(text));
    Serial.println("Dash sent");
  }
  else if (spaceValue > 800) {
    const char text[] = " ";
    radio.write(&text, sizeof(text));
    Serial.println("Space sent");
  }
  
  delay(500); // Delay to avoid multiple signals in quick succession
}
