#include "OLED.h"
#include <wire.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET   -1 // This display does not have a reset pin accessible                       

// Variable to store the value of the analog in pin.
// volatile uint16_t value = 0; //ADC is 12bit
volatile int OLEDcounter = 0; 
Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup_OLED() {
  
  Wire.setSCL(PB10);
  Wire.setSDA(PB11);
  display_handler.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // Displays Adafruit logo by default. call clearDisplay immediately if you don't want this.
  display_handler.display();

  // Displays "Hello world!" on the screen
  display_handler.clearDisplay();
  display_handler.setTextSize(1);
  display_handler.setTextColor(SSD1306_WHITE);
  display_handler.setCursor(0,0);
  display_handler.println("Hello World!!!");
  display_handler.display();
  delay(1000);
}

//updates OLED once
void OLED(String str, int num) {
    
    display_handler.clearDisplay();
    display_handler.setCursor(0,0); //sets location of cursor (x, y)
    display_handler.println("Loop Counter: ");
    display_handler.println(OLEDcounter);
    display_handler.println(str);
    display_handler.println(num);
    display_handler.display();
    OLEDcounter++;
}
//updates OLED once
void OLED2(String str, int a, int b) {
    
    display_handler.clearDisplay();
    display_handler.setCursor(0,0); //sets location of cursor (x, y)
    display_handler.println(str);
    display_handler.println(a);
    display_handler.println(b);
    display_handler.display();
    OLEDcounter++;
}

//updates OLED once
void OLED_manual(int a, int b, int c, int d) {
    
    display_handler.clearDisplay();
    display_handler.setCursor(0,0); //sets location of cursor (x, y)
    display_handler.println("Encoder 1 pos");
    display_handler.println(a);
    display_handler.println("Encoder 1 count");
    display_handler.println(b);
    display_handler.println("Encoder 2 pos");
    display_handler.println(c);
    display_handler.println("Encoder 2 count");
    display_handler.println(d);
    display_handler.display();
    OLEDcounter++;
}

//updates OLED once
void OLED_manual2(int a, int b, int c) {
    
    display_handler.clearDisplay();
    display_handler.setCursor(0,0); //sets location of cursor (x, y)
    display_handler.println("Loop Counter: ");
    display_handler.println(OLEDcounter);
    display_handler.println("left to right:");
    display_handler.println(a);
    display_handler.println(b);
    display_handler.println(c);
    display_handler.display();
    OLEDcounter++;
}

//updates OLED once
void OLED_manual3(float a, float b, float c) {
    
    display_handler.clearDisplay();
    display_handler.setCursor(0,0); //sets location of cursor (x, y)
    display_handler.println(a);
    display_handler.println(b);
    display_handler.println(c);
    display_handler.display();
    OLEDcounter++;
}
