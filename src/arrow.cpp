#include "arrow.h"
#include <stdio.h>
Arrow::Arrow(){}
Arrow::Arrow(float _x, float _y, int _width, int _height, float _vx, float _vy,
	unsigned int* _img, unsigned int* _fb,unsigned int *_background, float _tangent)
		:GameObject::GameObject(_x,_y,_width,_height, _vx, _vy, _img, _fb, _background)
{
	tangent=_tangent;
}
Arrow::~Arrow(){}

void Arrow::setTangent(int a, int b)
{
	float data1 = (getY()-(getH()/2)-b);
	float data2 = (getX()+getW()-a);
	float data3 = data1/data2;
	// tangent=((getY()-(getH()/2)-b)/(getX()+getW())-a);
	tangent = data3;
	// printf("%d %d %X\n",a, b, data3);
	// printf("%d %d %d\n", (int)getX(), (int)getW(), a);
	// printf("%X %X %X\n", data1, data2, data3);
	// printf("%d\n\n", 1/0);
}
float Arrow::getTangent(){return tangent;}