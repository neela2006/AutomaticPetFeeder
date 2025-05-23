#include <Wire.h>
#include <RTClib.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

RTC_DS3231 rtc;
Servo feederServo;
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
    feederServo.attach(11);  // Servo connected to pin 9
    lcd.begin(20,4);
    lcd.backlight();
    
    Serial.begin(9600);
    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
        while (1);
    }
    
    lcd.setCursor(0, 0);
    lcd.print("Automated Pet Feeder");
    lcd.setCursor(0, 1);
    lcd.print("System Initializing...");
    delay(2000);
    lcd.clear();
}

void loop() {
    DateTime now = rtc.now();  // Get current time

    // Display time on LCD
    lcd.setCursor(0, 0);
    lcd.print("Time: ");
    lcd.print(now.hour());
    lcd.print(":");
    lcd.print(now.minute());
    
    
    if (now.hour() == 8 && now.minute() == 30) {
        lcd.setCursor(0, 1);
        lcd.print("Next Feed: 1:30 PM");
        feed();
    }
    if (now.hour() == 13 && now.minute() == 00) {
        lcd.setCursor(0, 1);
        lcd.print("Next Feed: 8:00 PM");
        feed();
    }
    if (now.hour() == 19 && now.minute() == 37) {
        feed();
        lcd.setCursor(0, 1);
        lcd.print("Next Feed: 8:30 AM");
    }
    delay(1000);
}

void feed() {
  lcd.setCursor(0, 2);
    lcd.print("Feeding in progress...");
    Serial.println("Feeding time!");

    feederServo.write(90);
    delay(3000);
    feederServo.write(0);
    
    lcd.setCursor(0, 3);
    lcd.print("Food Dispensed!");

}
