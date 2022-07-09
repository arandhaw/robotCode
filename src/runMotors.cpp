#include <wire.h>
#include <Adafruit_SSD1306.h>
#include "runMotors.h"
#include <Motor.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET   -1 // This display does not have a reset pin accessible
#define AOUT_PIN_1 PA1   // analog out pin for PWM
#define AOUT_PIN_1_PWM PA_1 // analog out pin for PWM (same pin but different
                        	// data type - this is confusing!)
#define AOUT_PIN_2 PA2   // analog out pin for PWM
#define AOUT_PIN_2_PWM PA_2 // analog out pin for PWM (same pin but different
                        	// data type - this is confusing!)                          

Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Variable to store the value of the analog in pin.
// volatile uint16_t value = 0; //ADC is 12bit
volatile int j = 0; 

void setup_OLED() {
  display_handler.begin(SSD1306_SWITCHCAPVCC, 0x3C);
 
  // Displays Adafruit logo by default. call clearDisplay immediately if you don't want this.
  display_handler.display();
  delay(2000);

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
void OLED(int dutycycle) {
    
    display_handler.clearDisplay();
    display_handler.setCursor(0,0); //sets location of cursor (x, y)
    display_handler.println("Loop Counter: ");
    display_handler.println(j);
    display_handler.println("Duty cycle:");
    display_handler.println(dutycycle);
    display_handler.display();
    j++;
    delay(10);
}

Motor motor1(PA0, PA_0, PA1, PA_1);
Motor motor2(PA2, PA_2, PA3, PA_3);
bool dir;
int dutycycle = 50;

//setup function - run once
void setup_runMotors(){
  bool dir = true;
  setup_OLED();
  motor1.powerMotor(dutycycle, dir);
  motor2.powerMotor(dutycycle, dir);
}

//loop function - run in master loop
void loop_runMotors(){
  OLED(dutycycle);
  motor1.powerMotor(45, dir);
  motor2.powerMotor(45, !dir);
  delay(2000);
  //motor1.powerMotor(50, dir);
  //motor2.powerMotor(50, dir);
  //OLED(50);
  motor1.powerMotor(45, dir);
  motor2.powerMotor(45, !dir);
  delay(2000);
}
