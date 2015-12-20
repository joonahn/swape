#include <stdio.h>
#include <string.h>
#include <s3c_uart.h>
#include <lcd.h>
#include <interrupt.h>
#include <timer.h>

static void mango_hw_init(void)
{
  mango_uart_init(1, 115200);
  mango_interrupt_init();
  mango_lcd_init();
  mango_timer_init();
}

int main()
{
  char ch;
  mango_hw_init();

  while(1){
    ch = getchar();
    switch(ch){
      case '1':
        enable_interrupts();
        printf ("interrupt enabled\n");
        break;
      case '2':
        disable_interrupts();          
        printf ("interrupt disabled\n");
        break;
      case 'q':
        interrupt_reset();
        return 0;
      default:
        printf ("Invalid button\n");
    }
  }

  return 0;
}

