#include "gameObject.h"

class Arrow: public GameObject
{
public:
	Arrow();
	Arrow(float _x, float _y, int _width, int _height, float _vx, float _vy, unsigned int* _img, unsigned int* _fb, unsigned int * _background, float _tangent);
	virtual ~Arrow();
	void setTangent(int _x, int _y);
	float getTangent();
private:
	float tangent;
};