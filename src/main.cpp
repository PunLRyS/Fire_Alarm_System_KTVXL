#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>

const int rs = PA0, en = PA1, d4 = PA2, d5 = PA3, d6 = PA4, d7 = PA5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int ledPin = PB0;
const int buzzerPin = PB1;

void setup() {
    lcd.begin(16, 2);
    
    pinMode(ledPin, OUTPUT); 
    
    pinMode(buzzerPin, OUTPUT); 
}

void loop() {

    int temperature = 70;

    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print(" C");
    
    lcd.setCursor(6, 0); 
    lcd.print(temperature);
    lcd.print(" C");
    if (temperature > 50) {
        lcd.setCursor(0, 1);
        lcd.print("High Temp");
        digitalWrite(ledPin, HIGH);
        digitalWrite(buzzerPin, HIGH);
        delay(1000); 
        digitalWrite(ledPin, LOW);
        digitalWrite(buzzerPin, LOW);
        delay(1000);
    } else {
        digitalWrite(ledPin, LOW);
        digitalWrite(buzzerPin, LOW);
    }

    delay(1000);
}