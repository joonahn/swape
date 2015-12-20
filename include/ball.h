class ball:public gameObject
{
public:
	ball();
	ball(int _x, int _y, int _width, int _height, int _vx, int _vy, unsigned int* _img, unsigned int* _phy_addr);
	virtual ~ball();
private:
};
