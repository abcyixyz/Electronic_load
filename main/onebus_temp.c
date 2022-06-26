#include <driver/gpio.h>
#include <ds18x20.h>
#include <esp_log.h>
#include <esp_err.h>
#include "onebus_device.h"

static const ds18x20_addr_t ADDR0 = DS18X20_ADDR0;

void onebus_ds18b20_init(void)
{
    gpio_set_pull_mode(SENSOR_GPIO, GPIO_PULLUP_ONLY);
}

void onebus_ds18b20_read(void)
{
    esp_err_t res;
    float temperature;

    res = ds18x20_measure_and_read(SENSOR_GPIO, ADDR0, &temperature);
    if (res != ESP_OK)
        ESP_LOGE("ds18x20", "Could not read from sensor %08x%08x: %d (%s)",
                (uint32_t)(ADDR0 >> 32), (uint32_t)ADDR0, res, esp_err_to_name(res));
    else
        ESP_LOGI("ds18x20", "Sensor %08x%08x: %.2f°C",
                (uint32_t)(ADDR0 >> 32), (uint32_t)ADDR0, temperature);
}