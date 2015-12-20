#include "bar.h"
bar::bar(){}
bar::bar(float _x, float _y, int _width, int _height, float _vx, float _vy, unsigned int* _img, unsigned int* _phy_addr)
{
	gameObject::gameObject(_x,_y,_width,_height,_vx,_vy,_img,_phy_addr);
}
bar::~bar(){}