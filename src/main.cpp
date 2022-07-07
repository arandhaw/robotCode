#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // This display does not have a reset pin accessible
#define INTERRUPTPIN PA0
#define AOUT_PIN_1 PA1   // analog out pin for PWM
#define AOUT_PIN_1_PWM PA_1 // analog out pin for PWM (same pin but different
                        	// data type - this is confusing!)
#define AOUT_PIN_2 PA2   // analog out pin for PWM
#define AOUT_PIN_2_PWM PA_2 // analog out pin for PWM (same pin but different
                        	// data type - this is confusing!)                          

Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void handle_interrupt();
void handle_interrupt_schmitt();

// Variable to store the value of the analog in pin.
// volatile uint16_t value = 0; //ADC is 12bit
volatile int i = 0;
volatile int j = 0; 

class Motor {
  private:
    int forward_pin;
    int reverse_pin; 
    PinName forward_pin_;
    PinName reverse_pin_;

    //creates PWM wave at specified pin
    void PWM(int dutycycle, PinName pin){
      uint32_t frequency_Hz = 100000;
      pwm_start(pin, frequency_Hz, dutycycle,
      TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
    }

  public:
    Motor(int forward_pin, PinName forward_pin_, int reverse_pin, PinName reverse_pin_){
      this->forward_pin  = forward_pin;
      this->reverse_pin = reverse_pin;
      this->forward_pin_  = forward_pin_;
      this->reverse_pin_ = reverse_pin_;
      pinMode(forward_pin, OUTPUT); //specify that pins are analog out
      pinMode(reverse_pin, OUTPUT);
    }
    void powerMotor(int dutycycle, bool direction){
      if (direction == true){
        PWM(0, reverse_pin_);
        PWM(dutycycle, forward_pin_);
      }
      else{
        PWM(0, forward_pin_);
        PWM(dutycycle, reverse_pin_);
      }
    }
};

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
  display_handler.println("Hello!!!");
  display_handler.display();
  delay(1000);
  pinMode(INTERRUPTPIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INTERRUPTPIN),handle_interrupt, RISING);
}


void OLED(int dutycycle) {
    
    display_handler.clearDisplay();
    display_handler.setCursor(0,0); //sets location of cursor (x, y)
    display_handler.println("Hello World!");
    display_handler.println("Loop Counter: ");
    display_handler.println(j);
    display_handler.println("Duty cycle:");
    display_handler.println(dutycycle);
    display_handler.display();
    j++;
    delay(10);
}

Motor motor1(AOUT_PIN_1, AOUT_PIN_1_PWM, AOUT_PIN_2, AOUT_PIN_2_PWM);
bool dir;
int dutycycle = 30;

void handle_interrupt(){
  delay(2000);
  // dir = !dir;
}

void setup(){
  bool dir = true;
  setup_OLED();
  motor1.powerMotor(dutycycle, dir);
}

void loop(){
  motor1.powerMotor(dutycycle, dir);
  OLED(dutycycle);
}
