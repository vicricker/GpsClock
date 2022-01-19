/**
 * Simple clock using GPS and 20x4 I2C LCD display
 */

#include <TimeLib.h>
#include <Timezone.h>
#include <TinyGPS++.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include "font.h"

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);
TinyGPSPlus gps;
SoftwareSerial ss(4, 3);

TimeChangeRule usEDT = { "EDT", Second, Sun, Mar, 2, -240 };  //UTC - 4 hours
TimeChangeRule usEST = { "EST", First, Sun, Nov, 2, -300 };   //UTC - 5 hours
Timezone usEastern(usEDT, usEST);

boolean useMilitaryTime = false;

/**
 * Draw a big digit to the display
 */
void drawDigit(const int h, const int c) {
  const uint8_t *d PROGMEM = digit[c];

  for (int v = 0; v < 3; v++) {
    lcd.setCursor(h, v);
    lcd.write(pgm_read_byte(d++));
    lcd.write(pgm_read_byte(d++));
    lcd.write(pgm_read_byte(d++));
  }
}

/**
 * Draw a 2 digit integer in big digits
 */
void drawDigits(const int h, const int number) {
  drawDigit(h, (number / 10) % 10);
  drawDigit(h+3, number % 10);
}

uint8_t lastDay = -1;

void drawDate(time_t n) {
  uint8_t m = month(n);
  uint8_t d = day(n);
  short y = year(n);

  if (d != lastDay) {
    lastDay = d;

    lcd.setCursor(0, 3);
    for (int i = 0; i < 20; i++) {
      lcd.write(' ');
    }

    lcd.setCursor(0, 3);
    lcd.print(dayStr(weekday(n)));
    lcd.write(' ');
    lcd.print(m);
    lcd.write('/');
    lcd.print(d);
    lcd.write('/');
    lcd.print(y);
  }
}

uint8_t lastHour = -1, lastMinute = -1, lastSecond = -1;

/**
 * Draw the time in big digits, only updating the components that have changed.
 */
void drawTime(time_t n) {
  uint8_t h = hour(n);
  uint8_t m = minute(n);
  uint8_t s = second(n);

  if (!useMilitaryTime && h > 12) {
    h -= 12;
  }

  if (s != lastSecond) {
    drawDigits(14, s);

    if (m != lastMinute) {
      lastMinute = m;
      drawDigits(7, m);

      if (h != lastHour) {
        lastHour = h;
        drawDigits(0, h);
      }
    }
  }
}


uint8_t ls = 60;
void loop() {
  handleGps();

  uint8_t sec = gps.time.second();

  if (sec != ls) {
    ls = sec;

    setTime(gps.time.hour(), gps.time.minute(), sec, gps.date.day(), gps.date.month(), gps.date.year());

    if (timeStatus() == timeSet) {
      time_t localTime = usEastern.toLocal(now());

      drawTime(localTime);
      drawDate(localTime);
    }
  }
}

static void handleGps() {
  while (ss.available()) {
    gps.encode(ss.read());
  }
}

/**
 * Create a custom character from PROGMEM to the LCD
 */
void createChar(const int n, const uint8_t *data) {
  uint8_t ram[8];

  memcpy_P(ram, data, 8);

  lcd.createChar(n, ram);
}

/**
 * Init the LCD, send the custom characters, etc.
 */
void setupLcd() {
  lcd.init();
  lcd.clear();
  lcd.backlight();

  createChar(0, NWW);
  createChar(1, HORIZ);
  createChar(2, NE);
  createChar(3, VERT);
  createChar(4, T_LEFT);
  createChar(5, T_RIGHT);
  createChar(6, SW);
  createChar(7, SX);

  lcd.setCursor(6, 1);
  lcd.write(':');
  lcd.setCursor(13, 1);
  lcd.write(':');

  lcd.setCursor(0, 3);
  lcd.print("Acquiring satellites");
}

void setup() {
  Serial.begin(115200);
  ss.begin(9600);

  setupLcd();
}
