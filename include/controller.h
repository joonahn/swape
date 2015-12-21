#ifndef CONTROLLER_H
#define CONTROLLER_H

#define TARGET_MAX 70
#define BALL_MAX 70
#define MANGO_WIDTH 800
#define MANGO_HEIGHT 480

#include "target.h"
#include "button.h"
#include "bar.h"
#include "ball.h"
#include "arrow.h"
#include "gameObject.h"

class Controller
{
private:
	//Members
	bool isTurnStarted;
	unsigned int * background;
	unsigned int * fb;
	Target * target[TARGET_MAX];
	Target * graveyard[TARGET_MAX];
	int graveyardYear[TARGET_MAX];
	GameObject * gameoverImage;
	Button * button;
	Ball * ball[BALL_MAX];
	Bar * bar[2];
	Arrow * arrow;
	int graveNum;
	int targetNum;
	int ballNum;
	int getItem;
	int turnNum;
	int timeCount;
	unsigned int * blockImage;
	unsigned int * itemImage;
	unsigned int * numberImage[10];
	unsigned int * ballImage;
	unsigned int * buttonImage;
	int firstBallArriveY;
	bool isGameover;

	//Private method
	void detectCollision(unsigned int * fb);
	void checkLife(Target * t, unsigned int * _fb);
	void launch();
	bool isBlockThere(int x, int y);

public:
	//Inner method
	Controller(unsigned int * background);
	void touchHandler(int x, int y);
	void update(unsigned int * fb);
	void endTurn();
	void gameOver();
	void startTurn();
	void eachTime();
	
};

#endif