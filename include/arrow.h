class Arrow: public gameObject
{
public:
	Arrow();
	Arrow(float _x, float _y, int _width, int _height, float _vx, float _vy, unsigned int* _img, unsigned int* _fb,float _angle);
	virtual ~Arrow();
	void setAngle(int _x, int _y);
	float getAngle();
private:
	float angle;
};