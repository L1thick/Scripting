#include <Adafruit_NeoPixel.h>

#define PIN_NEO_PIXEL 4       // NeoPixel input
#define NUM_PIXELS 13         // Strip Length
#define DELAY_INTERVAL 500    // Half-second delay
#define LIGHT_ON_TIME 10000   // 10 seconds

Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);

int inputSensor1 = 10;      // First motion sensor input
int inputSensor2 = 9;       // Second motion sensor input

void setup() {
  NeoPixel.begin();
  pinMode(inputSensor1, INPUT);
  pinMode(inputSensor2, INPUT);
}

void loop() {
  if (digitalRead(inputSensor1) == HIGH) {
    activateNeoPixelSequence(false);
  } else if (digitalRead(inputSensor2) == HIGH) {
    activateNeoPixelSequence(true);
  }
}

void activateNeoPixelSequence(bool reverse) {
  Serial.println("Motion detected!");
  NeoPixel.clear();

  for (int i = 0; i < NUM_PIXELS; i++) {
    int pixelIndex = reverse ? NUM_PIXELS - 1 - i : i;
    NeoPixel.setPixelColor(pixelIndex, NeoPixel.Color(0, 255, 0));
    NeoPixel.show();
    delay(DELAY_INTERVAL);
  }

  delay(LIGHT_ON_TIME);

  NeoPixel.clear();
  NeoPixel.show();
}
