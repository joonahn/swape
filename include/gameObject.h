#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject
{
public:
	GameObject();
	GameObject(float _x, float _y, int _width, int _height, float _vx, float _vy, unsigned int* _img, unsigned int* _fb, unsigned int * _background);
	virtual ~GameObject();
	void setX(float);
	void setY(float);
	void setW(int);
	void setH(int);
	void setVx(float);
	void setVy(float);
	void setImg(unsigned int*);
	float getX();
	float getY();
	int getW();
	int getH();
	float getVx();
	float getVy();
	void move(unsigned int *fb);
	void moveto(int x, int y);
	virtual void draw(unsigned int *fb);
	virtual bool collision(int);
private:
	float px;
	float py;
	float ppx;
	float ppy;
	unsigned int* img;
	bool isMoveTo;
	int moveX, moveY;
protected:
	float x;
	float y;
	int width;
	int height;
	float vx;
	float vy;
	unsigned int * fb;
	unsigned int * background;
};

#endif