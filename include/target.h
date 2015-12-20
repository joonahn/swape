#ifndef TARGET_H
#define TARGET_H

#include "target.h"
#include "gameObject.h"

class Target: public GameObject
{
public:
	Target();
	Target(int _x, int _y, int _width, int _height, int _vx, int _vy,
		unsigned int* _img, unsigned int* _fb, unsigned int * _background, int _Life);
	virtual ~Target();
	int getLife();
	virtual bool collision(int _type);

private:
	int Life;
};

class item: public Target
{
public:
	item();
	item(int _x, int _y, int _width, int _height, int _vx, int _vy,
		unsigned int* _img, unsigned int * _fb, unsigned int * _background);
	virtual bool collision(int _type);
	virtual ~item();
private:
};

class block: public Target
{
public:
	block();
	block(int _x, int _y, int _width, int _height, int _vx, int _vy,
		unsigned int* _img, unsigned int* _fb, unsigned int *_background, int _Life);
	virtual bool collision(int _type);
	virtual ~block();
private:
};

#endif