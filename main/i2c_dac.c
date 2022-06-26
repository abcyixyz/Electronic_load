#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>
#include <string.h>
#include <esp_log.h>
#include <esp_err.h>
#include <i2cdev.h>
#include <mcp4725.h>
#include "i2c_device.h"


#define MCP4725_ADDR    0x60
#define VDD             3.3
i2c_dev_t dev_dac;

static void wait_for_eeprom(i2c_dev_t *dev)
{
    bool busy;
    while (true)
    {
        mcp4725_eeprom_busy(dev, &busy);
        if (!busy)
            return;
        ESP_LOGI("i2c dac", "...DAC is busy, waiting...");
        vTaskDelay(1);
    }
}

void i2c_dac_mcp4725_init1(void)
{
    memset(&dev_dac, 0, sizeof(i2c_dev_t));
    mcp4725_init_desc(&dev_dac, MCP4725_ADDR, I2C1_PORT, I2C1_MASTER_SDA, I2C1_MASTER_SCL);
    
    mcp4725_power_mode_t pm;
    mcp4725_get_power_mode(&dev_dac, true, &pm);
    if (pm != MCP4725_PM_NORMAL)
    {
        ESP_LOGI("i2c dac", "DAC was sleeping... Wake up Neo!");
        mcp4725_set_power_mode(&dev_dac, true, MCP4725_PM_NORMAL);
        wait_for_eeprom(&dev_dac);
    }

    ESP_LOGI("i2c dac", "Set default DAC output value to MAX...");
    mcp4725_set_raw_output(&dev_dac, MCP4725_MAX_VALUE, true);
    wait_for_eeprom(&dev_dac);

    ESP_LOGI("i2c dac", "Now let's generate the sawtooth wave in slow manner");

}

void i2c_dac_mcp4725_write1(float vout)
{
    if (vout > VDD) vout = 0;

    ESP_LOGI("i2c dac", "bus1 Vout: %.02f", vout);
    mcp4725_set_voltage(&dev_dac, VDD, vout, false);
}