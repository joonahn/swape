#include "gameObject.h"

GameObject::GameObject()
{
	vx=0;
	vy=0;
};
GameObject::GameObject(float _x, float _y, int _width, int _height, float _vx, float _vy, unsigned int* _img, unsigned int* _fb)
{
	x=_x;
	y=_y;
	width=_width;
	height=_height;
	vx=_vx;
	vy=_vy;
	img=_img;
	fb=_fb;
}
GameObject::~GameObject()
{
	for(int i=y;i<y+height;i++)
		for(int j=x;i<x+width;j++)
			fb[y*800+x]=0xFFFFFF;
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
void GameObject::move(unsigned int *fb)
{
	ppx=px;
	ppy=py;
	px=x;
	py=y;
	x+=vx;
	y+=vy;
	int a=(int)x;
	int b=(int)y;
	if(x<169-5)
	{
		x=169-5;
		vx=-vx;
	}
	if(y<0)
	{
		y=0;
		vy=-vy;
	}
	if(y>480-width)
	{
		y=480-width;
		vy=-vy;
	}
	if(x>590-height)
	{
		x=590-height;
		vx=0;
		vy=0;
	}
	//background drawing
	gfx_bitblock_ext(fb,background,ppx,ppy,ppx+width,ppy+height,S3CFB_HRES, S3CFB_VRES,ppx,ppy,ppx+width,ppy+height,S3CFB_HRES, S3CFB_VRES);
}
void GameObject::draw(unsigned int *fb)
{
	//image drawing
	gfx_bitblock(fb,img, S3CFB_HRES, S3CFB_VRES, width, height,(int)x,(int)y);
}
bool GameObject::collision(int _type){}