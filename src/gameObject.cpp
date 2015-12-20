#include "gameObject.h"

GameObject::GameObject()
{
	vx=0;
	vy=0;
};
GameObject::GameObject(float _x, float _y, int _width, int _height, float _vx, float _vy, unsigned int* _img, unsigned int* _phy_addr)
{
	x=_x;
	y=_y;
	width=_width;
	height=_height;
	vx=_vx;
	vy=_vy;
	img=_img;
	phy_addr=_phy_addr;
}
GameObject::~GameObject()
{
	for(int i=y;i<y+height;i++)
		for(int j=x;i<x+width;j++)
			phy_addr[y*800+x]=0x000000;
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
void GameObject::move()
{
	x+=vx;
	y+=vy;
	int a=(int)x;
	int b=(int)y;
	for(int i=b;i<b+height;i++)
		for(int j=a;j<a+width;j++)
			phy_addr[i*800+j]=img[(i-b)*800+(j-a)];
}
bool GameObject::collision(int _type){}