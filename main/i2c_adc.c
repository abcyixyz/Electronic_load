#include <i2cdev.h>
#include "ADS1110.h"
#include <esp_log.h>
#include <esp_err.h>
#include "i2c_device.h"

ADS1110_t adc[2] = { 0 };
i2c_dev_t dev[2] = { 0 };

void i2c_adc_ads1110_init1(void)
{
    ads1110_i2c_init(&dev[0], ADS1110A0, I2C1_PORT, I2C1_MASTER_SDA, I2C1_MASTER_SCL);
    ads1110_register(&adc[0], dev[0]);
}

void i2c_adc_ads1110_init2(void)
{
    ads1110_i2c_init(&dev[1], ADS1110A0, I2C2_PORT, I2C2_MASTER_SDA, I2C2_MASTER_SCL);
    ads1110_register(&adc[1], dev[1]);
}

void i2c_adc_ads1110_read1(void)
{
    ESP_LOGI("adc1", "bus1 ads1110 voltage = %d mV", ads1110_getVoltage(&adc[0]));
}

void i2c_adc_ads1110_read2(void)
{
    ESP_LOGI("adc2", "bus2 ads1110 current = %d mV", ads1110_getVoltage(&adc[1]));
}