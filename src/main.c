#include <math.h>
#include "pico/stdlib.h"
#include "color_sensor.h"

int main() {
    stdio_init_all();
    sleep_ms(3000);
    color_sensor_init();

    color_data_t data;

    while (1) {
        color_sensor_read(&data);

        printf("RAW -> C:%-5u R:%-5u G:%-5u B:%-5u | ", data.c, data.r, data.g, data.b);

        // Lógica para detectar a cor dominante
        if (data.c < 500) { // Limiar para considerar "Preto"
            printf("COR DETECTADA: PRETO\n");
        } else {
            // Normaliza os valores
            float r_norm = (float)data.r / data.c * 100.0f;
            float g_norm = (float)data.g / data.c * 100.0f;
            float b_norm = (float)data.b / data.c * 100.0f;

            float max_val = fmaxf(r_norm, fmaxf(g_norm, b_norm));
            float min_val = fminf(r_norm, fminf(g_norm, b_norm));

            // Verifica se é Branco/Cinza
            if ((max_val - min_val) < 10.0f) {
                printf("COR DETECTADA: BRANCO/CINZA\n");
            }
            // Encontra a cor dominante
            else if (r_norm > g_norm && r_norm > b_norm) {
                printf("COR DETECTADA: VERMELHO\n");
            } else if (g_norm > r_norm && g_norm > b_norm) {
                printf("COR DETECTADA: VERDE\n");
            } else {
                printf("COR DETECTADA: AZUL\n");
            }
        }
        sleep_ms(1000);
    }
    return 0;
}