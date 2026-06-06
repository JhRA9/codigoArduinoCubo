#include <FastLED.h>

#define LED_PIN 6

#define LED_TYPE WS2812
#define COLOR_ORDER GRB

#define BRIGHTNESS 180
#define STEP_TIME 180

// Cambia este valor de 1 a 8
#define FILAS_A_PROBAR 2

#define LEDS_POR_FILA 8
#define TOTAL_PANEL 64
#define LEDS_A_PROBAR (FILAS_A_PROBAR * LEDS_POR_FILA)

CRGB leds[TOTAL_PANEL];

uint8_t hue = 0;

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, TOTAL_PANEL);
  FastLED.setBrightness(BRIGHTNESS);

  // Apaga todo el panel al iniciar
  FastLED.clear();
  FastLED.show();
  delay(1000);
}

void loop() {
  apagarTodo();
  culebraIda();
  delay(300);

  apagarTodo();
  culebraRegreso();
  delay(300);
}

// Apaga los 64 LEDs
void apagarTodo() {
  for (int i = 0; i < TOTAL_PANEL; i++) {
    leds[i] = CRGB::Black;
  }

  FastLED.show();
}

// Culebra arcoiris solo en las filas indicadas
void culebraIda() {
  for (int i = 0; i < LEDS_A_PROBAR; i++) {
    limpiarZonaPrueba();

    if (i - 3 >= 0) leds[i - 3] = CHSV(hue - 45, 255, 50);
    if (i - 2 >= 0) leds[i - 2] = CHSV(hue - 30, 255, 100);
    if (i - 1 >= 0) leds[i - 1] = CHSV(hue - 15, 255, 160);

    leds[i] = CHSV(hue, 255, 255);

    FastLED.show();
    delay(STEP_TIME);

    hue += 12;
  }
}

// Culebra blanca solo en las filas indicadas
void culebraRegreso() {
  for (int i = LEDS_A_PROBAR - 1; i >= 0; i--) {
    limpiarZonaPrueba();

    if (i + 3 < LEDS_A_PROBAR) leds[i + 3] = CRGB(50, 50, 50);
    if (i + 2 < LEDS_A_PROBAR) leds[i + 2] = CRGB(100, 100, 100);
    if (i + 1 < LEDS_A_PROBAR) leds[i + 1] = CRGB(160, 160, 160);

    leds[i] = CRGB::White;

    FastLED.show();
    delay(STEP_TIME);
  }
}

// Limpia todo, pero mantiene la prueba limitada
void limpiarZonaPrueba() {
  for (int i = 0; i < TOTAL_PANEL; i++) {
    leds[i] = CRGB::Black;
  }
}