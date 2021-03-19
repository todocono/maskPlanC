/*
  ATtiny85 with WS2812 8x8 matrix &



  The connections to the ATTiny are as follows:
  ATTiny    Arduino    Info
  Pin  1  - 5          RESET
  Pin  2  - 3 / A3     WS2812b
  Pin  3  - 4 / A2     MIC DIGITAL (PWM)
  Pin  4  -            GND
  Pin  5  - 0          LED (PWM)
  Pin  6  - 1          (PWM)
  Pin  7  - 2 / A1     MIC ANALOG
  Pin  8  -   +Vcc

  This example code is in the public domain.

  http://github.com/todocono/
*/


#include <FastLED.h>

#define NUM_LEDS      32  // How many leds in your strip?
#define DATA_PIN      11   // Where are they connected?
#define MIC           1
CRGB leds[NUM_LEDS];

//
//CRGBPalette16 gPal;       //for Fire2012
//bool gReverseDirection = false;
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
//
//int n = 0;

#define BRIGHTNESS         100
#define FRAMES_PER_SECOND  50
//
//// #define TEST  //only usable with Arduino UNO
//const int animationDelay = 250;
//const int animationQty = 4;
//const int animation[animationQty][8] =
//{ //smiley
//  { //first image
//    B00000000,
//    B00000000,
//    B00000000,
//    B00111100,
//    B00011000,
//    B00000000,
//    B00000000,
//    B00000000
//  },
//  { //second image
//    B00000000,
//    B00000000,
//    B00000000,
//    B00100100,
//    B00100100,
//    B00111100,
//    B00000000,
//    B00000000
//  },
//  { //third image
//    B00000000,
//    B00000000,
//    B01000010,
//    B01000010,
//    B01000010,
//    B01111110,
//    B01111110,
//    B00000000
//  },
//  { //fourth image
//    B10000001,
//    B10000001,
//    B10000001,
//    B10000001,
//    B11000011,
//    B11000011,
//    B11111111,
//    B11111111
//  }
//};


/*  concentric circles
  {
  { //first image
    B00000000,
    B00000000,
    B00000000,
    B00011000,
    B00011000,
    B00000000,
    B00000000,
    B00000000
  },
  { //second image
    B00000000,
    B00000000,
    B00111100,
    B00100100,
    B00100100,
    B00111100,
    B00000000,
    B00000000
  },
  { //third image
    B00000000,
    B01111110,
    B01000010,
    B01000010,
    B01000010,
    B01000010,
    B01111110,
    B00000000
  },
  { //fourth image
    B11111111,
    B10000001,
    B10000001,
    B10000001,
    B10000001,
    B10000001,
    B10000001,
    B11111111
  }
  };
*/

// the setup function runs once when you press reset or power the board
void setup() {
#ifdef TEST
  Serial.begin(9600);
#endif
  // initialize digital pin LED_BUILTIN as an output.
  // pinMode(4, OUTPUT);
  pinMode(A2, INPUT);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

  // This first palette is the basic 'black body radiation' colors,
  // which run from black to red to bright yellow to white.
  // gPal = HeatColors_p;

  // These are other ways to set up the color palette for the 'fire'.
  // First, a gradient from black to red to yellow to white -- similar to HeatColors_p
  //   gPal = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::Yellow, CRGB::White);

  // Second, this palette is like the heat colors, but blue/aqua instead of red/yellow
  //   gPal = CRGBPalette16( CRGB::Black, CRGB::Blue, CRGB::Aqua,  CRGB::White);

  // Third, here's a simpler, three-step gradient, from black to red to white
  //  gPal = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::White);
}

// the loop function runs over and over again forever
void loop() {

  //  Fire2012WithPalette(); // run simulation frame, using palette colors
  // rainbow();

  //  if (digitalRead(A2)) {
  //    cylon(CRGB::Pink);
  //  }
  // FastLED.setBrightness(readMic());
  // FastLED.show(); // display this frame
  // FastLED.delay(1000 / FRAMES_PER_SECOND); //the second parameter is frames per second (50 by default)
  //
    turnAll( CRGB::Green );
  //  delay(1000);                       // wait for a second
  //
  //
  //  turnAll( CRGB::Blue );
  //  delay(1000);                       // wait for a second

  // matrixBoom(); //iterates among the 4 animations

  //  if ( readMic() > 3) {
  //    matrixT(n++); //shows among the 4 animations
  //    delay(10);
  //    if (n >= animationQty) n = 0;
  //  }
  //
  //  //
  //  EVERY_N_MILLISECONDS( 400 ) { // do some periodic updates
  //    //    if (gHue++ > 360) gHue = 0;  // slowly cycle the "base color" through the rainbow
  //    //        matrixT(n++); //shows among the 4 animations
  //    //        if (n >= animationQty) n = 0;
  //    //
  //  }
  // EVERY_N_SECONDS( 10 ) {doSmthng } // change patterns periodically
  FastLED.show(); // display this frame
}




