#ifndef CONTROLLER_H
#define CONTROLLER_H

#define TARGET_MAX 20
#define BALL_MAX 20
#define MANGO_WIDTH 800
#define MANGO_HEIGHT 480

class Target;
class Button;
class Bar;
class Ball;
class Arrow;

class Controller
{
private:
	//Members
	bool isTurnStarted;
	unsigned int * phy_addr;
	Target * target[TARGET_MAX];
	Button * button;
	Ball * ball[BALL_MAX];
	Bar * bar[2];
	Arrow * arrow;
	int targetNum;
	int ballNum;
	unsigned int * blockImage;
	unsigned int * itemImage;
	unsigned int * numberImage[10];
	unsigned int * ballImage;
	unsigned int * buttonImage;

	//Private method
	void detectCollision();
	void checkLife(Target * t);
	void launch();

public:
	//Inner method
	Controller(unsigned int * _phy_addr);
	void touchHandler(int x, int y);
	void update();
	void endTurn();
	void gameOver();
	void startTurn();
	
};

#endif