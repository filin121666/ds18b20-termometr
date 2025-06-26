#include <LiquidCrystal_I2C.h>

#include <GyverDS18.h>
#include <GyverDS18Array.h>
#include <GyverDS18Single.h>

#include <stdint.h>

#define DS18B20_PIN 6
// LCD:  SDA – A4, SCL – A5

LiquidCrystal_I2C lcd(0x27, 16, 2);
GyverDS18Single ds(DS18B20_PIN);
char temp[7] = {' ', ' ', ' ', ' ', ' ', ' ', 0};

void setup() {
    lcd.init();
    lcd.backlight();
    lcd.setCursor(2, 0);
    lcd.print("Temperature");
    lcd.setCursor(0, 1);

    ds.setResolution(11);
    ds.requestTemp();
}

void loop() {
    if (ds.ready()) {
        if (ds.readTemp()) {
            dtostrf((double) ds.getTemp(), 6, 2, temp);
            lcd.setCursor(0, 1);
            lcd.print("          ");
            lcd.write(223);
            lcd.print("C    ");
            lcd.setCursor(4, 1);
            lcd.print(temp);
        } else {
            lcd.print("     Error     ");
        }
        ds.requestTemp();
    }
}
