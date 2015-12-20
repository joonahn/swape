class target: public GameObject
{
public:
	target();
	target::target(int _x, int _y, int _width, int _height, int _vx, int _vy, unsigned int* _img,, unsigned int* _phy_addr, int _Life);
	virtual ~target();

private:
	int Life;
};