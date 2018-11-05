/*
*/
#include "stm32f0xx_hal.h"
#include "stdlib.h"

#define TRUE			1
#define FALSE			0
#define I2C_GPIO	GPIOA
#define I2C_SCL		GPIO_PIN_1
#define I2C_SDA		GPIO_PIN_0

#define SCL_H			(I2C_GPIO->BSRR 	= I2C_SCL)
#define SCL_L			(I2C_GPIO->BRR 		= I2C_SCL)
#define	SDA_H			(I2C_GPIO->BSRR		= I2C_SDA)
#define SDA_L			(I2C_GPIO->BRR		= I2C_SDA)
#define	SCL_READ 	(I2C_GPIO-IDR 		& I2C_SCL)
#define SDA_READ 	(I2C_GPIO->IDR 		& I2C_SDA)
 
#define I2C_PageSize 8
 
void I2C_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/*Configure I2C1 Pins:SCL and SDA*/
	GPIO_InitStructure.Pin = GPIO_PIN_6 |GPIO_PIN_7;
	GPIO_InitStructure.Speed =GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
	HAL_GPIO_Init(GPIOB,&GPIO_InitStructure);
}
 
void I2C_delay(void)
{
	uint8_t i=100; //设置通信速度
	
	while(i)
	{
		i--;
	}	
}

int  I2C_START(void)
{
	SDA_H;
	SCL_H;
	I2C_delay();
	if(!SDA_READ) return FALSE;  //SDA线为低电平总线忙，退出
	
	SDA_L;
	I2C_delay();
	if(SDA_READ) return FALSE; //SDA线为高电平则总线出错，退出
	
	SDA_L;
	I2C_delay();
	return TRUE;
}
 
void I2C_STOP(void)
{
	SCL_L;
	I2C_delay();
	SDA_L;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SDA_H;
	I2C_delay();	
}
 
void I2C_Ack(void)
{
	SCL_L;
	I2C_delay();
	SDA_L;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();	
}
 
void I2C_NoAck(void)
{
	SCL_L;
	I2C_delay();
	SDA_H;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
}
 
int  I2C_WaitAck(void)  //返回为：-1有ACK， =0 无ACK
{
	SCL_L;
	I2C_delay();
	SDA_H;
	I2C_delay();
	SCL_H;
	I2C_delay();
	if(SDA_READ)
	{
		SCL_L;
		return FALSE;
	}
	SCL_L;
	return TRUE;
	
}
 
void I2C_SendByte(uint8_t SendByte) //数据从高位到低位
{
	uint8_t i=8;
	while(i--)
	{
		SCL_L;
		I2C_delay();
		if(SendByte & 0x80)
			SDA_H;
		else
			SDA_L;
		SendByte <<= 1;
		I2C_delay();
		SCL_H;
		I2C_delay();
		
	}
	SCL_L;	
}

uint8_t I2C_ReceiveByte(void) //数据从高位到低位
{
	uint8_t i=8;
	uint8_t ReceiveByte = 0;
	
	SDA_H;
	while(i--)
	{
		ReceiveByte <<= 1;
		SCL_L;
		I2C_delay();
		SCL_H;
		I2C_delay();
		if(SDA_READ)
		{
			ReceiveByte|=0x01;
		}		
	}
	SCL_L;
	return ReceiveByte;		
}

int  I2C_WirteByte(uint8_t addr, uint8_t data)
{
	if(!I2C_START()) return FALSE;
	
	I2C_SendByte(addr);	//器件地址
	
	if(!I2C_WaitAck())
	{		
		I2C_STOP();
		return FALSE;
	}
	I2C_SendByte(data); //数据
	I2C_WaitAck();
	I2C_STOP();
	return TRUE;
}