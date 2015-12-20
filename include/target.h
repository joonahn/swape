class target: public GameObject
{
public:
	target();
	target::target(int _x, int _y, int _width, int _height, int _vx, int _vy, unsigned int* _img,, unsigned int* _phy_addr, int _Life);
	virtual ~target();
	int getLife();

private:
	int Life;
};

class item: public target
{
public:
	item();
	item(int _x, int _y, int _width, int _height, int _vx, int _vy, unsigned int* _img);
	virtual ~item();
private:
};

class block:: public target
{
public:
	block();
	block(int _x, int _y, int _width, int _height, int _vx, int _vy, unsigned int* _img, unsigned int* _phy_addr, int _Life);
	virtual ~block();
private:
};