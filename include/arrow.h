class arrow: public gameObject
{
public:
	arrow();
	arrow(float _x, float _y, int _width, int _height, float _vx, float _vy, unsigned int* _img, unsigned int* _phy_addr,float _angle);
	virtual ~arrow();
	void setAngle(int _x, int _y);
	float getAngle();
private:
	float angle;
};