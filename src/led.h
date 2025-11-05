#ifndef __LED_H__
#define __LED_H__

#include "pico/stdlib.h"

// Pinos do LED RGB
#define LED_R_PIN 13
#define LED_G_PIN 11
#define LED_B_PIN 12

#define LED_BRIGHTNESS 0.4f // 40% do brilho máximo

// Funções públicas
void led_init(void);
void led_set_color(uint8_t r, uint8_t g, uint8_t b);

#endif // __LED_H__
