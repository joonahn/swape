#include "target.h"
#include <stdio.h>
#include "one.h"
#include "two.h"
#include "three.h"
#include "four.h"
#include "five.h"
#include "six.h"
#include "seven.h"
#include "eight.h"
#include "nine.h"
#include "zero.h"
#include "graphics.h"
#include "lcd.h"

Target::Target(){}
Target::Target(int _x, int _y, int _width, int _height, int _vx, int _vy, 
	unsigned int* _img, unsigned int* _fb, unsigned int * _background, int _Life)
		:GameObject(_x,_y,_width,_height,_vx,_vy,_img,_fb, _background)
{
	Life=_Life;
}
Target::~Target(){}
bool Target::collision(int _type)
{
	Life--;
	printf("Life--\n");
	return false;
}
int Target::getLife(){return Life;}



item::item(){}
item::item(int _x, int _y, int _width, int _height, int _vx, int _vy,
	unsigned int* _img, unsigned int* _fb, unsigned int * _background)
		:Target(_x,_y,_width,_height,_vx,_vy,_img, _fb,_background, 1)
{

}
item::~item()
{}
bool item::collision(int _type)
{
	Target::collision(_type);
	printf("Item collision\n");
	return true;
}



block::block(){}
block::block(int _x, int _y, int _width, int _height, int _vx, int _vy,
	unsigned int* _img, unsigned int* _fb, unsigned int * _background, int _Life)
		:Target(_x,_y,_width,_height,_vx,_vy,_img,_fb,_background,_Life)
{


}
block::~block(){}
bool block::collision(int _type)
{
	printf("Block collision\n");
	Target::collision(_type);
	return false;
}

void block::draw(unsigned int *fb)
{
	GameObject::draw(fb);
	int dig_width = 21, dig_height = 14;
	int one_x = 5, two_y = 26, one_y = 33;
	int _Life = getLife();
	if (_Life<10 && _Life>0)
	{
		unsigned int * _image;
		switch(_Life)
		{
			case 1:
				_image = (unsigned int *)one;
				dig_height = 10;
				break;
			case 2:
				_image = (unsigned int *)two;
				break;
			case 3:
				_image = (unsigned int *)three;
				break;
			case 4:
				_image = (unsigned int *)four;
				break;
			case 5:
				_image = (unsigned int *)five;
				break;
			case 6:
				_image = (unsigned int *)six;
				break;
			case 7:
				_image = (unsigned int *)seven;
				break;
			case 8:
				_image = (unsigned int *)eight;
				break;
			case 9:
				_image = (unsigned int *)nine;
				break;
			default:
				_image = (unsigned int *)zero;
				break;
		}

		gfx_bitblck(fb,_image, S3CFB_HRES, S3CFB_VRES, dig_width, dig_height,
			(int)x + one_x,(int)y + one_y);
		
	}
	else if(_Life<100 &&_Life>9)
	{
		int first = _Life/10;
		int second = _Life % 10;
		unsigned int * firstimg, *secondimg;
		switch(first)
		{
			case 1:
				firstimg = (unsigned int *)one;
				dig_height = 10;
				break;
			case 2:
				firstimg = (unsigned int *)two;
				break;
			case 3:
				firstimg = (unsigned int *)three;
				break;
			case 4:
				firstimg = (unsigned int *)four;
				break;
			case 5:
				firstimg = (unsigned int *)five;
				break;
			case 6:
				firstimg = (unsigned int *)six;
				break;
			case 7:
				firstimg = (unsigned int *)seven;
				break;
			case 8:
				firstimg = (unsigned int *)eight;
				break;
			case 9:
				firstimg = (unsigned int *)nine;
				break;
			default:
				firstimg = (unsigned int *)zero;
				break;
		}
		gfx_bitblck(fb,firstimg, S3CFB_HRES, S3CFB_VRES, dig_width, dig_height,
			(int)x + one_x,(int)y + two_y + dig_height);
		dig_height = 14;
		switch(second)
		{
			case 1:
				secondimg = (unsigned int *)one;
				dig_height = 10;
				break;
			case 2:
				secondimg = (unsigned int *)two;
				break;
			case 3:
				secondimg = (unsigned int *)three;
				break;
			case 4:
				secondimg = (unsigned int *)four;
				break;
			case 5:
				secondimg = (unsigned int *)five;
				break;
			case 6:
				secondimg = (unsigned int *)six;
				break;
			case 7:
				secondimg = (unsigned int *)seven;
				break;
			case 8:
				secondimg = (unsigned int *)eight;
				break;
			case 9:
				secondimg = (unsigned int *)nine;
				break;
			default:
				secondimg = (unsigned int *)zero;
				break;
		}

		gfx_bitblck(fb,secondimg, S3CFB_HRES, S3CFB_VRES, dig_width, dig_height,
			(int)x + one_x,(int)y + two_y);
	}
}