#include "stm32f0xx_hal.h"
#include "gpio-i2c.h"

#define SSD1316_ADDR 0x7a

void Write_Command(uint8_t cmd){
	uint8_t txbuf[3];
	txbuf[0] = SSD1316_ADDR;
	txbuf[1] = 0x00;
	txbuf[2] = cmd;
	I2C_SendBuf(txbuf, 3, I2C_FLAG_START|I2C_FLAG_STOP);
}

void Write_Data(uint8_t *data, int len){
	uint8_t txbuf[2];
	txbuf[0] = SSD1316_ADDR;
	txbuf[1] = 0x40;
	I2C_SendBuf(txbuf, 3, I2C_FLAG_START);
	I2C_SendBuf(data, len, I2C_FLAG_STOP);
}

void SSD1316_Clear(void){
	int  page;
	uint8_t data[128] = {0};
	for(page=0;page<8;page++)
	{
		Write_Command(0xb0+page);		//page0-page1
		Write_Command(0x00);		//low column start address
		Write_Command(0x10);		//high column start address
		Write_Data(data,sizeof(data));
	}
}

void SSD1316_Init(void) 
{ 
  Write_Command(0xAE);      // Set Display Off 
	Write_Command(0xD5);      // Display divide ratio/osc. freq. mode 
	Write_Command(0xC1);      // 115HZ 
	Write_Command(0xA8);      // Multiplex ration mode: 
	Write_Command(0x1F); 
	Write_Command(0xAD);      // External or Internal VCOMH/ IREF Selection 
	Write_Command(0x00);      // Internal VCOMH/ External IREF 
	Write_Command(0x20);  		// Set Memory Addressing Mode 
	Write_Command(0x02);      // Page Addressing Mode 
	Write_Command(0xD3);      // Set Display Offset       
	Write_Command(0x00); 
	Write_Command(0x40);      // Set Display Start Line 
	Write_Command(0x8D);      // DC-DC Control Mode Set 
	Write_Command(0x14);      // DC-DC ON Mode Set   
	Write_Command(0xA0);      // Segment Remap     
	Write_Command(0xC8);      // Set COM Output Scan Direction 
	Write_Command(0xDA);      // Seg pads hardware: alternative 
	Write_Command(0x12); 
	Write_Command(0x81);      // Contrast control 
	Write_Command(0x53); 
	Write_Command(0xD9);      // Set pre-charge period    
	Write_Command(0x22); 
	Write_Command(0xDB);      // VCOMH deselect level mode 
	Write_Command(0x00); 
	Write_Command(0xA4);      // Set Entire Display On/Off 
	Write_Command(0xA6);      // Set Normal Display   
	SSD1316_Clear(); 
	Write_Command(0xAF);      // Set Display On 
} 
