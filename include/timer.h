#include <s3c_uart.h>
#include <s3c6410.h>


void enable_interrupts();
void disable_interrupts();

void timer1InterruptServiceRoutine();
void mango_timer_init();
void interrupt_reset();