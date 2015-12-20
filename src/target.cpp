#include "target.h"

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
	Target::collision(_type);
	return false;
}