#include <stdlib.h>
#include <stdio.h>
#include "frame.h"
#include "s3c6410.h"
#include "lcd.h"
#include "graphics.h"
#include "util.h"
#include "controller.h"
#include "jsg.h"

static int frame_asserted = 0;

static unsigned background[S3CFB_SIZE];

//vsync handling routines
//two frame buffers are serviced
//into lcd screen in an alternating manner
//to avoid tearing (strange vertical lines on the screen)
static unsigned fb_odd[S3CFB_SIZE];
static unsigned fb_even[S3CFB_SIZE];

static int imagew = 100;
static int imageh = 55;

//Global Image variable
Controller * controller = (Controller *)0;


int frame_is_asserted(void) {
	return frame_asserted;
}

void frame_set_fb(unsigned *fb) {
	unsigned ufb = (unsigned)fb;
	S3C_VIDW00ADD0B0 = ufb; 
	S3C_VIDW00ADD1B0 = (unsigned)S3C_VIDWxxADD1_VBASEL_F(ufb + 
		(PAGE_WIDTH + S3CFB_OFFSET) * S3CFB_VRES);
	S3C_VIDW00ADD2  = S3C_VIDWxxADD2_OFFSIZE_F(S3CFB_OFFSET) |
		S3C_VIDWxxADD2_PAGEWIDTH_F(PAGE_WIDTH);
}

void frame_init(void) {
	int i;
	  printf("frame init second line");
	for (i = 0; i < S3CFB_SIZE; i ++) {
		int x, y;

		x = i % S3CFB_HRES;
		y = i / S3CFB_HRES;

		background[i] = (((x >> 5) & 1) != ((y >> 5) & 1)) ? 0xFFFFFFFF : 0xFFD7D7D7;
		fb_odd[i] = background[i];
		fb_even[i] = background[i];
	}

	for (i = 0; i < imagew * imageh; i++) {
		int x, y, ds, limit;

		x = (i % imagew) - (imagew >> 1);
		y = (i / imagew) - (imageh >> 1);
		ds = x * x + y * y;
		limit = (imagew >> 1) * (imagew >> 1);

		// graphics2D also supports alpha value
		// but image data is previously has alpha value 0
		// which reside on MSB
		// outside of circle area remains with alpha value 0.
		if (ds < limit * 9 / 10)
			((unsigned *)jsg)[i] |= 0xFF000000;
		else if (ds < limit)
			((unsigned *)jsg)[i] = 0xFF303030;
		// ((unsigned *)ball)[i] |= 0xFF000000;
	}
	printf("I think this is the bomb");
	controller = new Controller(background);

	frame_set_fb(fb_even);
}

void frame_assert(void) {
	frame_asserted = 1;
}

static void implement_your_drawing_here(unsigned *fb);

void frame_service(void) {
	static int parity = 0;

	if (frame_asserted) {
		//it is guaranteed that it is asserted 60 times per sec
		//by lcd vsync timer interrupt
		unsigned *fb_shown;
		unsigned *fb_working;

		fb_shown = parity ? fb_odd : fb_even;
		fb_working = !parity ? fb_odd : fb_even;
		parity = !parity;

		//shows a framebuffer on screen
		frame_set_fb(fb_shown);
		//and working on the other frame buffer
		implement_your_drawing_here(fb_working);

		frame_asserted = 0;
	}
}

static void implement_your_drawing_here(unsigned *fb) {
	// static float pps = 1.0;
	// static float ppx = 0.0;
	// static float ppy = 0.0;

	// static float ps = 1.0;
	// static float px = 0.0;
	// static float py = 0.0;

	// static float s = 1.0;
	// static float x = 0.0;
	// static float y = 0.0;

	// static float phase = 0.0;

	// int x1, y1, x2, y2;

	// phase += 0.05;

	// //store 2-step previous position data
	// //to redraw background image accordingly
	// pps = ps;
	// ppx = px;
	// ppy = py;

	// ps = s;
	// px = x;
	// py = y;

	// s = 1.0 / (1.0 - 0.2 * sin(phase));
	// x = (float)(S3CFB_HRES_HALF) + 120.0 * cos(phase);
	// y = (float)(S3CFB_VRES_HALF) + 80.0 * sin(phase);

	// x1 = (int)(ppx - (pps * (float)imagew * 0.5));
	// y1 = (int)(ppy - (pps * (float)imageh * 0.5));
	// x2 = (int)(ppx + (pps * (float)imagew * 0.5));
	// y2 = (int)(ppy + (pps * (float)imageh * 0.5));


	// //redraw background image
	// gfx_bitblck_ext(fb, background, 
	// 		x1, y1, x2, y2,
	// 		S3CFB_HRES, S3CFB_VRES,
	// 		x1, y1, x2, y2,
	// 		S3CFB_HRES, S3CFB_VRES);

	// x1 = (int)(x - (s * (float)imagew * 0.5));
	// y1 = (int)(y - (s * (float)imageh * 0.5));
	// x2 = (int)(x + (s * (float)imagew * 0.5));
	// y2 = (int)(y + (s * (float)imageh * 0.5));

	// //draw current image
	// gfx_bitblck_ext(fb, (unsigned *)ball, 
	// 		x1, y1, x2, y2,
	// 		S3CFB_HRES, S3CFB_VRES,
	// 		0, 0, imagew, imageh,
	// 		imagew, imageh);
	/*
	simple drawing without stretching

	gfx_bitblck(fb, (unsigned *)image, 
			S3CFB_HRES, S3CFB_VRES, imagew, imageh, 
			(int)(x), (int)y);
	*/
	
	controller->update(fb);

}