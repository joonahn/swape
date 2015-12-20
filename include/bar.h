#include "gameObject.h"

class Bar: public GameObject
{
public:
	Bar();
	Bar(float _x, float _y, int _width, int _height, float _vx, float _vy,
		unsigned int* _img, unsigned int* _fb, unsigned int * _background);
	~Bar();
private:
};