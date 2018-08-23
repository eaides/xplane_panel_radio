#include <Pushbutton.h>

/* This example uses the Pushbutton library to demonstrate three
 * different methods for detecting a button press and release. It
 * blinks the yellow user LED on pin 13 each time the a button on
 * pin 12 is pressed and released.  A normally-open momentary
 * pushbutton should be connected between pin 12 and ground.  */

#define LED_PIN 23
#define BUTTON_PIN 22

/* Create a Pushbutton object with default settings, which
 * enables the internal pull-up on the pin and interprets a HIGH
 * pin value as the default (unpressed) state of the
 * button. (Optional arguments can be passed to the constructor
 * to specify other button types and connection methods; see the
 * documentation for details.) */
Pushbutton button(BUTTON_PIN);
byte status_led = 0;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop()
{
  if (button.getSingleDebouncedRelease())
  {
    if (status_led == 0) {
      digitalWrite(LED_PIN, HIGH);  
      status_led = 1;
    } else {
      digitalWrite(LED_PIN, LOW);
      status_led = 0;
    }
    
    
  }
}
