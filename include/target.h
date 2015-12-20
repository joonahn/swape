class Target: public GameObject
{
public:
	Target();
	Target::Target(int _x, int _y, int _width, int _height, int _vx, int _vy, unsigned int* _img,, unsigned int* _fb, int _Life);
	virtual ~Target();
	int getLife();

private:
	int Life;
};

class item: public Target
{
public:
	item();
	item(int _x, int _y, int _width, int _height, int _vx, int _vy, unsigned int* _img);
	virtual ~item();
private:
};

class block:: public Target
{
public:
	block();
	block(int _x, int _y, int _width, int _height, int _vx, int _vy, unsigned int* _img, unsigned int* _fb, int _Life);
	virtual ~block();
private:
};