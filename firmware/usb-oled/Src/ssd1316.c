#include "stm32f0xx_hal.h"
#include "gpio-i2c.h"

#define SSD1316_ADDR 0x7a

void Write_Command(uint8_t data){
	I2C_WirteByte(SSD1316_ADDR, data);
}

void Init_IC(void) 
{ 
  Write_Command(0xAE);      // Set Display Off 
	Write_Command(0xD5);        // Display divide ratio/osc. freq. mode 
	Write_Command(0xC1);        // 115HZ 
	Write_Command(0xA8);      // Multiplex ration mode: 
	Write_Command(0x1F); 
	Write_Command(0xAD);      // External or Internal VCOMH/ IREF Selection 
	Write_Command(0x00);      // Internal VCOMH/ External IREF 
	Write_Command(0x20);  // Set Memory Addressing Mode 
	Write_Command(0x02);      // Page Addressing Mode 
	Write_Command(0xD3);        // Set Display Offset       
	Write_Command(0x00); 
	Write_Command(0x40);        // Set Display Start Line 
	Write_Command(0x8D);        // DC-DC Control Mode Set 
	Write_Command(0x14);        // DC-DC ON Mode Set   
	Write_Command(0xA0);        // Segment Remap     
	Write_Command(0xC8);        // Set COM Output Scan Direction 
	Write_Command(0xDA);        // Seg pads hardware: alternative 
	Write_Command(0x12); 
	Write_Command(0x81);      // Contrast control 
	Write_Command(0x53); 
	Write_Command(0xD9);      // Set pre-charge period    
	Write_Command(0x22); 
	Write_Command(0xDB);        // VCOMH deselect level mode 
	Write_Command(0x00); 
	Write_Command(0xA4);        // Set Entire Display On/Off 
	Write_Command(0xA6);        // Set Normal Display   
	//Clear_Screen(); 
	Write_Command(0xAF);        // Set Display On 
} 
