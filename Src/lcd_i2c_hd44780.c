#include "lcd_i2c_hd44780.h"

uint8_t buf[1] = {0};
extern I2C_HandleTypeDef hi2c1;
char strl[100];
uint8_t portlcd; //

static void Priv_Send_Halfbyte(uint8_t c);
static void Priv_Send_Byte(uint8_t c, uint8_t mode);
static inline void DELAY_MICRSECOND(__IO uint32_t micros);
static void LCD_Write_I2C_LCD(uint8_t bt);

void LCD_Init(void)
{
	uint8_t i=0;

	//Wybranie trybu czterobitowego dane wysylane cztery razy
	HAL_Delay(100);
	for(i=0;i<3;i++)
	{
		Priv_Send_Halfbyte(0x03);
		HAL_Delay(45);
	}

	//Wlaczenie trybu czterobitowego
	Priv_Send_Halfbyte(0x02);
	HAL_Delay(100);

	Priv_Send_Byte(HD44780_FUNCTION_SET | HD44780_FONT5x7 | HD44780_TWO_LINE | HD44780_4_BIT,0);
	HAL_Delay(1);

	Priv_Send_Byte(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_OFF,0);
	HAL_Delay(1);

	Priv_Send_Byte(HD44780_ENTRY_MODE | HD44780_EM_SHIFT_CURSOR | HD44780_EM_INCREMENT,0);
	HAL_Delay(1);

	Priv_Send_Byte(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_OFF | HD44780_CURSOR_NOBLINK,0);
	HAL_Delay(1);

	LED_SET();
	WRITE_SET();

	LCD_Clear();
}

void LCD_Clear(void)
{
	Priv_Send_Byte(0x01,0);
	HAL_Delay(1000);
}

void LCD_Send_Char(char ch)
{
	Priv_Send_Byte(ch,1);
}

void LCD_Send_String(char* st)
{
	uint8_t i=0;
	while(st[i] != 0)
	{
		Priv_Send_Byte(st[i],1);
		i++;
	}
}

void LCD_Send_Str_Pos(char* st, uint8_t x, uint8_t y)
{
	LCD_Set_Position(x,y);
	LCD_Send_String(st);
}

void LCD_Set_Position(uint8_t x, uint8_t y)
{
    switch(y)
    {
        case 0:
        	Priv_Send_Byte(x|0x80,0);
            HAL_Delay(1);
            break;
        case 1:
        	Priv_Send_Byte((0x40+x)|0x80,0);
            HAL_Delay(1);
            break;
    }
}

static void Priv_Send_Halfbyte(uint8_t c)
{
        c<<=4;
        ENABLE_SET();
        DELAY_MICRSECOND(50);
        LCD_Write_I2C_LCD(portlcd|c);
        ENABLE_RESET();
        DELAY_MICRSECOND(50);
}

static void Priv_Send_Byte(uint8_t c, uint8_t mode)
{
    uint8_t hc=0;

    if (mode==0)
    {
       	RS_RESET();
    }
    else
    {
      	RS_SET();
    }
    hc=c>>4;

    Priv_Send_Halfbyte(hc);
    Priv_Send_Halfbyte(c);
}

static inline void DELAY_MICRSECOND(__IO uint32_t micros)
{
	micros *= (SystemCoreClock / 1000000) / 5;
}

static void LCD_Write_I2C_LCD(uint8_t bt)
{
	buf[0] = bt;
	HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)0x4E, buf, 1, 1000);
}
