#ifndef __I2C_DEVICE_H_
#define __I2C_DEVICE_H_

#ifdef __cplusplus
extern "C" {
#endif

//i2c
#define I2C1_PORT           0
#define I2C1_MASTER_SDA     19
#define I2C1_MASTER_SCL     21

#define I2C2_PORT           1
#define I2C2_MASTER_SDA     5
#define I2C2_MASTER_SCL     18


void i2c_adc_ads1110_init1(void);
void i2c_adc_ads1110_read1(void);
void i2c_adc_ads1110_init2(void);
void i2c_adc_ads1110_read2(void);


void i2c_dac_mcp4725_init1(void);
void i2c_dac_mcp4725_write1(float vout);

void i2c_oled_init2(void);
void i2c_oled_write2(int32_t value);


#ifdef __cplusplus
}
#endif

#endif