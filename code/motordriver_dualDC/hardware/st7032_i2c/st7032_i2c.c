#include "st7032_i2c.h"


uint8_t contrast = 0x33;//0x21;//        //0x00~0x3f
uint8_t displayOnOffSetting = (DISPLAY_ON_OFF | DISPLAY_ON_OFF_D);
void st7032_i2c_config(void )
{
//    pin_LCD_RST_config();
    
    //reset
//    LCD_RST_H();
//    Delay(50000);
//    LCD_RST_L();
//    Delay(50000);
//    LCD_RST_H();
    Delay(50000);
    printf("st7032_i2c reset\n");
    //
    st7032_i2c_write_cmd(FUNCTION_SET | FUNCTION_SET_DL | FUNCTION_SET_N | FUNCTION_SET_IS);
    printf("st7032_i2c set\n");
    st7032_i2c_write_cmd(INTERNAL_OSC_FREQ | INTERNAL_OSC_FREQ_BS | INTERNAL_OSC_FREQ_F2);
    st7032_i2c_write_cmd(POWER_ICON_BOST_CONTR | POWER_ICON_BOST_CONTR_Ion);
    st7032_i2c_setcontrast(contrast);
    st7032_i2c_write_cmd(FOLLOWER_CONTROL | FOLLOWER_CONTROL_Fon | FOLLOWER_CONTROL_Rab2);
    Delay(50000);
    st7032_i2c_write_cmd(displayOnOffSetting);
	st7032_i2c_write_cmd(ENTRY_MODE_SET | ENTRY_MODE_SET_ID);
    st7032_i2c_write_cmd(CLEAR_DISPLAY); 
    st7032_i2c_write_cmd(RETURN_HOME); 
}

void st7032_i2c_setCursor(uint8_t line, uint8_t pos) 
{
	uint8_t p;
	if(pos > 15) pos = 0;
	if(line == 0) p = LINE_1_ADR + pos;
	else p = LINE_2_ADR + pos;
	st7032_i2c_write_cmd(SET_DDRAM_ADDRESS | p);
}
void st7032_i2c_setcontrast(int val) 
{
	if (val > CONTRAST_MAX) val = CONTRAST_MIN;
	else if (val < CONTRAST_MIN) val = CONTRAST_MAX;
	st7032_i2c_write_cmd(CONTRAST_SET | (val & 0x0F));
	st7032_i2c_write_cmd((val >> 4) | POWER_ICON_BOST_CONTR | POWER_ICON_BOST_CONTR_Bon);
	contrast = val;
}
void st7032_i2c_write_cmd(uint8_t cmd)
{
    I2C_Start();
    I2C_SendByte(st7032_i2c_addr);      //write addr
    I2C_WaitAck();
    I2C_SendByte(CNTRBIT_CO);           //write cmd
    I2C_WaitAck();
    I2C_SendByte(cmd);                  //cmd
    I2C_WaitAck();
    I2C_Stop();
    
}

void st7032_i2c_write_data(uint8_t dataBuf)
{
    I2C_Start();
    I2C_SendByte(st7032_i2c_addr);      //write addr
    I2C_WaitAck();
    I2C_SendByte(CNTRBIT_RS);           //write cmd
    I2C_WaitAck();
    I2C_SendByte(dataBuf);                  //cmd
    I2C_WaitAck();
    I2C_Stop();
    
}
void st7032_i2c_write_str(char *strBuf)
{
    uint8_t i = 0;
    I2C_Start();
    I2C_SendByte(st7032_i2c_addr);      //write addr
    I2C_WaitAck();
    I2C_SendByte(CNTRBIT_RS);           //write data
    I2C_WaitAck();
    
    while(strBuf[i])
    {
        I2C_SendByte(strBuf[i]);                  //data
        I2C_WaitAck();
        i++;
    }
    
    I2C_Stop();
    
}
