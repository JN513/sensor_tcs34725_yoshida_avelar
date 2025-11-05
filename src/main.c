#include <math.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "color_sensor.h"
#include "led.h"

// ---------- Conversão RGB → HSV ----------
void rgb_to_hsv(float r, float g, float b, float *h, float *s, float *v) {
    float max = fmaxf(r, fmaxf(g, b));
    float min = fminf(r, fminf(g, b));
    float delta = max - min;

    // Valor (brilho)
    *v = max;

    // Saturação
    *s = (max == 0) ? 0 : delta / max;

    // Matiz
    if (delta == 0) {
        *h = 0; // sem cor definida (branco/cinza/preto)
    } else if (max == r) {
        *h = 60.0f * fmodf(((g - b) / delta), 6.0f);
    } else if (max == g) {
        *h = 60.0f * (((b - r) / delta) + 2.0f);
    } else {
        *h = 60.0f * (((r - g) / delta) + 4.0f);
    }

    if (*h < 0) *h += 360.0f;
}

// ---------- Função de detecção de cor ----------
void detectar_cor(uint8_t r, uint8_t g, uint8_t b) {
    float rf = r / 255.0f;
    float gf = g / 255.0f;
    float bf = b / 255.0f;

    float h, s, v;
    rgb_to_hsv(rf, gf, bf, &h, &s, &v);

    // Classificação por saturação e valor
    if (v < 0.1f) {
        printf("COR DETECTADA: PRETO\n");
        return;
    }
    if (s < 0.2f) {
        if (v > 0.8f)
            printf("COR DETECTADA: BRANCO\n");
        else
            printf("COR DETECTADA: CINZA\n");
        return;
    }

    // Classificação por faixa de matiz (Hue)
    if (h < 15 || h >= 345)
        printf("COR DETECTADA: VERMELHO\n");
    else if (h < 45)
        printf("COR DETECTADA: LARANJA\n");
    else if (h < 70)
        printf("COR DETECTADA: AMARELO\n");
    else if (h < 160)
        printf("COR DETECTADA: VERDE\n");
    else if (h < 260)
        printf("COR DETECTADA: AZUL\n");
    else if (h < 320)
        printf("COR DETECTADA: ROXO\n");
    else
        printf("COR DETECTADA: MAGENTA\n");
}

// ---------- Programa principal ----------
int main() {
    stdio_init_all();
    sleep_ms(3000);
    color_sensor_init();
    led_init();

    color_data_t data;

    while (1) {
        color_sensor_read(&data);

        printf("RAW -> C:%-5u R:%-5u G:%-5u B:%-5u | ", data.c, data.r, data.g, data.b);

        // --- Detecta preto com base na luminosidade total ---
        if (data.c < 300) { // Limiar ajustável conforme ambiente
            printf("COR DETECTADA: PRETO\n");
            led_set_color(0, 0, 0); // LED apagado
            sleep_ms(1000);
            continue;
        }

        // Evita divisão por zero
        float c = (float)(data.c < 1 ? 1 : data.c);

        // Normaliza para 0–255 e gera HEX
        uint8_t r8 = (uint8_t)fminf((data.r / c) * 255.0f, 255.0f);
        uint8_t g8 = (uint8_t)fminf((data.g / c) * 255.0f, 255.0f);
        uint8_t b8 = (uint8_t)fminf((data.b / c) * 255.0f, 255.0f);

        printf("HEX -> #%02X%02X%02X | ", r8, g8, b8);

        led_set_color(r8, g8, b8);
        detectar_cor(r8, g8, b8);

        sleep_ms(1000);
    }
    return 0;
}

