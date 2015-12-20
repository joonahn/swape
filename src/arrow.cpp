#include "arrow.h"
#include <math.h>
Arrow::Arrow(){}
Arrow::Arrow(float _x, float _y, int _width, int _height, float _vx, float _vy, unsigned int* _img, unsigned int* _fb,float _angle)
{
	gameObject::gameObject(_x,_y,_width,_height, _vx, _vy, _img, _fb);
	angle=_angle;
}
Arrow::~Arrow(){}

void setAngle(int _x, int _y)
{
	float tangent;
	tangent=((getY()-getW()-_y)/(getX()-getH()/2)-_x);
	angle=atan(tangent);
}
float getAngle(){return angle;}