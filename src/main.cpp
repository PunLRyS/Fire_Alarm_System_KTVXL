#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>

const int rs = PA0, en = PA1, d4 = PA2, d5 = PA3, d6 = PA4, d7 = PA5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int ledPin = PB0;
const int buzzerPin = PB1;
const int buttonIncreasePin = PA6;
const int buttonDecreasePin = PA7;

int temperature = 45;
String statusMessage = "Running...";
int messagePosition = 0;

void increaseTemperature() {
    temperature++;
}

void decreaseTemperature() {
    temperature--;
}

void setup() {
    lcd.begin(16, 2);
    
    pinMode(ledPin, OUTPUT); 
    
    pinMode(buzzerPin, OUTPUT); 

    pinMode(buttonIncreasePin, INPUT_PULLUP);

    pinMode(buttonDecreasePin, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(buttonIncreasePin), increaseTemperature, FALLING);
    attachInterrupt(digitalPinToInterrupt(buttonDecreasePin), decreaseTemperature, FALLING);
}

void loop() {

    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print(" C");
    
    lcd.setCursor(6, 0); 
    lcd.print(temperature);
    lcd.print(" C");
    if (temperature > 50) {
        lcd.setCursor(0, 1);
        lcd.print("High Temp           ");
        digitalWrite(ledPin, HIGH);
        digitalWrite(buzzerPin, HIGH);
        delay(500); 
        digitalWrite(ledPin, LOW);
        digitalWrite(buzzerPin, LOW);
        delay(500);
    } else {
        lcd.setCursor(0, 1);
        for (int i = 0; i < 16; i++) {
            int charIndex = (messagePosition + i) % statusMessage.length();
            lcd.print(statusMessage[charIndex]);
        }
        messagePosition++;
        if (messagePosition >= statusMessage.length()) {
            messagePosition = 0;
        }
        digitalWrite(ledPin, LOW);
        digitalWrite(buzzerPin, LOW);
    }
    delay(500);
}