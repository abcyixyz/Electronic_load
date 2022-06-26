#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include <esp_err.h>
#include "gpio_pin.h"
#include <i2cdev.h>
#include "i2c_device.h"
#include "onebus_device.h"


void thread_i2c_bus1(void *pvParameters)
{
    i2c_adc_ads1110_init1();
    i2c_dac_mcp4725_init1();
    while (1)
    {
        i2c_adc_ads1110_read1();
        i2c_dac_mcp4725_write1(1.0);
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void thread_i2c_bus2(void *pvParameters)
{
    uint16_t count = 0;
    i2c_adc_ads1110_init2();
    i2c_oled_init2();
    while (1)
    {
        if (count < 10) {
            count++;
            i2c_oled_write2(encoder_val);
        } else {
            count=0;
            i2c_adc_ads1110_read2();
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void thread_temp(void *pvParameters)
{
    onebus_ds18b20_init();
    while (1)
    {
        onebus_ds18b20_read();
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void thread_main(void *pvParameters)
{
    uint8_t count=0;
    encoder_pin_init();
    voltage_pin_init();
    while (1)
    {
        count ? (count=0) : (count=1);
        encoder_key_read();
        //voltage_pin_write(count);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main()
{
    // Init i2cdev library
    ESP_ERROR_CHECK(i2cdev_init());

    xTaskCreate(thread_i2c_bus1, "thread_i2c_bus1", configMINIMAL_STACK_SIZE * 3, NULL, 8, NULL);
    xTaskCreate(thread_i2c_bus2, "thread_i2c_bus2", configMINIMAL_STACK_SIZE * 3, NULL, 7, NULL);

    xTaskCreate(thread_temp, "thread_temp", configMINIMAL_STACK_SIZE * 3, NULL, 6, NULL);
    xTaskCreate(thread_main, "thread_temp", configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
}

