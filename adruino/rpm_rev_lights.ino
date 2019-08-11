#include <FastLED.h>

# define DATA_PIN 4
# define LED_TYPE WS2812
# define COLOR_ORDER GRB
# define NUM_LEDS 24
# define BRIGHTNESS 30

// Define the array of leds
CRGB leds[NUM_LEDS];

// Define Gradient (0-85 => green, 85-170 => blue, 170-255 => red)
DEFINE_GRADIENT_PALETTE( rpm_palatte) {
  0,   85,  170,  0,  // green
  85,   85,  170,  0,  // green
  85, 0, 0, 255,  // blue
  170, 0, 0, 255,  // blue
  170, 255,  0,  0, // red
  255, 255,  0,  0 }; // red

  // Initial Setup of Adruino
  void setup() {
    delay(3000);

    // Serial setup
    Serial.begin(9600);
    Serial.setTimeout(50);

    // FastLED setup
    FastLED.addLeds < LED_TYPE, DATA_PIN, COLOR_ORDER > (leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);

    // Turn off
    BlackoutStrip();
  }

  // Initialize variables
  int prevLedCount;
  String incoming;
  unsigned long previousMillis = 0;
  unsigned long currentMillis;
  CRGBPalette16 rpmColourPalette = rpm_palatte;

  void loop() {
  
    currentMillis = millis();

    // Turn off if no activity for 3s
    if (currentMillis - previousMillis >= 3000) {
      BlackoutStrip();
    }
    
    if (Serial.available() > 0) {
      incoming = Serial.readString();
      int posColon = incoming.indexOf(':');
      String ledString = incoming.substring(0, posColon);
      int numLeds = ledString.toInt();

      previousMillis = currentMillis; // reset

      // Max Rpm blink LEDs
      if(numLeds == NUM_LEDS){
        BlinkLeds(numLeds);
      } else if (numLeds >= 1 && numLeds < NUM_LEDS) {
        if(prevLedCount > numLeds) {
          TurnOffLeds(prevLedCount, numLeds);
        } else {
          TurnOnLeds(numLeds);
        }
        prevLedCount = numLeds;
      } else {
        BlackoutStrip();
        incoming = "";
        prevLedCount = 0;
      }
    }
  }

  /*
  Turn on leds in forward direction
  */
  void TurnOnLeds(int numLeds){
    float gradientindex = 0;
    for(int i = 0; i < numLeds; i++){
      leds[i] = ColorFromPalette( rpmColourPalette, gradientindex);
      gradientindex = gradientindex + 10.6;
      FastLED.show();
    }
  }

  /*
  Blink LEDs
  */
  void BlinkLeds(int numLeds){
    TurnOnLeds(numLeds);
    delay(10);
    BlackoutStrip();
    delay(10);
  }

  /*
  Turn off leds from reverse direction
  */
  void TurnOffLeds(int prevLedCount, int numLeds){
    for(int i = prevLedCount; i >= numLeds; i--) {
      leds[i] = CRGB::Black;
      FastLED.show();
    }
  }

  /*
  Turn off all leds in strip
  */
  void BlackoutStrip(){
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
  }
