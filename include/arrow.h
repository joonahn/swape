#include "gameObject.h"

class Arrow: public GameObject
{
public:
	Arrow();
	Arrow(float _x, float _y, int _width, int _height, float _vx, float _vy, unsigned int* _img, unsigned int* _fb, unsigned int * _background, float _angle);
	virtual ~Arrow();
	void setAngle(int _x, int _y);
	float getAngle();
private:
	float angle;
};