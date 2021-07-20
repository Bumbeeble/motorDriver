#include "display.h"
void display_init(void )
{
    
    I2C_GPIOInit();
}

//Run every 1ms
void led_handler(void )
{
    
}

void lcd_handler(void )
{
#if 0
	printf("I2C LCD Init\n");
    st7032_i2c_config();
    st7032_i2c_setCursor(1,0);
    st7032_i2c_write_str("Hello world");
    
    
    st7032_i2c_setCursor(0,0);
    sprintf(char_buf, "PPM:%04U ",ppm_in[0].result);
    st7032_i2c_write_str(char_buf);
    st7032_i2c_setCursor(1,0);
    sprintf(char_buf, "AIN:%04U ",voltage_Vin);
    st7032_i2c_write_str(char_buf);
#endif
    
    
}

void display_handler(void  )
{
    led_handler();
    lcd_handler();
}