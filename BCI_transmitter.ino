#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); 
const byte address[6] = "00001";
int relay = 9;

bool isRaining = false; 

unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 1000;    

void setup() {
  pinMode(relay, OUTPUT);
  Serial.begin(115200);

  radio.begin();
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening(); 
}

void loop() {
  if (radio.available()) {
  
    float rainValue;
    radio.read(&rainValue, sizeof(rainValue));

    Serial.print("Received Rain Value: ");
    Serial.println(rainValue);
    delay(500);

    if (rainValue > 500.00) {
      isRaining = true;
    } else {
      isRaining = false;
      delay(3000);
    }

    if (isRaining && millis() - lastDebounceTime > debounceDelay) {
      digitalWrite(relay, LOW); 
      lastDebounceTime = millis();  
    } else if (!isRaining && millis() - lastDebounceTime > debounceDelay) {
      digitalWrite(relay, HIGH); 
      lastDebounceTime = millis();  
    }
  }
}
