#include "gameObject.h"
class Button: public GameObject
{
public:
	Button();
	Button(float _x, float _y, int _width, int _height, float _vx, float _vy,
		unsigned int* _img, unsigned int* _fb, unsigned int * _background);
	virtual ~Button();
private:
};