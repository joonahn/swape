#include "target.h"

Target::Target(){}
Target::Target(int _x, int _y, int _width, int _height, int _vx, int _vy, unsigned int* _img, unsigned int* _fb, int _Life)
{
	GameObject::GameObject(_x,_y,_width,_height,_vx,_vy,_img,_fb);
	Life=_Life;
}
Target::~Target(){}
bool Target::collision(int _type)
{
	Life--;
}
int Target::getLife(){retun Life;}



item::item(){}
item::item(int _x, int _y, int _width, int _height, int _vx, int _vy, unsigned int* _img, unsigned int* _fb)
{
	Target::Target(_x,_y,_width,_height,_vx,_vy,_img, _fb, 1);
}
item::~item()
{}
bool item::collision(int _type)
{
	Target::collision(_type);
	return true;
}



block::block(){}
block::block(int _x, int _y, int _width, int _height, int _vx, int _vy, unsigned int* _img, unsigned int* _fb, int _Life)
{
	Target::Target(x,_y,_width,_height,_vx,_vy,_img,_fb,_Life);
}
block::~block(){}
bool block::collision(int _type)
{
	taget::collision(_type);
	return false;
}