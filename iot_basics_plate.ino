#include <Adafruit_BMP085.h>
#include <Wire.h>
#include <Arduino.h>

#define FAN_PWR_PIN 2
#define FAN_PWM 9
#define DB_SENSOR_PIN A0

Adafruit_BMP085 bmp;
float temp = 0;
float pres = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("T P SPEED DB");
  
  pinMode(FAN_PWR_PIN, OUTPUT);
  pinMode(FAN_PWM, OUTPUT);
  digitalWrite(FAN_PWR_PIN,false);
  
  delay(1000);
  digitalWrite(FAN_PWR_PIN, true);

  for (int i = 0; i <= 255; i++) {
    analogWrite(FAN_PWM, i);
    delay(10);
  }

  for (int i = 255; i >= 0; i--) {
    analogWrite(FAN_PWM, i);
    delay(10);
  }

  digitalWrite(FAN_PWR_PIN,false);

  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1) {//Have you tried explaning it to the rubber duck?}
    }
  }
}

void loop() {
  temp = bmp.readTemperature();
  pres = bmp.readPressure();
  
  Serial.print(temp);
  Serial.print(",");
  
  Serial.print(pres);
  Serial.print(",");
  
  if (temp < 27){
    digitalWrite(FAN_PWR_PIN, false);
    Serial.print(0);
  }
  
  if (temp >= 27 && temp < 30){
    digitalWrite(FAN_PWR_PIN, true);
    analogWrite(FAN_PWM, 50);
    Serial.print(50);
  }

  if (temp >= 30){
    analogWrite(FAN_PWM, 100);
    Serial.print(100);
  }

  long sum = 0;
  for(int i=0; i<32; i++)
  {
      sum += analogRead(DB_SENSOR_PIN);
  }

  sum >>= 5;
  Serial.print(",");
  Serial.print(sum);
  Serial.println();
  delay(1000);
}
