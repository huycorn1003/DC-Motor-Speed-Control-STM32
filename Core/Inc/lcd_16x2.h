#ifndef __LCD_16X2_H__
#define __LCD_16X2_H__

#include "stm32f1xx_hal.h"
#include "string.h"

/* LCD PIN CONFIG */
#define RS_Pin GPIO_PIN_13
#define RS_GPIO_Port GPIOC

#define EN_Pin GPIO_PIN_15
#define EN_GPIO_Port GPIOC

#define RW_Pin GPIO_PIN_14
#define RW_GPIO_Port GPIOC

#define D4_Pin GPIO_PIN_12
#define D4_GPIO_Port GPIOB

#define D5_Pin GPIO_PIN_13
#define D5_GPIO_Port GPIOB

#define D6_Pin GPIO_PIN_14
#define D6_GPIO_Port GPIOB

#define D7_Pin GPIO_PIN_15
#define D7_GPIO_Port GPIOB


/* LCD CONFIG */
#define LCD_MODE LCD_4_BIT_MODE

#define SET_CGRAM_ADDRESS 0x40

#define LINES 2

#define START_LINE_1 0x00
#define START_LINE_2 0x40

#define SET_DDRAM_ADDRESS 0x80


/* COMMANDS */
#define CLEAR_DISPLAY 0x01
#define RETURN_HOME 0x02

#define ENTRY_MODE_SET 0x04
#define OPT_S 0x01
#define OPT_INC 0x02

#define DISPLAY_ON_OFF_CONTROL 0x08
#define OPT_D 0x04
#define OPT_C 0x02
#define OPT_B 0x01

#define CURSOR_DISPLAY_SHIFT 0x10
#define OPT_SC 0x08
#define OPT_RL 0x04

#define FUNCTION_SET 0x20
#define OPT_DL 0x10
#define OPT_N 0x08
#define OPT_F 0x04

#define SET_DDRAM_ADDR 0x80


/* FUNCTIONS */
void Lcd_Init(void);
void Lcd_clear_xy(uint8_t x,uint8_t y);
void Lcd_write_custom_char(uint8_t x, uint8_t y, uint8_t location);
void Lcd_gotoxy(uint8_t x, uint8_t y);
void Lcd_create_custom_char(uint8_t location, uint8_t* data_bytes);
void Lcd_clear_display(void);
void Lcd_write_string(char * string);
void Lcd_write_int(int number);

#endif
