#include "gameObject.h"
#include "lcd.h"
#include "graphics.h"

GameObject::GameObject()
{
	vx=0;
	vy=0;
};
GameObject::GameObject(float _x, float _y, int _width, int _height, float _vx, float _vy, unsigned int* _img, unsigned int* _fb, unsigned int * _background)
{
	x=_x;
	y=_y;
	width=_width;
	height=_height;
	vx=_vx;
	vy=_vy;
	img=_img;
	fb=_fb;
	background = _background;
	isMoveTo = false;
	moveX = 0;
	moveY = 0;
}
GameObject::~GameObject()
{
	/*
	gfx_bitblck_ext(fb, background,
		ppx, ppy, ppx+width, ppy+height,
		S3CFB_HRES, S3CFB_VRES, 
		ppx, ppy, ppx+width, ppy+height,
		S3CFB_HRES, S3CFB_VRES);
		*/
}
void GameObject::setX(float _x){x=_x;}
void GameObject::setY(float _y){y=_y;}
void GameObject::setW(int _width){width=_width;}
void GameObject::setH(int _height){height=_height;}
void GameObject::setVx(float _vx){vx=_vx;}
void GameObject::setVy(float _vy){vy=_vy;}
void GameObject::setImg(unsigned int* _img){img=_img;}
float GameObject::getX(){return x;}
float GameObject::getY(){return y;}
int GameObject::getW(){return width;}
int GameObject::getH(){return height;}
float GameObject::getVx(){return vx;}
float GameObject::getVy(){return vy;}

void GameObject::move(unsigned int *_fb)
{
	ppx=px;
	ppy=py;
	px=x;
	py=y;
	x+=vx;
	y+=vy;
	if(isMoveTo)
	{
		x = moveX;
		y = moveY;
		isMoveTo = false;
	}

	//background drawing
	gfx_bitblck_ext(_fb,background,
		ppx,ppy,ppx+width,ppy+height,
		S3CFB_HRES, S3CFB_VRES,
		ppx,ppy,ppx+width,
		ppy+height,S3CFB_HRES, S3CFB_VRES);
}

void GameObject::draw(unsigned int *_fb)
{
	//image drawing
	gfx_bitblck(_fb,img, S3CFB_HRES, S3CFB_VRES, width, height,(int)x,(int)y);
}

bool GameObject::collision(int _type){return false;}

void GameObject::moveto(int _x, int _y)
{
	isMoveTo = true;
	moveX = _x;
	moveY = _y;
}