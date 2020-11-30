/*
  ATtiny85 sleep test w/ LED

  This code makes an LED to blink random times at a random rythm. When it's not doing anything, it goes to sleep.
  It only wakes up with the watchdog timer. This code is designed to run on the ATTiny 25/45/85

  The connections to the ATTiny are as follows:
  ATTiny    Arduino    Info
  Pin  1  - 5          RESET
  Pin  2  - 3 / A3
  Pin  3  - 4 / A2     (PWM)
  Pin  4  -            GND
  Pin  5  - 0          LED (PWM)
  Pin  6  - 1          (PWM)
  Pin  7  - 2 / A1
  Pin  8  -   +Vcc

  Using code from www.re-innovation.co.uk for more details including flow code

  14/11/13 by Matt Little (matt@re-innovation.co.uk/www.re-innovation.co.uk)
  Added code from (http://www.insidegadgets.com/2011/02/05/reduce-attiny-power-consumption-by-sleeping-with-the-watchdog-timer/).
  Thanks to: KHM 2008 / Lab3/  Martin Nawrath nawrath@khm.de - Kunsthochschule fuer Medien Koeln - Academy of Media Arts Cologne

  05/02/2011 - InsideGadgets (www.insidegadgets.com) to suit the ATtiny85 and removed the cbi( MCUCR,SE ) section in setup() to match the Atmel datasheet recommendations
  14/11/2013 - Added Power_Down Sleep mode - Matt Little
  20/11/2020 - changed to use FastLED

  This example code is in the public domain.
*/
#include <FastLED.h>
#include <avr/sleep.h>


// *********** Routines used in the sleep code **********************
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

// *********** Global variables **********************
#define NUM_LEDS 64  // How many leds in your strip?
#define DATA_PIN 3   // Where are they connected?
CRGB leds[NUM_LEDS];

// *********** I/O Pins **********************
const int led = 0;

// the setup routine runs once when you press reset:
void setup()  {
  pinMode(led, OUTPUT);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  turnAll( CRGB::White );
  
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
    //analogWrite(led, fadeValue);  // sets the value (range from 0 to 255):
    FastLED.setBrightness(fadeValue);
    delay(30);  // wait for 30 milliseconds to see the dimming effect
    FastLED.show(); // display this frame
  }

  setup_watchdog(9); // approximately 8 seconds sleep
}

// the loop routine runs over and over again forever:
void loop()  {

  digitalWrite(DATA_PIN, LOW); // Shuts down the OUT port
  delay(1);
  system_sleep();  // Send the unit to sleep

  turnAll( CRGB::White );
  int d = random(2, 10);
  for (int i = 0; i < random(0, 5); i++) {
    for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
    FastLED.setBrightness(fadeValue);
    delay(d);  // wait for 30 milliseconds to see the dimming effect
    FastLED.show(); // display this frame
    }
    for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
    FastLED.setBrightness(fadeValue);
    delay(d);  // wait for 30 milliseconds to see the dimming effect
    FastLED.show(); // display this frame
    }
  }
  turnAll( CRGB::Black );
}


// set system into the sleep state
// system wakes up when wtchdog is timed out
void system_sleep() {
  cbi(ADCSRA, ADEN);                   // switch Analog to Digitalconverter OFF
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
  sleep_enable();
  sleep_mode();                        // System actually sleeps here
  sleep_disable();                     // System continues execution here when watchdog timed out
  sbi(ADCSRA, ADEN);                   // switch Analog to Digitalconverter ON

}

// 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms
// 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec
void setup_watchdog(int ii) {

  byte bb;
  int ww;
  if (ii > 9 ) ii = 9;
  bb = ii & 7;
  if (ii > 7) bb |= (1 << 5);
  bb |= (1 << WDCE);
  ww = bb;

  MCUSR &= ~(1 << WDRF);
  WDTCR |= (1 << WDCE) | (1 << WDE);  // start timed sequence
  WDTCR = bb;          // set new watchdog timeout value
  WDTCR |= _BV(WDIE);
}

// Watchdog Interrupt Service / is executed when watchdog timed out
ISR(WDT_vect) {
  //do nothing f_wdt = 1; // set global flag
}

// Helper for led Matrix
void turnAll( CRGB  _c ) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = _c;
  }
  FastLED.show();

}
