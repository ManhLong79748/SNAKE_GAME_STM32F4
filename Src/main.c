
#include<stdio.h>
#include "stdlib.h"
#include "stm32f4.h"
#include"stm32f4_gpio.h"
#include"stm32f4_i2c.h"
#include"systick.h"
#include"oled.h"
#include "stdbool.h"

#define MY_ADDR 0x61;

I2C_Handle_t I2C1Handle;

/*
 * PB8-> SCL
 * PB9-> SDA
 */


int draw_grid[16][8];
int snake_speed[2]={1,0};
int size_of_snake=2;
int snake_pos[2][20];
int old_poshx;
int old_poshy;
int pos_head[2];
bool sw_up = false;
bool sw_down = false;
bool sw_right = false;
bool sw_left = false;
int score;


void init_grid(void);
void update_grid(void);
void draw_snake(int x,int y);
void draw_food(int x,int y);
void clear_block(int x,int y);
void move_snake(void);
void re_init(void);
void spawn_food(void);
int rand_no(int m);
void check_collision(void);
void wait_check(void);
void check_food(void);
void game_over_screen(void);

void I2C1_GPIOInits(void)
{
	GPIO_Handle_t I2CPins;

	I2CPins.pGPIOx = GPIOB;
	I2CPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	I2CPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
	I2CPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	I2CPins.GPIO_PinConfig.GPIO_PinAltFunMode = 4;
	I2CPins. GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//scl
	I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_8;
	GPIO_Init(&I2CPins);

	//sda
	//Note : since we found a glitch on PB9 , you can also try with PB7
	I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;

	GPIO_Init(&I2CPins);

}

void I2C1_Inits(void)
{
	I2C1Handle.pI2Cx = I2C1;
	I2C1Handle.I2C_Config.I2C_AckControl = I2C_ACK_ENABLE;
	I2C1Handle.I2C_Config.I2C_DeviceAddress = MY_ADDR;
	I2C1Handle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;
	I2C1Handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM;

	I2C_Init(&I2C1Handle);
}

void GPIO_ButtonInit(void)
{
	GPIO_Handle_t GPIOBtnR;
	GPIOBtnR.pGPIOx = GPIOD;
	GPIOBtnR.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	GPIOBtnR.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIOBtnR.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBtnR.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	GPIO_Init(&GPIOBtnR);

	GPIO_Handle_t GPIOBtnL;
	GPIOBtnL.pGPIOx = GPIOD;
	GPIOBtnL.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;
	GPIOBtnL.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIOBtnL.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBtnL.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	GPIO_Init(&GPIOBtnL);

	GPIO_Handle_t GPIOBtnU;
	GPIOBtnU.pGPIOx = GPIOD;
	GPIOBtnU.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
	GPIOBtnU.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIOBtnU.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBtnU.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	GPIO_Init(&GPIOBtnU);

	GPIO_Handle_t GPIOBtnD;
	GPIOBtnD.pGPIOx = GPIOD;
	GPIOBtnD.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
	GPIOBtnD.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIOBtnD.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBtnD.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	GPIO_Init(&GPIOBtnD);
}

int main(void)
{
	GPIO_ButtonInit();
	//i2c pin inits
	I2C1_GPIOInits();
	//i2c peripheral configuration
	I2C1_Inits();
	//enable the i2c peripheral
	I2C_PeripheralControl(I2C1,ENABLE);
	systick_init();
	DelayMs(100);
	ssd1306_Init();

	init_grid();
	draw_grid[0][0]=2;
	draw_grid[1][0]=2;
	snake_pos[0][0]=0;
	snake_pos[1][0]=0;
	snake_pos[0][1]=1;
	snake_pos[1][1]=0;
	size_of_snake=2;
	snake_speed[0]=1;
	snake_speed[1]=0;
	sw_up=true;
	sw_down=true;
	sw_right=true;
	sw_left=true;
	score=0;
	spawn_food();

	while(1)
	{
		update_grid();
		check_food();
		move_snake();
		check_collision();
		wait_check();
	}
}

void draw_snake(int x,int y){
	int x0=x*8;
	int y0=y*8;
	int x1=x0+8;
	int y1=y0+8;
	for(int i=x0;i<x1;i++){
		for(int j=y0;j<y1;j++){
			ssd1306_DrawPixel(i,j,0x01);
		}
	}
}
void draw_food(int x,int y){
	int x0=x*8;
	int y0=y*8;
	int x1=x0+8;
	int y1=y0+8;
	for(int i=x0;i<x1;i++){
		for(int j=y0;j<y1;j++){
			ssd1306_DrawPixel(i,j,0x01);
		}
	}
}

void clear_block(int x,int y){
	int x0=x*8;
	int y0=y*8;
	int x1=x0+8;
	int y1=y0+8;
	for(int i=x0;i<x1;i++){
		for(int j=y0;j<y1;j++){
			ssd1306_DrawPixel(i,j,0x00);
		}
	}
}

