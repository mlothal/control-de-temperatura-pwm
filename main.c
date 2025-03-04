#include <16f876a.h>    // Pic a utilizar
#fuses xt,nowdt,noput,nobrownout,nolvp,noprotect   // Fusibles
#device ADC=10                         // Usa resolución de 10 bits
#use delay(clock=4M)       // Cristal a utilizar
#define LCD_DATA_PORT getenv("SFR:PORTB")   //definicion de puerto de salida al lcd
#include <lcd.c>             // Libreria para utilizar LCD por el puerto D

void main (void)
{

long  lec;
long  temp;
int pwm;
lcd_init();  

setup_timer_2(T2_DIV_BY_16,255,1);
setup_ccp1(CCP_PWM);
setup_adc(ADC_CLOCK_INTERNAL);
setup_adc_ports(AN0);
set_adc_channel(0);
delay_ms(1000);
while (true){
 lec=read_adc();
 temp=((0.4877*lec)-0.0999);
 lcd_putc("\f");
 lcd_gotoxy(2,1);
lcd_putc(" Temperatura\n");  
lcd_putc("actual");                      // Saca texto
lcd_gotoxy(13,2);                       // Acomoda cursor LCD
lcd_putc("oC");
 lcd_gotoxy(8,2);
 printf(lcd_putc,"%ld",temp);
 set_pwm1_duty(0);
 delay_ms(1000);
if ( temp>=20 && temp <= 150 )
{
 lec=read_adc();
 temp=((0.4877*lec)-0.0999);
  lcd_putc("\f");
 lcd_gotoxy(2,1);
lcd_putc(" Temperatura\n");  
lcd_putc("actual");                      // Saca texto
lcd_gotoxy(13,2);                       // Acomoda cursor LCD
lcd_putc("oC");
  lcd_gotoxy(8,2);
 printf(lcd_putc,"%ld",temp);
 pwm=((1.9615*temp)-39.231);
 set_pwm1_duty(pwm);
 delay_ms(1000);
}
}
}
