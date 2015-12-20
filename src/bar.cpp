#include "bar.h"

Bar::Bar(){}
Bar::Bar(float _x, float _y, int _width, int _height, float _vx, float _vy,
	unsigned int* _img, unsigned int* _fb, unsigned int * _background)
		:GameObject(_x,_y,_width,_height,_vx,_vy,_img,_fb, _background)
{
	
}
Bar::~Bar(){}