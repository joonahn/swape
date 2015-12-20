
#include "gameObject.h"

class Ball: public GameObject
{
public:
	Ball();
	Ball(int _x, int _y, int _width, int _height, int _vx, int _vy,
		unsigned int* _img, unsigned int* _fb, unsigned int * _background);
	virtual ~Ball();
	bool collision(int _type);
	void move(unsigned int * fb);
private:
};
