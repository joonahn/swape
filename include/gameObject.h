class GameObject
{
public:
	GameObject();
	GameObject(float _x, float _y, int _width, int _height, float _vx, float _vy, unsigned int* _img, unsigned int* _phy_addr);
	virtual ~GameObject();
	void setX(float);
	void setY(float);
	void setW(int);
	void setH(int);
	void setVx(float);
	void setVy(float);
	void setImg(unsigned int*);
	float getX();
	float getY();
	int getW();
	int getH();
	float getVx();
	float getVy();
	void move();
	virtual bool collision(int);
private:
	float x;
	float y;
	int width;
	int height;
	float vx;
	float vy;
	unsigned int* img;
protected:
	unsigned int* phy_addr;
};
