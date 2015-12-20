#include "target.h"

target::target(){}
target::target(int _x, int _y, int _width, int _height, int _vx, int _vy, unsigned int* _img, unsigned int* _phy_addr, int _Life)
{
	GameObject::GameObject(_x,_y,_width,_height,_vx,_vy,_img,_phy_addr);
	Life=_Life;
}
target::~target(){}
bool target::collision(int _type)
{
	Life--;
}
int target::getLife(){retun Life;}



item::item(){}
item::item(int _x, int _y, int _width, int _height, int _vx, int _vy, unsigned int* _img, unsigned int* _phy_addr)
{
	target::target(_x,_y,_width,_height,_vx,_vy,_img, _phy_addr, 1);
}
item::~item()
{}
bool item::collision(int _type)
{
	target::collision(_type);
	return true;
}



block::block(){}
block::block(int _x, int _y, int _width, int _height, int _vx, int _vy, unsigned int* _img, unsigned int* _phy_addr, int _Life)
{
	target::target(x,_y,_width,_height,_vx,_vy,_img,_phy_addr,_Life);
}
block::~block(){}
bool block::collision(int _type)
{
	taget::collision(_type);
	return false;
}