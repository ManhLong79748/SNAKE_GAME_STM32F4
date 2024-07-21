
#ifndef INC_OLED_H_
#define INC_OLED_H_

#include "stm32f4_i2c.h"
#include "fonts.h"
#include "systick.h"


// I2c address
#define SSD1306_I2C_ADDR        0x78
// SSD1306 width in pixels
#define SSD1306_WIDTH           128
// SSD1306 LCD height in pixels
#define SSD1306_HEIGHT          64


//
//  Enumeration for screen colors
//
typedef enum {
	Black = 0x00, // Black color, no pixel
	White = 0x01  //Pixel is set. Color depends on LCD
} SSD1306_COLOR;

//
//  Struct to store transformations
//
typedef struct {
	uint16_t CurrentX;
	uint16_t CurrentY;
	uint8_t Inverted;
	uint8_t Initialized;
} SSD1306_t;

//	Definition of the i2c port in main
extern I2C_Handle_t I2C1Handle;

//
//  Function definitions
//
uint8_t ssd1306_Init(void);
void ssd1306_Fill(SSD1306_COLOR color);
void ssd1306_UpdateScreen(void);
void ssd1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color);
char ssd1306_WriteChar(char ch, FontDef Font, SSD1306_COLOR color);
char ssd1306_WriteString(char* str, FontDef Font, SSD1306_COLOR color);
void ssd1306_SetCursor(uint8_t x, uint8_t y);
void SSD1306_DrawBitmap(int16_t x, int16_t y, const unsigned char* bitmap, int16_t w, int16_t h, uint16_t color);
void SSD1306_ClearScreen();



#endif /* INC_OLED_H_ */
