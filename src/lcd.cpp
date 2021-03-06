#include <stdio.h>

#include "s3c_uart.h"
#include "s3c6410.h"
#include "lcd.h"
#include "frame.h"
#include "vic.h"

#define FIN 12000000
#define LCD_PWR_CON GPNCON_REG
#define LCD_PWR_DAT GPNDAT_REG
#define LCD_BL_CON  GPFCON_REG
#define LCD_BL_DAT  GPFDAT_REG
#define MAX_BL_LEV  0xFF

#define S3CFB_HFP       64   /* front porch */
#define S3CFB_HSW       128   /* hsync width */
#define S3CFB_HBP       16  /* back porch */

#define S3CFB_VFP       16   /* front porch */
#define S3CFB_VSW       1   /* vsync width */
#define S3CFB_VBP       16   /* back porch */

#define S3CFB_HRES      800 /* horizon pixel  x resolition */
#define S3CFB_VRES      480 /* line cnt       y resolution */
#define S3CFB_SIZE      (S3CFB_HRES*S3CFB_VRES)

#define S3CFB_HRES_VIRTUAL  800 /* horizon pixel  x resolition */
#define S3CFB_VRES_VIRTUAL  960 /* line cnt       y resolution */

#define S3CFB_HRES_OSD      800 /* horizon pixel  x resolition */
#define S3CFB_VRES_OSD      480 /* line cnt       y resolution */

#define S3CFB_VFRAME_FREQ       60  /* frame rate freq */

#define S3CFB_PIXEL_CLOCK   (S3CFB_VFRAME_FREQ * (S3CFB_HFP + S3CFB_HSW + S3CFB_HBP + S3CFB_HRES) * (S3CFB_VFP + S3CFB_VSW + S3CFB_VBP + S3CFB_VRES))

#define BYTE_PER_PIXEL 4
#define S3CFB_OFFSET ((S3CFB_HRES_VIRTUAL - S3CFB_HRES) * BYTE_PER_PIXEL)
#define PAGE_WIDTH  (S3CFB_HRES * BYTE_PER_PIXEL)

#define FB_ADDR     (unsigned int *)0x5a000000


void lcd_pwr_on(void){
  LCD_PWR_CON  = (LCD_PWR_CON & ~(3<<18)) | (1<<18);
  LCD_PWR_DAT  |= (1<<9);
}

void lcd_Pwr_off(void){
  LCD_PWR_DAT  &= ~(1<<9);
}

void lcd_bl_on(int level){
  LCD_BL_CON = (LCD_BL_CON & ~(3<<30)) | (2<<30); 

  // prescaler 0 (timer 0, 1) : 0xFF
  TCFG0_REG = (TCFG0_REG & ~(0xFF)) | 0xFF;
  // divider mux 1 : 1/16
  TCFG1_REG = (TCFG1_REG & ~(0xF<<4)) | (4<<4);

  //Initial TCNTB Value
  TCNTB1_REG = MAX_BL_LEV;

  //Setting PWM Duty
  if(level >= MAX_BL_LEV)
    TCMPB1_REG = MAX_BL_LEV-1;
  else
    TCMPB1_REG = level;
  
  // update TCNTB1, TCMPB1
  TCON_REG |= (1<<9);

  // Interval mode, Timer1 start
  TCON_REG = (TCON_REG & ~(0xF<<8)) | (1<<11) | (1<<8) ;
}

unsigned int get_hclk(void){
  unsigned int mpll, mdiv, pdiv, sdiv;
  unsigned int hclkx2, hclk;

  mdiv = (MPLL_CON_REG>> 16) & 0x3FF;
  pdiv = (MPLL_CON_REG>> 8)  & 0x3F;
  sdiv = (MPLL_CON_REG>> 0)  & 0x7;
  mpll = mdiv * FIN;
  mpll /= (pdiv * (1<<sdiv));

  hclkx2 = mpll / (((CLK_DIV0_REG & (0x7<<9)) >> 9) + 1);
  hclk = hclkx2 / (((CLK_DIV0_REG & (0x1<<8)) >> 8) + 1);

  printf("\nmpll : %d, hclkx2:%d, hclk:%d\n", mpll, hclkx2, hclk);

  return hclk;
}

