#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); 
const byte address[6] = "00001";

#define ALPHA 0.1 
int sensorPin = A0;
float smoothedValue = 0;
int y = smoothedValue;
int trig = 0;
int x = 630;

void setup() {
  pinMode(sensorPin, INPUT);
  Serial.begin(115200);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening(); 
}

void loop() {

  int a = analogRead(sensorPin);
  int b = analogRead(sensorPin);
  int c = analogRead(sensorPin);
  int d = analogRead(sensorPin);
  int e = analogRead(sensorPin);
  int f = analogRead(sensorPin);
  int g = analogRead(sensorPin);
  int h = analogRead(sensorPin);
  int i = analogRead(sensorPin);
  int j = analogRead(sensorPin);
  int sensorValue = (a+b+c+d+e+f+g+h+i+j)/10;
  
  smoothedValue = ALPHA * sensorValue + (1 - ALPHA) * smoothedValue;
 
  
  byte smoothedBytes[sizeof(smoothedValue)];
  memcpy(smoothedBytes, &smoothedValue, sizeof(smoothedValue));

  radio.write(&smoothedBytes, sizeof(smoothedBytes));
  Serial.println(smoothedValue);
  delay(200);

}
