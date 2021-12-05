#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    A6

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 143

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

#include <Adafruit_CircuitPlayground.h>
float X, Y, Z, X1, MovementX, Y1, MovementY, Z1, MovementZ;
int timer;


#include <FastLED.h>
#define LED_PIN1    A6
#define NUM_LEDS1   143
CRGB leds1[NUM_LEDS1];
uint8_t max_bright = 255;

static bool flag = false;
bool condition = false;

void setup()
{

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  Serial.begin(9600);
  CircuitPlayground.begin();
  FastLED.addLeds<WS2812, LED_PIN1, GRB>(leds1, NUM_LEDS1);
  FastLED.setBrightness(max_bright);
}

void loop()
{

  X = CircuitPlayground.motionX();
  Y = CircuitPlayground.motionY();
  Z = CircuitPlayground.motionZ();

  X1 = CircuitPlayground.motionX();
  MovementX = X1 - X;

  Y1 = CircuitPlayground.motionY();
  MovementY = Y1 - Y;

  Z1 = CircuitPlayground.motionZ();
  MovementZ = Z1 - Z;

  if ((MovementX > 1 || MovementX < -1) && (condition == true)) {
    Serial.print("WALK");

    theaterChase(strip.Color(127, 127, 127), 50);
    strip.clear();

    timer = 0;
  } else if ((MovementZ > 1) && condition == false) {
    Serial.print("PICK UP");
    condition = true;
    colorWipe(strip.Color(  0,   0, 255), 5); // Blue
    strip.clear();
    delay(50);
    timer = 0;


  } else if (MovementX < 0.5 && MovementX > -0.5 && MovementY < 0.5 
  && MovementY > -0.5 && MovementZ < 0.5 && MovementZ > -0.5 && condition == true) {

    timer ++;
    Serial.print("sit");
    Serial.print(timer);
    if (timer >= 100) {
      condition = false;
      timer = 0;
      for (int i = 0; i < 143; i++)
      {
        leds1[i] = CRGB::Black;
      }
      FastLED.show();
      strip.show();

    } else {
      for (int i = 0; i < 143; i++)
      {
        leds1[i] = CRGB::Black;
      }
      FastLED.show();
      strip.show();

    }

  }


  Serial.print("X: ");
  Serial.print(MovementX);
  //Serial.print("X1: ");
  //Serial.print(X1);
  Serial.print("  Y: ");
  Serial.print(MovementY);
  Serial.print("  Z: ");
  Serial.println(MovementZ);

  delay(50);
}


void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for (int a = 0; a < 10; a++) { // Repeat 10 times...
    for (int b = 0; b < 3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for (int c = b; c < strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}