/* * * * * * * * .* * * * * * * * * * * * *
    Functions you can choose to use with your LED matrix
    Where color is one of these predefined RGB colors.
  AliceBlue =0xF0F8FF, Amethyst =0x9966CC, AntiqueWhite =0xFAEBD7, Aqua =0x00FFFF,
  Aquamarine =0x7FFFD4, Azure =0xF0FFFF, Beige =0xF5F5DC, Bisque =0xFFE4C4,
  Black =0x000000, BlanchedAlmond =0xFFEBCD, Blue =0x0000FF, BlueViolet =0x8A2BE2,
  Brown =0xA52A2A, BurlyWood =0xDEB887, CadetBlue =0x5F9EA0, Chartreuse =0x7FFF00,
  Chocolate =0xD2691E, Coral =0xFF7F50, CornflowerBlue =0x6495ED, Cornsilk =0xFFF8DC,
  Crimson =0xDC143C, Cyan =0x00FFFF, DarkBlue =0x00008B, DarkCyan =0x008B8B,
  DarkGoldenrod =0xB8860B, DarkGray =0xA9A9A9, DarkGrey =0xA9A9A9, DarkGreen =0x006400,
  DarkKhaki =0xBDB76B, DarkMagenta =0x8B008B, DarkOliveGreen =0x556B2F, DarkOrange =0xFF8C00,
  DarkOrchid =0x9932CC, DarkRed =0x8B0000, DarkSalmon =0xE9967A, DarkSeaGreen =0x8FBC8F,
  DarkSlateBlue =0x483D8B, DarkSlateGray =0x2F4F4F, DarkSlateGrey =0x2F4F4F, DarkTurquoise =0x00CED1,
  DarkViolet =0x9400D3, DeepPink =0xFF1493, DeepSkyBlue =0x00BFFF, DimGray =0x696969,
  DimGrey =0x696969, DodgerBlue =0x1E90FF, FireBrick =0xB22222, FloralWhite =0xFFFAF0,
  ForestGreen =0x228B22, Fuchsia =0xFF00FF, Gainsboro =0xDCDCDC, GhostWhite =0xF8F8FF,
  Gold =0xFFD700, Goldenrod =0xDAA520, Gray =0x808080, Grey =0x808080,
  Green =0x008000, GreenYellow =0xADFF2F, Honeydew =0xF0FFF0, HotPink =0xFF69B4,
  IndianRed =0xCD5C5C, Indigo =0x4B0082, Ivory =0xFFFFF0, Khaki =0xF0E68C,
  Lavender =0xE6E6FA, LavenderBlush =0xFFF0F5, LawnGreen =0x7CFC00, LemonChiffon =0xFFFACD,
  LightBlue =0xADD8E6, LightCoral =0xF08080, LightCyan =0xE0FFFF, LightGoldenrodYellow =0xFAFAD2,
  LightGreen =0x90EE90, LightGrey =0xD3D3D3, LightPink =0xFFB6C1, LightSalmon =0xFFA07A,
  LightSeaGreen =0x20B2AA, LightSkyBlue =0x87CEFA, LightSlateGray =0x778899, LightSlateGrey =0x778899,
  LightSteelBlue =0xB0C4DE, LightYellow =0xFFFFE0, Lime =0x00FF00, LimeGreen =0x32CD32,
  Linen =0xFAF0E6, Magenta =0xFF00FF, Maroon =0x800000, MediumAquamarine =0x66CDAA,
  MediumBlue =0x0000CD, MediumOrchid =0xBA55D3, MediumPurple =0x9370DB, MediumSeaGreen =0x3CB371,
  MediumSlateBlue =0x7B68EE, MediumSpringGreen =0x00FA9A, MediumTurquoise =0x48D1CC, MediumVioletRed =0xC71585,
  MidnightBlue =0x191970, MintCream =0xF5FFFA, MistyRose =0xFFE4E1, Moccasin =0xFFE4B5,
  NavajoWhite =0xFFDEAD, Navy =0x000080, OldLace =0xFDF5E6, Olive =0x808000,
  OliveDrab =0x6B8E23, Orange =0xFFA500, OrangeRed =0xFF4500, Orchid =0xDA70D6,
  PaleGoldenrod =0xEEE8AA, PaleGreen =0x98FB98, PaleTurquoise =0xAFEEEE, PaleVioletRed =0xDB7093,
  PapayaWhip =0xFFEFD5, PeachPuff =0xFFDAB9, Peru =0xCD853F, Pink =0xFFC0CB,
  Plaid =0xCC5533, Plum =0xDDA0DD, PowderBlue =0xB0E0E6, Purple =0x800080,
  Red =0xFF0000, RosyBrown =0xBC8F8F, RoyalBlue =0x4169E1, SaddleBrown =0x8B4513,
  Salmon =0xFA8072, SandyBrown =0xF4A460, SeaGreen =0x2E8B57, Seashell =0xFFF5EE,
  Sienna =0xA0522D, Silver =0xC0C0C0, SkyBlue =0x87CEEB, SlateBlue =0x6A5ACD,
  SlateGray =0x708090, SlateGrey =0x708090, Snow =0xFFFAFA, SpringGreen =0x00FF7F,
  SteelBlue =0x4682B4, Tan =0xD2B48C, Teal =0x008080, Thistle =0xD8BFD8,
  Tomato =0xFF6347, Turquoise =0x40E0D0, Violet =0xEE82EE, Wheat =0xF5DEB3,
  White =0xFFFFFF, WhiteSmoke =0xF5F5F5, Yellow =0xFFFF00, YellowGreen =0x9ACD32,
  FairyLight =0xFFE42D, FairyLightNCC =0xFF9D2A
  }

*/


void turnAll( CRGB  _c ) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = _c;
  }
  //FastLED.show();
}
