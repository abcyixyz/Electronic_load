#include <string.h>
#include <driver/gpio.h>
#include <esp_log.h>
#include <esp_err.h>
#include "gpio_pin.h"

int32_t encoder_val;

#define GPIO_INPUT_PIN_SEL  ((1ULL<<ENCORD_B_GPIO) | (1ULL<<ENCORD_K_GPIO))//打开引脚标志
#define ESP_INTR_FLAG_DEFAULT 0   //设置中断编号

static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    uint32_t gpio_num = (uint32_t) arg;
    if(gpio_num == ENCORD_A_GPIO)
    {
        if(gpio_get_level(ENCORD_B_GPIO))
        {
            encoder_val--;
        } else {
            encoder_val++;
        }
    }
    return;
}

void encoder_pin_init(void)
{
    gpio_config_t config;

    memset(&config, 0, sizeof(gpio_config_t));
    config.mode = GPIO_MODE_INPUT;
    config.pull_up_en = GPIO_PULLUP_DISABLE;
    config.intr_type = GPIO_INTR_DISABLE;
    config.pin_bit_mask = GPIO_INPUT_PIN_SEL;
    gpio_config(&config);

    memset(&config, 0, sizeof(gpio_config_t));
    config.mode = GPIO_MODE_INPUT;
    config.pull_up_en = GPIO_PULLUP_DISABLE;
    config.intr_type = GPIO_PIN_INTR_POSEDGE;
    config.pin_bit_mask = (1ULL<<ENCORD_A_GPIO);
    gpio_config(&config);

    gpio_set_intr_type(ENCORD_A_GPIO, GPIO_INTR_POSEDGE);

    //install gpio isr service
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
    //hook isr handler for specific gpio pin
    gpio_isr_handler_add(ENCORD_A_GPIO, gpio_isr_handler, (void*) ENCORD_A_GPIO);
}

void encoder_key_read(void)
{
    ESP_LOGI("gpio_pin", "key     = %d", gpio_get_level(ENCORD_K_GPIO));
    ESP_LOGI("gpio_pin", "encoder = %d", encoder_val);
}


void voltage_pin_init(void)
{
    gpio_config_t config;

    memset(&config, 0, sizeof(gpio_config_t));
    config.mode = GPIO_MODE_OUTPUT;
    config.pull_up_en = GPIO_PULLUP_DISABLE;
    config.pull_down_en = GPIO_PULLDOWN_DISABLE;
    config.intr_type = GPIO_PIN_INTR_DISABLE;
    config.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    gpio_config(&config);
}

void voltage_pin_write(uint32_t level)
{
    gpio_set_level(V_SWITCH_GPIO, level);
}
