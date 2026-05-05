#include <FastLED.h>

// pin de datos
#define LED_PIN 6

// total de leds
#define NUM_LEDS 512

// brillo
#define BRIGHTNESS 50

// tamaño del cubo
#define SIZE 8

CRGB leds[NUM_LEDS];

// matriz logica 3D
int cube[SIZE][SIZE][SIZE];

// convierte coordenadas a indice
int getIndex(int x, int y, int z) {
  return z * SIZE * SIZE + y * SIZE + x;
}

// limpia matriz logica
void clearMatrix() {
  for (int x = 0; x < SIZE; x++)
    for (int y = 0; y < SIZE; y++)
      for (int z = 0; z < SIZE; z++)
        cube[x][y][z] = 0;
}

// renderiza matriz a leds
void renderCube(CRGB color) {
  for (int x = 0; x < SIZE; x++) {
    for (int y = 0; y < SIZE; y++) {
      for (int z = 0; z < SIZE; z++) {

        if (cube[x][y][z] == 1)
          leds[getIndex(x, y, z)] = color;
        else
          leds[getIndex(x, y, z)] = CRGB::Black;

      }
    }
  }
  FastLED.show();
}

// enciende voxel logico
void setVoxel(int x, int y, int z) {
  if (x >= 0 && x < SIZE && y >= 0 && y < SIZE && z >= 0 && z < SIZE)
    cube[x][y][z] = 1;
}

// apaga todo
void clearCube() {
  clearMatrix();
  renderCube(CRGB::Black);
}

// plano XY
void planoXY(int z) {
  clearMatrix();

  for (int x = 0; x < SIZE; x++)
    for (int y = 0; y < SIZE; y++)
      setVoxel(x, y, z);

  renderCube(CRGB::Blue);
}

// plano XZ
void planoXZ(int y) {
  clearMatrix();

  for (int x = 0; x < SIZE; x++)
    for (int z = 0; z < SIZE; z++)
      setVoxel(x, y, z);

  renderCube(CRGB::Red);
}

// plano YZ
void planoYZ(int x) {
  clearMatrix();

  for (int y = 0; y < SIZE; y++)
    for (int z = 0; z < SIZE; z++)
      setVoxel(x, y, z);

  renderCube(CRGB::Green);
}

// cubo completo
void cuboCompleto() {
  clearMatrix();

  for (int x = 0; x < SIZE; x++)
    for (int y = 0; y < SIZE; y++)
      for (int z = 0; z < SIZE; z++)
        setVoxel(x, y, z);

  renderCube(CRGB::White);
}

// barrido en Z
void barridoXY() {
  for (int z = 0; z < SIZE; z++) {
    planoXY(z);
    delay(150);
  }
}

// expansion desde centro
void expansionCentro() {
  int c = SIZE / 2;

  for (int r = 0; r <= c; r++) {
    clearMatrix();

    for (int x = c - r; x <= c + r; x++)
      for (int y = c - r; y <= c + r; y++)
        for (int z = c - r; z <= c + r; z++)
          setVoxel(x, y, z);

    renderCube(CRGB::Purple);
    delay(200);
  }
}

// rotacion de planos
void rotacionPlanos() {
  for (int i = 0; i < SIZE; i++) {
    planoXY(i);
    delay(100);

    planoYZ(i);
    delay(100);

    planoXZ(i);
    delay(100);
  }
}

// animacion tipo lluvia
void lluvia() {
  for (int i = 0; i < 30; i++) {

    int x = random(0, SIZE);
    int y = random(0, SIZE);

    for (int z = SIZE - 1; z >= 0; z--) {
      clearMatrix();
      setVoxel(x, y, z);
      renderCube(CRGB::Cyan);
      delay(60);
    }
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

  lluvia();
  delay(300);

  cuboCompleto();
  delay(500);

  clearCube();
  delay(500);
}