#ifndef LCD_I2C_HD44780_H_
#define LCD_I2C_HD44780_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f3xx_hal.h"
#include <stdint.h>

#define ENABLE_SET()	 LCD_Write_I2C_LCD(portlcd |= 0x04)
#define ENABLE_RESET()	 LCD_Write_I2C_LCD(portlcd &=~ 0x04)
#define RS_SET()		 LCD_Write_I2C_LCD(portlcd |= 0x01)
#define RS_RESET()		 LCD_Write_I2C_LCD(portlcd &=~ 0x01)
#define LED_SET()		 LCD_Write_I2C_LCD(portlcd |= 0x08)
#define WRITE_SET()		 LCD_Write_I2C_LCD(portlcd &=~ 0x02)

#define HD44780_CLEAR					 0x01

#define HD44780_HOME			         0x02

#define HD44780_ENTRY_MODE				 0x04
	#define HD44780_EM_SHIFT_CURSOR		 	0
	#define HD44780_EM_SHIFT_DISPLAY	 	1
	#define HD44780_EM_DECREMENT		   	0
	#define HD44780_EM_INCREMENT		   	2

#define HD44780_DISPLAY_ONOFF			   0x08
	#define HD44780_DISPLAY_OFF		     	0
	#define HD44780_DISPLAY_ON			   	4
	#define HD44780_CURSOR_OFF			   	0
	#define HD44780_CURSOR_ON			    2
	#define HD44780_CURSOR_NOBLINK	   		0
	#define HD44780_CURSOR_BLINK			1

#define HD44780_DISPLAY_CURSOR_SHIFT 0x10
	#define HD44780_SHIFT_CURSOR		   0
	#define HD44780_SHIFT_DISPLAY		   8
	#define HD44780_SHIFT_LEFT			   0
	#define HD44780_SHIFT_RIGHT		     4

#define HD44780_FUNCTION_SET			   0x20
	#define HD44780_FONT5x7				     0
	#define HD44780_FONT5x10			     4
	#define HD44780_ONE_LINE			     0
	#define HD44780_TWO_LINE			     8
	#define HD44780_4_BIT				       0
	#define HD44780_8_BIT				       16

#define HD44780_CGRAM_SET				     0x40

#define HD44780_DDRAM_SET				     0x80

void LCD_Init(void);
void LCD_Clear(void);
void LCD_Send_Char(char ch);
void LCD_Send_String (char* st);
void LCD_Set_Position(uint8_t x, uint8_t y);
void LCD_Send_Str_Pos(char* st, uint8_t x, uint8_t y);

#ifdef __cplusplus
}
#endif

#endif /* LCD_I2C_HD44780_H_ */
