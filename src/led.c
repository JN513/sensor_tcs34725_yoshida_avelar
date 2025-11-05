#include "led.h"
#include "hardware/pwm.h"

// Função auxiliar para configurar um pino em modo PWM
static uint pwm_init_gpio(uint gpio) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(gpio);

    // Configura PWM com clock padrão (1 MHz)
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.0f); // reduz frequência → brilho mais estável
    pwm_init(slice, &config, true);

    return slice;
}

void led_init(void) {
    pwm_init_gpio(LED_R_PIN);
    pwm_init_gpio(LED_G_PIN);
    pwm_init_gpio(LED_B_PIN);
}

// Define a cor em intensidades (0–255)
void led_set_color(uint8_t r, uint8_t g, uint8_t b) {
    // Converte 0–255 para nível PWM (0–65535)
    //uint16_t r_level = (uint16_t)(r * 257); // 255*257 ≈ 65535
    //uint16_t g_level = (uint16_t)(g * 257);
    //uint16_t b_level = (uint16_t)(b * 257);

    uint16_t r_level = (uint16_t)(r * 257 * LED_BRIGHTNESS);
    uint16_t g_level = (uint16_t)(g * 257 * LED_BRIGHTNESS);
    uint16_t b_level = (uint16_t)(b * 257 * LED_BRIGHTNESS);
    
    //pwm_set_gpio_level(LED_R_PIN, r_level);
    //pwm_set_gpio_level(LED_G_PIN, g_level);
    //pwm_set_gpio_level(LED_B_PIN, b_level);

    pwm_set_gpio_level(LED_R_PIN, 65535 - r_level);
    pwm_set_gpio_level(LED_G_PIN, 65535 - g_level);
    pwm_set_gpio_level(LED_B_PIN, 65535 - b_level);
}
