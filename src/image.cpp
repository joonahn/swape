#include <stdio.h>
#include "s3c_uart.h"
#include "s3c6410.h"
#include "image.h"


Image::Image(unsigned int *img, int _width, int _height, int _x, int _y, unsigned int *_phy_addr)
{
	x = _x;
	y = _y;
	width = _width;
	height = _height;
	phy_addr = _phy_addr;
	imageref = img;
	background = 0x000000;
	for(int i = 0;i<height;i++)
		for(int j = 0;j<width;j++)
		{
			phy_addr[(i+y)*800+(j+x)] = imageref[i*width+j] ;
		}
}

void Image::move(int dx, int dy)
{
	for(int i = 0;i<height;i++)
		for(int j = 0;j<width;j++)
		{
			phy_addr[(i+y)*800+(j+x)] = background;
		}

	x+=dx;
	y+=dy;
	for(int i = 0;i<height;i++)
		for(int j = 0;j<width;j++)
		{
			phy_addr[(i+y)*800+(j+x)] = imageref[i*width+j];
		}
	// printf("Move to %u %u", x, y);
}