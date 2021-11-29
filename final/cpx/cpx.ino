

#include <Adafruit_CircuitPlayground.h>


#include <FastLED.h>       
#define LED_PIN1    A6      
#define NUM_LEDS1   143    
CRGB leds1[NUM_LEDS1];     
uint8_t max_bright=155; 
float X, Y, Z;


// mess with this number to adjust TWINklitude :)
// lower number = more sensitive
#define MOVE_THRESHOLD 10
static bool flag = true;


void setup() {

  Serial.begin(9600);
  CircuitPlayground.begin();
  FastLED.addLeds<WS2812, LED_PIN1, GRB>(leds1, NUM_LEDS1);
  FastLED.setBrightness(max_bright);
}

void loop() {
  
  //CircuitPlayground.clearPixels();
  X = CircuitPlayground.motionX();
  Y = CircuitPlayground.motionY();
  Z = CircuitPlayground.motionZ();
 
   // Get the magnitude (length) of the 3 axis vector
  // http://en.wikipedia.org/wiki/Euclidean_vector#Length
  double storedVector = X*X;
  storedVector += Y*Y;
  storedVector += Z*Z;
  storedVector = sqrt(storedVector);
  Serial.print("Len: "); Serial.println(storedVector);
  
  // wait a bit
  delay(100);
  
  // get new data!
  X = CircuitPlayground.motionX();
  Y = CircuitPlayground.motionY();
  Z = CircuitPlayground.motionZ();
  double newVector = X*X;
  newVector += Y*Y;
  newVector += Z*Z;
  newVector = sqrt(newVector);
  Serial.print("New Len: "); Serial.println(newVector);
  
  // are we moving 
  if (abs(10*newVector - 10*storedVector) > MOVE_THRESHOLD && flag==true) {
    Serial.println("Twinkle!");
    for(int x=0;x<=255;x++)
      {
          for(int i=0;i<143;i++)  
          {
             leds1[i] = CRGB (x,x,x);
          }
         FastLED.show(); 
         delay(5);
     }
     flag = false;  
  }
  else if(flag == false){
    Serial.println("off!");
     for(int x=255;x>=0;x--)
      {
          for(int i=0;i<143;i++)     
          {
              leds1[i] = CRGB (x,x,x);
          }
          FastLED.show(); 
          
      }   
      flag = true;    
  }
  
}
