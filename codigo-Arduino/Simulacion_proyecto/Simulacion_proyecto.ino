#include <FastLED.h>

// pin de datos
#define LED_PIN 6

// total leds
#define NUM_LEDS 512

// brillo general
#define BRIGHTNESS 50

// arreglo de leds
CRGB leds[NUM_LEDS];

// tamano del cubo
#define SIZE 8

// convierte x,y,z a indice
int getIndex(int x, int y, int z) {
  return z * SIZE * SIZE + y * SIZE + x;
}

// enciende un led
void setLED(int x, int y, int z, CRGB color) {
  if (x >= 0 && x < SIZE && y >= 0 && y < SIZE && z >= 0 && z < SIZE) {
    leds[getIndex(x,y,z)] = color;
  }
}

// apaga todo
void clearCube() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

// plano XY en altura z
void planoXY(int z, CRGB color) {
  clearCube();

  for (int x = 0; x < SIZE; x++)
    for (int y = 0; y < SIZE; y++)
      setLED(x, y, z, color);

  FastLED.show();
}

// plano XZ en fila y
void planoXZ(int y, CRGB color) {
  clearCube();

  for (int x = 0; x < SIZE; x++)
    for (int z = 0; z < SIZE; z++)
      setLED(x, y, z, color);

  FastLED.show();
}

// plano YZ en columna x
void planoYZ(int x, CRGB color) {
  clearCube();

  for (int y = 0; y < SIZE; y++)
    for (int z = 0; z < SIZE; z++)
      setLED(x, y, z, color);

  FastLED.show();
}

// enciende todo el cubo
void cuboCompleto(CRGB color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;
  }

  FastLED.show();
}

// barrido en eje z
void barridoXY() {
  for (int z = 0; z < SIZE; z++) {
    planoXY(z, CRGB::Blue);
    delay(150);
  }
}

// expansion desde centro
void expansionCentro() {
  int c = SIZE / 2;

  for (int r = 0; r < c; r++) {
    clearCube();

    for (int x = c - r; x <= c + r; x++)
      for (int y = c - r; y <= c + r; y++)
        for (int z = c - r; z <= c + r; z++)
          setLED(x, y, z, CRGB::Green);

    FastLED.show();
    delay(200);
  }
}

// rotacion con planos
void rotacionPlanos() {
  for (int i = 0; i < SIZE; i++) {
    planoXY(i, CRGB::Red);
    delay(100);

    planoYZ(i, CRGB::Yellow);
    delay(100);

    planoXZ(i, CRGB::Purple);
    delay(100);
  }
}

// configuracion inicial
void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  clearCube();
}

// ciclo principal
void loop() {

  barridoXY();
  delay(300);

  expansionCentro();
  delay(300);

  rotacionPlanos();
  delay(300);

  clearCube();
  delay(500);
}