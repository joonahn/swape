#include "button.h"

button::button(){}
button::button(float _x, float _y, int _width, int _height, float _vx, float _vy, unsigned int* _img, unsigned int* _phy_addr)
{
	gameObject(_x,_y,_width,_height,_vx,_vy,_img,_phy_addr);
}
button::~button(){}