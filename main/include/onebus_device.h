#ifndef __ONEBUS_DEVICE_H_
#define __ONEBUS_DEVICE_H_

#ifdef __cplusplus
extern "C" {
#endif

#define SENSOR_GPIO 25

// You can find out the address of your sensor by running ds18x20_multi example
#define DS18X20_ADDR0   0x2b3c02f648778a28

void onebus_ds18b20_init(void);
void onebus_ds18b20_read(void);

#ifdef __cplusplus
}
#endif

#endif