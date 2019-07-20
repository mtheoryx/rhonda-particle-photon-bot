#include <FastLED.h>
FASTLED_USING_NAMESPACE;
#define NUM_LEDS 3
#define DATA_PIN 6

bool TURNED_ON;          //Is the led on
unsigned int COLOR_NAME; //What color are we showing, rebbecca purple by default

CRGB leds[NUM_LEDS];

void setup()
{
  // LED registry requirements
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  // Particle led on/off
  Particle.function("led", ledToggle);

  //Particle set led color
  Particle.function("setColor", ledColor);

  // Initialize State
  TURNED_ON = false;
}

void loop()
{
  // if "turned on" do the thing
  if (TURNED_ON == true)
  {
    for (int reps = 0; reps < 3; reps++)
    {
      for (int dot = 0; dot < NUM_LEDS; dot++)
      {
        // leds[dot] = 0xFFFFFF;
        leds[dot] = COLOR_NAME;
        FastLED.show();
        delay(500);
        // clear this led for the next time around the loop
        leds[dot] = 0x000000;
        delay(250);
      }
    }
    TURNED_ON = false;
    // for(int dot = 0; dot < NUM_LEDS; dot++) {
    //     // clear this led for the next time around the loop
    //     // essentially turn it black color
    //     leds[dot] = 0x000000;
    //     FastLED.show();
    // }
    // FastLED.show();
  }
  for (int dot = 0; dot < NUM_LEDS; dot++)
  {
    // clear this led for the next time around the loop
    // essentially turn it black color
    leds[dot] = 0x000000;
  }
  FastLED.show();
  // } else {
  //     for(int dot = 0; dot < NUM_LEDS; dot++) {
  //         // clear this led for the next time around the loop
  //         // essentially turn it black color
  //         leds[dot] = 0x000000;
  //     }
  //     FastLED.show();
  // }
}

int ledColor(String color)
{
  COLOR_NAME = strtoul(color, NULL, 16);
}

// Handle cloud function call
int ledToggle(String command)
{
  /* Particle.functions always take a string as an argument and return an integer.
    Since we can pass a string, it means that we can give the program commands on how the function should be used.
    In this case, telling the function "on" will turn the LED on and telling it "off" will turn the LED off.
    Then, the function returns a value to us to let us know what happened.
    In this case, it will return 1 for the LEDs turning on, 0 for the LEDs turning off,
    and -1 if we received a totally bogus command that didn't do anything to the LEDs.
    */

  if (command == "on")
  {
    TURNED_ON = true;
    return 1;
  }
  else if (command == "off")
  {
    TURNED_ON = false;
    return 0;
  }
  else
  {
    return -1;
  }
}
