class Ball:public gameObject
{
public:
	Ball();
	Ball(int _x, int _y, int _width, int _height, int _vx, int _vy, unsigned int* _img, unsigned int* _fb);
	virtual ~Ball();
private:
};
