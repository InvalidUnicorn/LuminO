#include <Adafruit_NeoPixel.h> // Libary for LED-Ring

#define LED_PIN D1 // Make sure this PIN is right!
#define BUTTON_RED_PIN D2 // Make sure this PIN is right!
#define BUTTON_BLACK_PIN D3 // Make sure this PIN is right!
#define STRIPSIZE 12

Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIPSIZE, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  
  Serial.begin(9600);
  pinMode(BUTTON_RED_PIN, INPUT_PULLUP); // Initialize Red Button
  pinMode(BUTTON_BLACK_PIN, INPUT_PULLUP); // Initialize Black Button
  strip.begin();
  strip.setBrightness(50);  // Lower brightness and save eyeballs!
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  if(!digitalRead(BUTTON_RED_PIN) && !digitalRead(BUTTON_BLACK_PIN)) {
    rainbow(30);
  }
  if(!digitalRead(BUTTON_RED_PIN)) {
    colorFill(255,0,0);
    return;
  }
  if(!digitalRead(BUTTON_BLACK_PIN)) {
    colorFill(255,255,255);
    return;
  }
  colorFill(0,0,0);
  delay(10);
}


void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i*1+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void colorFill(int r, int g, int b) {
  for(int i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(r, g, b));
      strip.show();
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
