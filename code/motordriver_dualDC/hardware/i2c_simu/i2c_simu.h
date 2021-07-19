#ifndef __I2C_SIMU_H
#define	__I2C_SIMU_H

#include "define.h"
#include "delay.h"

#define IIC_DEBUG	1

sbit	I2C_SCK = P0^7;
#define I2C_SCK_config()    do{I2C_SCK = 0;P06_OpenDrain_Mode;}while(0)

sbit	I2C_SDA = P0^6;
#define I2C_SDA_config()    do{I2C_SDA = 0;P07_OpenDrain_Mode;}while(0)
//
#define I2C_SCK_H         do{I2C_SCK = 1;}while(0)//GPIO_SetBits(GPIOB,GPIO_Pin_6)
#define I2C_SCK_L         do{I2C_SCK = 0;}while(0)//GPIO_ResetBits(GPIOB,GPIO_Pin_6)
   
#define I2C_SDA_H         do{I2C_SDA = 1;}while(0)//GPIO_SetBits(GPIOB,GPIO_Pin_7)
#define I2C_SDA_L         do{I2C_SDA = 0;}while(0)//GPIO_ResetBits(GPIOB,GPIO_Pin_7)

#define I2C_SCL_read      (I2C_SCK)
#define I2C_SDA_read      (I2C_SDA)

void I2C_GPIOInit(void);
void I2C_delay(void);
bool I2C_Start(void);
void I2C_Stop(void);
void I2C_Ack(void);
void I2C_NoAck(void);
void I2C_WaitAck(void);
void I2C_SendByte(u8 SendByte);
unsigned char I2C_ReadByte(void);


#endif