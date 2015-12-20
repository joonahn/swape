#include "arrow.h"

arrow::arrow(){}
arrow::arrow(float _x, float _y, int _width, int _height, float _vx, float _vy, unsigned int* _img, unsigned int* _phy_addr,float _angle)
{
	gameObject::gameObject(_x,_y,_width,_height, _vx, _vy, _img, _phy_addr);
	angle=_angle;
}
arrow::~arrow(){}
void setAngle(int _x, int _y)
{
	float tangent;
	tangent=((getY()-getW()-_y)/(getX()-getH()/2)-_x);
	angle=tangent-(tanget^3)/3+(tanget^5)/5-(tanget^7)/7+(tanget^9)/9-(tanget^11)/11;
	return angle;
}
float getAngle(){return angle;}