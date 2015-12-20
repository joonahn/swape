#include <stdlib.h>
#include <time.h>
#include "ball.h"
#include "gameObject.h"

Ball::Ball(){}
Ball::Ball(int _x, int _y, int _width, int _height, int _vx, int _vy, 
	unsigned int* _img, unsigned int * _fb, unsigned int * _background)
		:GameObject(_x,_y,_width,_height,_vx,_vy,_img,_fb, _background)
{
	
}
Ball::~Ball(){}
bool Ball::collision(int _type)
{
	switch(_type)
	{
		float tmp;
		srand(time(NULL));
		case 0:
		setY(getY()-2);
		setVy(-getVy());
		break;
		case 1:
		setX(getX()-2);
		setY(getY()-2);
		tmp=getVx();
		setVx(-getVy());
		setVy(-tmp);
		break;
		case 2:
		setX(getX()-2);
		setVx(-getVx());
		break;
		case 3:
		setX(getX()-2);
		setY(getY()+2);
		tmp=getVx();
		setVx(-getVy());
		setVy(-tmp);
		break;
		case 4:
		setY(getY()+2);
		setVy(-getVy());
		break;
		case 5:
		setX(getX()+2);
		setY(getY()+2);
		tmp=getVx();
		setVx(-getVy());
		setVy(-tmp);
		break;
		case 6:
		setX(getX()+2);
		setVx(-getVx());
		break;
		case 7:
		setX(getX()+2);
		setY(getY()-2);
		tmp=getVx();
		setVx(-getVy());
		setVy(-tmp);
		break;
	}
}