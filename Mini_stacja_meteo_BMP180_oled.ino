/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x32 pixel display using I2C to communicate
 3 pins are required to interface (two I2C and one reset).

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
 **************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BMP085.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_BMP085 bmp;

void setup() {
  Serial.begin(9600);
if (!bmp.begin(0x76)) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextSize(1);   
  display.setTextColor(WHITE, BLACK);  // set text color to white and black background
  display.setCursor(25, 20);            // move cursor to position (15, 0) pixel
  display.println("BMP180 SENSOR");
  display.setCursor(12, 30);
  display.println("Mini Meteo Station");
  display.setCursor(17,40);
  display.println("by Kamil Hamerlak");
  display.display();        // update the display




  delay(5000);
  display.clearDisplay();
  
}

void loop() {
  float temp;
  float pres;

  temp = bmp.readTemperature();
  pres = (bmp.readPressure() /100);

  Serial.print("Temperatura: ");
  Serial.println(temp);
  Serial.print("Cisnienie: ");
  Serial.println(pres);

  
display.clearDisplay();
display.setTextSize(1); 
display.setTextColor(WHITE, BLACK); 
display.setCursor(1, 1);
display.println("Temperatura: ");
display.setTextSize(2);
display.print(temp );
display.print((char)247);
display.println("C");
display.setCursor(1, 30);
display.setTextSize(1);
display.println("Cisnienie: ");
display.setTextSize(2);
display.print(pres);
display.println(" hPa");
display.display();
}
