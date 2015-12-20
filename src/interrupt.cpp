#include <stdio.h>

#include "lcd.h"
#include "s3c_uart.h"
#include "s3c6410.h"
#include "controller.h"

/* Registers for timer interrupt */
#define VIC0IRQSTATUS_REG __REG(ELFIN_VIC0_BASE_ADDR + 0x0)
#define VIC0INTSELECT_REG __REG(ELFIN_VIC0_BASE_ADDR + 0xc)
#define VIC0INTENABLE_REG __REG(ELFIN_VIC0_BASE_ADDR + 0x10)
#define VIC0INTENCLEAR_REG __REG(ELFIN_VIC0_BASE_ADDR + 0x14)

#define VIC0VECTADDR24 __REG(ELFIN_VIC0_BASE_ADDR + 0x160)

#define BIT_TIMER1 (1<<24)
#define TINT_CSTAT_REG __REG(0x7f006044)
#define BIT_TIMER1_STAT (1<<6)
#define BIT_TIMER1_EN (1<<1)

/* Registers for touch interrupt  */
#define VIC1RAWINTR_REG __REG(ELFIN_VIC1_BASE_ADDR + 0x8)
#define VIC1IRQSTATUS_REG __REG(ELFIN_VIC1_BASE_ADDR + 0x0)
#define VIC1INTSELECT_REG __REG(ELFIN_VIC1_BASE_ADDR + 0xc)
#define VIC1INTENABLE_REG __REG(ELFIN_VIC1_BASE_ADDR + 0x10)
#define VIC1INTENCLEAR_REG __REG(ELFIN_VIC1_BASE_ADDR + 0x14)

#define VIC1VECTADDR30 __REG(ELFIN_VIC1_BASE_ADDR + 0x178)
#define VIC1VECTADDR31 __REG(ELFIN_VIC1_BASE_ADDR + 0x17c)

#define BIT_ADCEOC (1<<31)
#define BIT_ADC_PEN (1<<30)

extern Controller * controller;

/* enable interrupt in CPU level */
void enable_interrupts(void){
  __asm__ __volatile__ ("mrs r0, cpsr");
  __asm__ __volatile__ ("bic r0, r0, #0x80");
  __asm__ __volatile__ ("msr cpsr_c, r0");
}

/* disable interrupt in CPU level */
void disable_interrupts(void){
  __asm__ __volatile__ ("mrs r0, cpsr");
  __asm__ __volatile__ ("orr r0, r0, #0x80");
  __asm__ __volatile__ ("msr cpsr_c, r0");
}

void touchInterruptServiceRoutine(void){
  unsigned int temp;
  unsigned int temp2;

  if( !(VIC1RAWINTR_REG & 1<<30) )
    return;

  /* Disable any other interrupt */
  temp = VIC1INTENABLE_REG;
  VIC1INTENCLEAR_REG = 0xffffffff;

  temp2 = readl(ADCCON);
  temp2 |= 1;
  writel(temp2, ADCCON);
  writel(0xd4, ADCTSC);

  //printf ("Touch Detected\t");

  writel(0x1, ADCCLRINTPNDNUP);

  /* Enable other interrupts */
  VIC1INTENABLE_REG = temp;
}

void touchInterruptServiceRoutine2(void){
  unsigned int temp;
  unsigned int x, y;
  unsigned int i, j;

  if( !(VIC1RAWINTR_REG & 1<<31) )
    return;

  /* Disable any other interrupt */
  temp = VIC1INTENABLE_REG;
  VIC1INTENCLEAR_REG = 0xffffffff;

  while( !(readl(ADCCON) & 1<<15) );
  
  x = readl(ADCDAT0) & 0x3ff;
  y = readl(ADCDAT1) & 0x3ff;
  
  //printf ("x: %d y: %d\n", x, y);

  /* Change to the device coordinate */
  //drawing((x-210)*1.27, (y-325)*1.33);
  if(controller)
    controller->touchHandler((x-210)*1.27, (y-325)*1.33);
 
  writel(0xd3, ADCTSC);
  writel(0x1, ADCCLRINT);
        
  /* Enable other interrupts */
  VIC1INTENABLE_REG = temp;
}

void mango_interrupt_init(void){
  VIC1INTENABLE_REG |= BIT_ADCEOC;
  VIC1INTENABLE_REG |= BIT_ADC_PEN;

  writel(0xffff, ADCDLY);
  writel(0xd3, ADCTSC);
  writel(0x7fc1, ADCCON); 

  VIC1VECTADDR30 = (unsigned)touchInterruptServiceRoutine;
  VIC1VECTADDR31 = (unsigned)touchInterruptServiceRoutine2;
}

