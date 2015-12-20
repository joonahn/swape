#include "button.h"

Button::Button(){}
Button::Button(float _x, float _y, int _width, int _height, float _vx, float _vy,
 unsigned int* _img, unsigned int* _fb): GameObject(_x,_y,_width,_height,_vx,_vy,_img,_fb)
{
	
}
Button::~Button(){}