void update_grid(){
	SSD1306_ClearScreen();
	for(int i=0;i<16;i++){
		for(int j=0;j<8;j++){
			if(draw_grid[i][j]==2){
				draw_snake(i,j);
			}
			else if(draw_grid[i][j]==1){
				draw_food(i,j);
			}
			else{
				clear_block(i,j);
			}
		}
	}
	ssd1306_UpdateScreen();
}

//Fill grid with 0
void init_grid(void){
	for(int i=0; i<16;i++){
		for(int j=0;j<8;j++){
			draw_grid[i][j]=0;
		}
	}
}

void move_snake(){
		for(int i=size_of_snake-1;i>=0;i--){
			draw_grid[snake_pos[0][i]][snake_pos[1][i]]=0;
		}
		old_poshx=snake_pos[0][size_of_snake-1];
		old_poshy=snake_pos[1][size_of_snake-1];
		snake_pos[0][size_of_snake-1]=snake_pos[0][size_of_snake-1]+snake_speed[0];
		snake_pos[1][size_of_snake-1]=snake_pos[1][size_of_snake-1]+snake_speed[1];
		pos_head[0]=snake_pos[0][size_of_snake-1];
		pos_head[1]=snake_pos[1][size_of_snake-1];
		for(int i=size_of_snake-2;i>=0;i--){
			int nx = snake_pos[0][i];
			int ny = snake_pos[1][i];
			snake_pos[0][i]=old_poshx;
			snake_pos[1][i]=old_poshy;
			old_poshx=nx;
			old_poshy=ny;
		}
		for(int i=size_of_snake-1;i>=0;i--){
			draw_grid[snake_pos[0][i]][snake_pos[1][i]]=2;
		}
}

void re_init(void){
	init_grid();
	draw_grid[0][0]=2;
	draw_grid[1][0]=2;
	snake_pos[0][0]=0;
	snake_pos[1][0]=0;
	snake_pos[0][1]=1;
	snake_pos[1][1]=0;
	size_of_snake=2;
	snake_speed[0]=1;
	snake_speed[1]=0;
	sw_up=true;
	sw_down=true;
	sw_right=true;
	sw_left=true;
	score=0;
	spawn_food();
}

void spawn_food(void){
	int xf=rand_no(15);
	int yf=rand_no(7);
	while(draw_grid[xf][yf]==2){
		xf=rand_no(15);
		yf=rand_no(7);
	}
	draw_grid[xf][yf]=1;
}

int rand_no(int m){
	int num = (rand()%(m+1));
	return num;
}

void check_collision(void){
	if(pos_head[0]>=16 || pos_head[0]<0){
		game_over_screen();
		re_init();
	}
	if(pos_head[1]>=8 || pos_head[1]<0){
		game_over_screen();
		re_init();
	}
	if(draw_grid[pos_head[0]+snake_speed[0]][pos_head[1]+snake_speed[1]]==2){
		game_over_screen();
		re_init();
	}
}

void wait_check(void){
	for(int i=0;i<45;i++){
		sw_down=GPIO_ReadFromInputPin(GPIOD,GPIO_PIN_NO_1);
		if(sw_down==false && snake_speed[1]==0){
			snake_speed[0]=0;
			snake_speed[1]=1;
			break;
		}
		sw_up=GPIO_ReadFromInputPin(GPIOD,GPIO_PIN_NO_3);
		if(sw_up==false && snake_speed[1]==0){
			snake_speed[0]=0;
			snake_speed[1]=-1;
			break;
		}
		sw_right=GPIO_ReadFromInputPin(GPIOD,GPIO_PIN_NO_0);
		if(sw_right==false && snake_speed[0]==0){
			snake_speed[0]=1;
			snake_speed[1]=0;
			break;
		}
		sw_left=GPIO_ReadFromInputPin(GPIOD,GPIO_PIN_NO_2);
		if(sw_left==false && snake_speed[0]==0){
			snake_speed[0]=-1;
			snake_speed[1]=0;
			break;
		}
		DelayMs(5);
	}
}
void check_food(void){
	if(draw_grid[pos_head[0]+snake_speed[0]][pos_head[1]+snake_speed[1]]==1){
		score++;
		size_of_snake++;
		snake_pos[0][size_of_snake-1]=pos_head[0]+snake_speed[0];
		snake_pos[1][size_of_snake-1]=pos_head[1]+snake_speed[1];
		spawn_food();
	}
}

void game_over_screen(void){
	SSD1306_ClearScreen();
	ssd1306_SetCursor(16,20);
	ssd1306_WriteString("Game Over", Font_11x18, 0x01);
	ssd1306_SetCursor(16,40);
	ssd1306_WriteString("Score: ", Font_11x18, 0x01);
	ssd1306_SetCursor(80,40);
	char sc1=score+'0';
	ssd1306_WriteChar(sc1, Font_11x18,0x01);
	ssd1306_UpdateScreen();
	DelayMs(1000);
}



