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
	printf("I2C LCD Init\n");
    st7032_i2c_config();
    st7032_i2c_setCursor(1,0);
    st7032_i2c_write_str("Hello world");
}

void display_handler(void  )
{
    led_handler();
    lcd_handler();
}