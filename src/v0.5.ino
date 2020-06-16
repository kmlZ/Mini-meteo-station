
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BME280.h>
#include <LowPower.h>


#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET     -1 

#define LED_PIN 9
#define BLINK
#define SLEEPTIME 60 // in seconds, divisible by 8


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_BME280 bme;


 float temp;
 float pres;
 float humid;
 const int c = 10;
 

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  Serial.begin(9600);
if (!bme.begin(0x76)) {
  Serial.println("Could not find a valid BME280 sensor, check wiring!");
  while (1) {}
  
  }
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }

  display.clearDisplay();
  display.setTextSize(1);   
  display.setTextColor(WHITE, BLACK); 
  display.setCursor(25, 20);            
  display.println("BME280 SENSOR");
  display.setCursor(12, 30);
  display.println("Mini Meteo Station");
  display.setCursor(17,40);
  display.println("by Kamil Hamerlak");
  display.setCursor(90,50);
  display.println("v0.5");
  display.display();     


  delay(5000);
  display.clearDisplay();
  display.setTextSize(1); 
  display.setTextColor(WHITE, BLACK); 
  display.ssd1306_command(SSD1306_SETCONTRAST); 
  display.ssd1306_command(c);

  
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

void sleepmode(){
  for(int i=0;i<SLEEPTIME/8;i++){
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
}

void loop() {
  
  unsigned long currentMillis = millis();
  #ifdef BLINK
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  #endif
  temp = bme.readTemperature();
  pres = (bme.readPressure() /100);
  humid = bme.readHumidity();

  Serial.print("Temperatura: ");
  Serial.println(temp);
  Serial.print("Cisnienie: ");
  Serial.println(pres);
  Serial.print("Wilgotność: ");
  Serial.println(humid);

 

  displayMeasurment();
  sleepmode();
}

void displayMeasurment(){

display.clearDisplay();
display.setCursor(1, 1);
display.println("Temperatura: ");
display.setCursor(1, 11);
display.print(temp);
display.print((char)247);
display.println("C");
display.setCursor(1, 22);
display.println("Cisnienie: ");
display.setCursor(1, 32);
display.print(pres);
display.println(" hPa");
display.setCursor(1, 43);
display.println("Wilgotnosc: ");
display.setCursor(1, 54);
display.print(humid);
display.println(" %");
display.display();

}

 

