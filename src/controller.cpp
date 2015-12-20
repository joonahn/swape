#include "controller.h"
#include <stdio.h>
#include <stdlib.h>
#include "../include/controller.h"
#include "util.h"
#include "yellowblock.h"
#include "ballimage.h"
#include "barimage.h"
#include "itemblock.h"
#include "buttonimage.h"

bool Controller::isBlockThere(int x, int y)
{
	for(int i = 0;i<targetNum; i++)
	{
		if((x==target[i]->getX()) && (y==target[i]->getY()))
			return true;
	}
	return false;
}

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
					if(target[i]->collision(3))
						ball[ballNum++]=new ball()//Parameter setting here
					ball[j]->collision(3);
				}
				else if (((ty + theight) > (by + bheight)) && (by>ty))
				{
					//left center
					if(target[i]->collision(2))
						ball[ballNum++]=new ball()//Parameter setting here
					ball[j]->collision(2);
				}
				else if (((ty + theight + 2) > by) &&(ty + theight < by + bheight))
				{
					//left top
					if(target[i]->collision(1))
						ball[ballNum++]=new ball()//Parameter setting here
					ball[j]->collision(1);
				}
				
			}
			else if ((bx + bwidth < tx + twidth) && (bx>tx))
			{
				//Collision!
				if (((by + bheight + 2) > ty) && (by < ty))
				{
					//center bottom
					if(target[i]->collision(4))
						ball[ballNum++]=new ball()//Parameter setting here
					ball[j]->collision(4);
				}
				else if (((ty + theight + 2) > by) && (ty + theight < by + bheight))
				{
					//center top
					if(target[i]->collision(0))
						ball[ballNum++]=new ball()//Parameter setting here
					ball[j]->collision(0);
				}
			}
			else if ((bx<(tx + twidth)) && (bx + bwidth - 2 > tx + twidth))
			{
				//Collision!
				if (((by + bheight + 2) > ty) && (by < ty))
				{
					//right bottom
					if(target[i]->collision(5))
						ball[ballNum++]=new ball()//Parameter setting here
					ball[j]->collision(5);
				}
				else if (((ty + theight) >(by + bheight)) && (by>ty))
				{
					//right center
					if(target[i]->collision(6))
						ball[ballNum++]=new ball()//Parameter setting here
					ball[j]->collision(6);
				}
				else if (((ty + theight + 2) > by) && (ty + theight < by + bheight))
				{
					//right top
					if(target[i]->collision(8))
						ball[ballNum++]=new ball()//Parameter setting here
					ball[j]->collision(8);
				}
			}
		}
		checkLife(target[i]);
	}
}

void Controller::checkLife(Target * t)
{
	if (t->getLife() == 0)
	{
		int i;
		for(i=0;i<targetNum;i++)
		{
			if(target[i]==t)
				break;
		}
		delete t;
		for(;i<targetNum-1;i++)
		{
			target[i]=target[i+1];
		}
		target[targetNum-1]=(Target *)0;
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

//Constructor : generate initial blocks
Controller::Controller(unsigned int * _fb)
{
	//Turn is not started
	isTurnStarted=false;
	//Frame buffer
	fb=_fb;
	//Number of Target(random)
	targetNum=rand()%2+2;
	//Number of initial Ball(1)
	ballNum=1;

	//Initialize member object
	for(int i=0; i<targetNum;i++)
	{
		do
		{
			int blockY=(rand()%6) * 80;
		}
		while(isBlockThere(222, blockY));
			
		target[i]=new block(222,blockY,80,46,0,0,yellowblock,fb,1);
	}

	button=new Button(650,35,46,80,0,0,buttonimage,fb);
	ball[0]=new Ball(591-21,240,20,20,0,0,ballimage,fb);
	bar[0]=new Bar(169,0,5,480,0,0,barimage,fb);
	bar[1]=new Bar(590,0,5,480,0,0,barimage,fb);
	arrow = new Arrow(543,217, 47,47,0,0,(unsigned int *)0, fb);

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
		//Arrow Move Should be implemented
		else if()
		{
			arrow->setAngle(x, y);
		}
	}
}

//move objects by frame
void Controller::update()
{
	bool isTurnEnd=true;
	float theta=arrow->getAngle();
	for (int i = 0;i < targetNum;i++)
		target[i]->move(fb);
	for (int i = 0;i < ballNum;i++)
		ball[i]->move(fb);
	for(int i=0;i<targetNum;i++)
		target[i]->draw(fb);
	for(int i=0;i<ballNum;i++)
		ball[i]->draw(fb);
	for(int i=0;i<ballNum;i++)
	{
		if(!(ball[i]->getVx()==0&&ball[i]->getVy()==0))
			isTurnEnd=false;
	}
	///////////////////////////////////////////////////////

	if(isTurnEnd)
		endTurn();
}

//Drag blocks downward
//Collect balls
void Controller::endTurn()
{
	
	arrow = new Arrow(543,firstBallArriveY, 47,47,0,0,(unsigned int *)0, fb);
	for(int i=0;i<ballNum;i++)
	{
		ball[i]->setX(591-21);
		ball[i]->setY(firstBallArriveY);
	}
	for(int i=0;i<targetNum;i++)
	{
		int tmpY = target[i]->getY();
		if(tmpY==498)
		{
			gameOver();
			return;
		}
		target[i]->setY(tmpY+46);
	}
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