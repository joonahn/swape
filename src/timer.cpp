#include <stdio.h>
#include <stdlib.h>

#include <s3c_uart.h>
#include <s3c6410.h>
#include "frame.h"
#include "controller.h"

#define VIC0IRQSTATUS_REG __REG(ELFIN_VIC0_BASE_ADDR + 0x0)
#define VIC0INTSELECT_REG __REG(ELFIN_VIC0_BASE_ADDR + 0xc)
#define VIC0INTENABLE_REG __REG(ELFIN_VIC0_BASE_ADDR + 0x10)
#define VIC0INTENCLEAR_REG __REG(ELFIN_VIC0_BASE_ADDR + 0x14)

#define VIC0VECTADDR24 __REG(ELFIN_VIC0_BASE_ADDR + 0x160)
#define VIC0VECTADDR25 __REG(ELFIN_VIC0_BASE_ADDR + 0x164)
#define VIC0VECTADDR27 __REG(ELFIN_VIC0_BASE_ADDR + 0x16C)
#define VIC0VECTADDR28 __REG(ELFIN_VIC0_BASE_ADDR + 0x170)

#define BIT_TIMER1 (1<<24)
#define BIT_TIMER2 (1<<25)
#define BIT_TIMER3 (1<<27)
#define BIT_TIMER4 (1<<28)

#define TINT_CSTAT_REG __REG(0x7f006044)
#define BIT_TIMER1_STAT (1<<6)
#define BIT_TIMER2_STAT (1<<7)
#define BIT_TIMER3_STAT (1<<8)
#define BIT_TIMER4_STAT (1<<9)


#define BIT_TIMER1_EN (1<<1)
#define BIT_TIMER2_EN (1<<2)
#define BIT_TIMER3_EN (1<<3)
#define BIT_TIMER4_EN (1<<4)

extern Controller* controller;

//Interrupt Service Routine for Timer1
void timer2InterruptServiceRoutine(void){
  unsigned int temp;

  //Disable any other interrupt
  temp = VIC0INTENABLE_REG;
  VIC0INTENCLEAR_REG = 0xffffffff;

  // printf ("timer2InterruptSeviceRoutine is called %d times\n", timer1_isr_call_count);

  frame_service();

  //Reset interrupt status
  TINT_CSTAT_REG |= BIT_TIMER2_STAT;
  VIC0IRQSTATUS_REG |= BIT_TIMER2;

  //Enable other interrupts
  VIC0INTENABLE_REG = temp;


}

void timer3InterruptServiceRoutine(void){
  unsigned int temp;

  //Disable any other interrupt
  temp = VIC0INTENABLE_REG;
  VIC0INTENCLEAR_REG = 0xffffffff;

  //printf ("timer2InterruptSeviceRoutine is called %d times\n", timer1_isr_call_count);
  controller->eachTime();


  //Reset interrupt status
  TINT_CSTAT_REG |= BIT_TIMER3_STAT;
  VIC0IRQSTATUS_REG |= BIT_TIMER3;


  //Enable other interrupts
  VIC0INTENABLE_REG = temp;

}

void mango_timer_init(void){
  int i;
  /******TIMER2 *******/
  // Use Timer 2 as Frame timer
  TCFG0_REG = (TCFG0_REG & ~(0xff00)) | (0xff<<8); //Prescaler 1: 0xff - 256
  TCFG1_REG = (TCFG1_REG & ~(0xf<<12)) | (1<<14); //divider MUX2 : 1/16

  //One interrupt per one second
  TCNTB2_REG = 125;

  //Timer2 Manual update
  TCON_REG |= (1<<13); 
  //Timer2 Auto-reload on & Timer2 on
  TCON_REG = (TCON_REG & ~(0xf<<12)) | (1<<15) | (1<<12);
  

  //Enable interrupt for timer2
  VIC0INTENABLE_REG |= BIT_TIMER2;
  TINT_CSTAT_REG |= BIT_TIMER2_EN;

  //Set address of interrupt handler for timer1
  VIC0VECTADDR25 = (unsigned)timer2InterruptServiceRoutine;

}

void timer3_on()
{
  /******TIMER3 *******/
  //One interrupt per one second
  TCNTB3_REG = 3200;

  //Timer3 Manual update
  TCON_REG |= (1<<17); 
  //Timer3 Auto-reload on & Timer2 on
  TCON_REG = (TCON_REG & ~(0xf<<16)) | (1<<19) | (1<<16);
  

  //Enable interrupt for timer3
  VIC0INTENABLE_REG |= BIT_TIMER3;
  TINT_CSTAT_REG |= BIT_TIMER3_EN;

  //Set address of interrupt handler for timer3
  VIC0VECTADDR27 = (unsigned)timer3InterruptServiceRoutine;
}

void timer3_off()
{
  VIC0INTENABLE_REG &= ~(BIT_TIMER3);
  TINT_CSTAT_REG &= ~(BIT_TIMER3_EN);
  VIC0VECTADDR27 = 0;
}

void interrupt_reset(void){
  VIC0INTENABLE_REG &= ~(BIT_TIMER2);
  TINT_CSTAT_REG &= ~(BIT_TIMER2_EN);
  VIC0VECTADDR25 = 0;
}