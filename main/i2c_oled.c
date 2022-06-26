#include <driver/gpio.h>
#include <driver/spi_master.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>
#include <string.h>
#include <u8g2.h>
#include "u8g2_esp32_hal.h"
#include "i2c_device.h"

static const char *TAG = "ssd1306";

u8g2_t u8g2; // a structure which will contain all the data for one display

uint16_t width;

void i2c_oled_init2(void)
{
	u8g2_esp32_hal_t u8g2_esp32_hal = U8G2_ESP32_HAL_DEFAULT;
	u8g2_esp32_hal.sda  = I2C2_MASTER_SDA;
	u8g2_esp32_hal.scl  = I2C2_MASTER_SCL;
	u8g2_esp32_hal_init(u8g2_esp32_hal);


	u8g2_Setup_ssd1306_i2c_128x32_univision_f(
		&u8g2,
		U8G2_R0,
		//u8x8_byte_sw_i2c,
		u8g2_esp32_i2c_byte_cb,
		u8g2_esp32_gpio_and_delay_cb);  // init u8g2 structure
	u8x8_SetI2CAddress(&u8g2.u8x8,0x78);

	ESP_LOGI(TAG, "u8g2_InitDisplay");
	u8g2_InitDisplay(&u8g2); // send init sequence to the display, display is in sleep mode after this,

	ESP_LOGI(TAG, "u8g2_SetPowerSave");
	u8g2_SetPowerSave(&u8g2, 0); // wake up display

	ESP_LOGI(TAG, "All done!");
}

void i2c_oled_write2(int32_t value)
{
	width<100 ? width++ : (width=0);
	u8g2_ClearBuffer(&u8g2);
	u8g2_DrawBox(&u8g2, 0, 26, width,6);
	u8g2_DrawFrame(&u8g2, 0,26,100,6);

	u8g2_SetFont(&u8g2, u8g2_font_ncenB14_tr);
	u8g2_DrawStr(&u8g2, 2,17, u8x8_utoa(value));
	u8g2_SendBuffer(&u8g2);
}