#include "controller.h"
#include <stdio.h>
#include <stdlib.h>
#include "../include/controller.h"
#include "util.h"

void Controller::detectCollision()
{
	//Target collision
	for (int i = 0;i < targetNum;i++)
	{
		//Target Position
		int twidth, theight;
		int tx, ty;
		twidth = target[i]->getW();
		theight = target[i]->getH();
		tx = target[i]->getX();
		ty = target[i]->getY();
		for (int j = 0;j < ballNum;j++)
		{
			//Ball Position
			int bwidth, bheight;
			int bx, by;
			bwidth = ball[j]->getW();
			bheight = ball[j]->getH();
	   		bx = ball[j]->getX();
			by = ball[j]->getY();


			//X-axis overlap
			if (((bx + bwidth + 2)  > tx) && (bx<tx))
			{

				//Collision!
				if (((by + bheight + 2) > ty) && (by < ty))
				{
					//left bottom
					if(ball[j]->collision(3))
						ball[ballNum++]=new ball()//Parameter setting here
					target[i]->collision(3);
				}
				else if (((ty + theight) > (by + bheight)) && (by>ty))
				{
					//left center
					if(ball[j]->collision(2))
						ball[ballNum++]=new ball()//Parameter setting here
					target[i]->collision(2);
				}
				else if (((ty + theight + 2) > by) &&(ty + theight < by + bheight))
				{
					//left top
					if(ball[j]->collision(1))
						ball[ballNum++]=new ball()//Parameter setting here
					target[i]->collision(1);
				}
				
			}
			else if ((bx + bwidth < tx + twidth) && (bx>tx))
			{
				//Collision!
				if (((by + bheight + 2) > ty) && (by < ty))
				{
					//center bottom
					if(ball[j]->collision(4))
						ball[ballNum++]=new ball()//Parameter setting here
					target[i]->collision(4);
				}
				else if (((ty + theight + 2) > by) && (ty + theight < by + bheight))
				{
					//center top
					if(ball[j]->collision(0))
						ball[ballNum++]=new ball()//Parameter setting here
					target[i]->collision(0);
				}
			}
			else if ((bx<(tx + twidth)) && (bx + bwidth - 2 > tx + twidth))
			{
				//Collision!
				if (((by + bheight + 2) > ty) && (by < ty))
				{
					//right bottom
					if(ball[j]->collision(5))
						ball[ballNum++]=new ball()//Parameter setting here
					target[i]->collision(5);
				}
				else if (((ty + theight) >(by + bheight)) && (by>ty))
				{
					//right center
					if(ball[j]->collision(6))
						ball[ballNum++]=new ball()//Parameter setting here
					target[i]->collision(6);
				}
				else if (((ty + theight + 2) > by) && (ty + theight < by + bheight))
				{
					//right top
					if(ball[j]->collision(8))
						ball[ballNum++]=new ball()//Parameter setting here
					target[i]->collision(8);
				}
			}
		}
	}
}

void Controller::checkLife(Target * t)
{
	if (t->getLife() == 0)
	{
		int i;
		for(i=0;i<targetNum;i++)
		{
			if(target[i]=t)
				break;
		}
		delete t;
		for(;i<targetNum-1;i++)
		{
			target[i]=target[i+1];
		}
		target[targetNum-1]=null;
		targetNum--;
	}
}

void Controller::launch()
{
	float theta=arrow->getAngle();
	int speed=3;
	for(int i=0; i<ballNum;i++)
	{
		ball[i]->setVx(speed*sin(theta));
		ball[i]->setVy(speed*cos(theta));
	}
	//not implemented here
}

Controller::Controller(unsigned int * _phy_addr)
{
	//Constructor : generate initial blocks
	phy_addr = _phy_addr;
	int count = rand() % 3 + 2;
	for (int i = 0;i < count;i++)
	{

	}
}

void Controller::touchHandler(int x, int y)
{
	//button
	if (!isTurnStarted)
	{
		if (x > button->getX() && x < button->getX() - button->getW())
		{
			if (y > button->getY() && y < button->getY() - button->getH())
			{
				launch();
			}
		}
	}
	//Arrow Move Should be implemented
	else
	{
		arrow->setAngle(x, y);
	}
}

//move objects by frame
void Controller::update()
{
	for (int i = 0;i < targetNum;i++)
	{
		target[i]->move(target[i]->getVx(), target[i]->getVy());
	}
	for (int i = 0;i < ballNum;i++)
	{
		ball[i]->move(ball[i]->getVx(), target[i]->getVy());
	}
}

void Controller::endTurn()
{
	arrow = new Arrow();
	isTurnStarted = false;
}

void Controller::gameOver()
{
	//Print gameover image
	isTurnStarted = true;
	printf("Game Over!!!");
}

void Controller::startTurn()
{
	delete arrow;
	isTurnStarted = true;
}