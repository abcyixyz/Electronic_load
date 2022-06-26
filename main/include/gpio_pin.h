#ifndef __GPIO_PIN_H_
#define __GPIO_PIN_H_

#ifdef __cplusplus
extern "C" {
#endif

//io input
#define ENCORD_A_GPIO   GPIO_NUM_36     //要定义为输入的的io编号
#define ENCORD_B_GPIO   GPIO_NUM_39
#define ENCORD_K_GPIO   GPIO_NUM_34

//io output
#define V_SWITCH_GPIO           GPIO_NUM_23
#define GPIO_OUTPUT_PIN_SEL     (1ULL<<V_SWITCH_GPIO)

extern int32_t encoder_val;

void encoder_pin_init(void);
void encoder_key_read(void);

void voltage_pin_init(void);
void voltage_pin_write(uint32_t level);

#ifdef __cplusplus
}
#endif

#endif