void init_lcd_reg(void){
  printf("init start");
  unsigned int hclk = get_hclk();

  printf("VCLK : %d, CLKVAL:%dgg\n", S3CFB_PIXEL_CLOCK, (int)(hclk/S3CFB_PIXEL_CLOCK));

  printf("asd");
  HOSTIFB_MIFPCON_REG = 0x0;
  printf("EEEE");
  SPCON_REG &= (~0x3);
  SPCON_REG |= 0x1;


  GPICON_REG = 0xAAAAAAAA;
  GPJCON_REG = 0xAAAAAAAA;
  printf("init_lcd_reg mid");

  S3C_VIDCON0 = S3C_VIDCON0_VIDOUT_RGB_IF |
  S3C_VIDCON0_PNRMODE_BGR_P |
  S3C_VIDCON0_CLKVAL_F((int)(hclk/S3CFB_PIXEL_CLOCK)) |
  S3C_VIDCON0_CLKDIR_DIVIDED |
  S3C_VIDCON0_CLKSEL_F_HCLK;
  
  S3C_VIDCON1 = S3C_VIDCON1_IHSYNC_INVERT |
  S3C_VIDCON1_IVSYNC_INVERT |
  S3C_VIDCON1_IVDEN_NORMAL;
  
  S3C_VIDTCON0 = S3C_VIDTCON0_VBPD(S3CFB_VBP - 1) |
  S3C_VIDTCON0_VFPD(S3CFB_VFP - 1) |
  S3C_VIDTCON0_VSPW(S3CFB_VSW - 1);
  
  S3C_VIDTCON1 = S3C_VIDTCON1_HBPD(S3CFB_HBP - 1) |
  S3C_VIDTCON1_HFPD(S3CFB_HFP - 1) |
  S3C_VIDTCON1_HSPW(S3CFB_HSW - 1);
  
  S3C_VIDTCON2 = S3C_VIDTCON2_LINEVAL(S3CFB_VRES - 1) |
  S3C_VIDTCON2_HOZVAL(S3CFB_HRES - 1);
  
  S3C_WINCON0 = S3C_WINCONx_BUFSEL_0 |
  S3C_WINCONx_BUFAUTOEN_DISABLE |
  S3C_WINCONx_HAWSWP_DISABLE |
  S3C_WINCONx_BURSTLEN_4WORD |
  S3C_WINCONx_BPPMODE_F_24BPP_888;

  /* Buffer Address*/ 
  S3C_VIDW00ADD0B0 = (long unsigned int)FB_ADDR; 
  S3C_VIDW00ADD1B0 = (long unsigned int)S3C_VIDWxxADD1_VBASEL_F(FB_ADDR + 
    (PAGE_WIDTH + S3CFB_OFFSET) * S3CFB_VRES);
  S3C_VIDW00ADD2  = S3C_VIDWxxADD2_OFFSIZE_F(S3CFB_OFFSET) |
  S3C_VIDWxxADD2_PAGEWIDTH_F(PAGE_WIDTH);
  printf("init_lcd_reg last");
}

void set_wincon0_enable(void){
  S3C_WINCON0 |= S3C_WINCONx_ENWIN_F_ENABLE;
}

void set_vidcon0_enable(void){
  S3C_VIDCON0 |= (S3C_VIDCON0_ENVID_ENABLE |
    S3C_VIDCON0_ENVID_F_ENABLE);
}

void set_lcd_pos(int ltx, int lty, int rbx, int rby){
  S3C_VIDOSD0A = S3C_VIDOSDxA_OSD_LTX_F(ltx) |
  S3C_VIDOSDxA_OSD_LTY_F(lty);

  S3C_VIDOSD0B = S3C_VIDOSDxB_OSD_RBX_F(rbx- 1) |
  S3C_VIDOSDxB_OSD_RBY_F(rby- 1);
}

void drawing(int x, int y){
  unsigned int *phy_addr = FB_ADDR;
  int i, j;

}

void vsync_interrupt_service_routine(void) {
  static int serviced = 1;
  unsigned temp;

  temp = VIC0INTENABLE_REG;
  VIC0INTENCLEAR_REG = 0xffffffff;

  if (S3C_VIDINTCON1 | (1 << 1)) {
    frame_assert();
    S3C_VIDINTCON1 = 0x2;
  }
  serviced++;

  VIC0INTENABLE_REG = temp;
}

void mango_lcd_init(void){
  unsigned int i;
  unsigned int *phy_addr = FB_ADDR;

  lcd_bl_on(MAX_BL_LEV-1);
  printf("The bomb lcd_pwr_on");
  lcd_pwr_on();
  printf("init_lcd_reg");
  init_lcd_reg();

  printf("The bomb frame_init");
  frame_init();
  printf("oops! frame_init");
  //VSync Interrupt Setting
  S3C_VIDINTCON0 |= (3 << 15) | (1 << 12) | 1;
  VIC0INTENABLE_REG |= (1 << 30);
  VIC0VECTADDR30 = (unsigned)vsync_interrupt_service_routine;

  set_lcd_pos(0, 0, S3CFB_HRES, S3CFB_VRES);

  set_wincon0_enable();
  set_vidcon0_enable(); 

}
