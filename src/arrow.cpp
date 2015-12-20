#include "arrow.h"
#include <math.h>
Arrow::Arrow(){}
Arrow::Arrow(float _x, float _y, int _width, int _height, float _vx, float _vy,
	unsigned int* _img, unsigned int* _fb,unsigned int *_background, float _angle)
		:GameObject::GameObject(_x,_y,_width,_height, _vx, _vy, _img, _fb, _background)
{
	angle=_angle;
}
Arrow::~Arrow(){}

void Arrow::setAngle(int _x, int _y)
{
	float tangent;
	tangent=((getY()-getW()-_y)/(getX()-getH()/2)-_x);
	angle=atan(tangent);
}
float Arrow::getAngle(){return angle;}