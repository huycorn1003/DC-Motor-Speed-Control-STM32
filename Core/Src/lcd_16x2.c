#include "lcd_16x2.h"
#include <stdio.h>
/* Private functions */

static void LCD_Enable(void)
{
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
    HAL_Delay(1);
}

static void LCD_Send4Bit(uint8_t data)
{
    HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, (data >> 0) & 0x01);
    HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, (data >> 1) & 0x01);
    HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, (data >> 2) & 0x01);
    HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, (data >> 3) & 0x01);

    LCD_Enable();
}

static void LCD_SendCommand(uint8_t cmd)
{
    HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);

    LCD_Send4Bit(cmd >> 4);
    LCD_Send4Bit(cmd & 0x0F);

    HAL_Delay(2);
}

static void LCD_SendData(uint8_t data)
{
    HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);

    LCD_Send4Bit(data >> 4);
    LCD_Send4Bit(data & 0x0F);

    HAL_Delay(1);
}

/* Public functions */

void Lcd_Init(void)
{
    HAL_Delay(50);

    HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);

    LCD_Send4Bit(0x03);
    HAL_Delay(5);

    LCD_Send4Bit(0x03);
    HAL_Delay(1);

    LCD_Send4Bit(0x03);
    HAL_Delay(1);

    LCD_Send4Bit(0x02);

    LCD_SendCommand(0x28);
    LCD_SendCommand(0x0C);
    LCD_SendCommand(0x06);
    LCD_SendCommand(0x01);

    HAL_Delay(2);
}

void Lcd_clear_display(void)
{
    LCD_SendCommand(CLEAR_DISPLAY);
}

void Lcd_gotoxy(uint8_t x, uint8_t y)
{
    uint8_t address;

    if(y == 0)
        address = START_LINE_1 + x;
    else
        address = START_LINE_2 + x;

    LCD_SendCommand(SET_DDRAM_ADDR + address);
}

void Lcd_write_string(char * string)
{
    while(*string)
    {
        LCD_SendData(*string++);
    }
}

void Lcd_write_int(int number)
{
    char buffer[16];
    sprintf(buffer,"%d",number);
    Lcd_write_string(buffer);
}

void Lcd_clear_xy(uint8_t x,uint8_t y)
{
    Lcd_gotoxy(x,y);
    Lcd_write_string("                ");
}

void Lcd_write_custom_char(uint8_t x, uint8_t y, uint8_t location)
{
    Lcd_gotoxy(x,y);
    LCD_SendData(location);
}

void Lcd_create_custom_char(uint8_t location, uint8_t* data_bytes)
{
    location &= 0x7;
    LCD_SendCommand(SET_CGRAM_ADDRESS + (location<<3));

    for(int i=0;i<8;i++)
    {
        LCD_SendData(data_bytes[i]);
    }
}
