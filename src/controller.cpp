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

Controller::Controller(unsigned int * _fb)
{
	//Constructor : generate initial blocks
	int blockCount=rand()%2+2;
	isTurnStarted=false;
	fb=_fb;
	targetNum=blockCount;
	ballNum=1;
	for(int i=0; i<blockCount;i++)
	{
		int blockPos=rand()%6;
		target[i]=new block(222,blockPos*80,46,80,0,0,(unsigned int *)yellowblock,fb,1);
	}
	button=new Button(650,35,46,80,0,0,buttonImg,fb);
	ball[0]=new Ball(591-20,240,20,20,0,0,(unsigned int *)ballimage,fb);
	bar[0]=new Bar(169,0,5,480,0,0,(unsigned int *)barimage,fb);
	bar[1]=new Bar(590,0,5,480,0,0,(unsigned int *)barimage,fb);
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
		if(ball[i]->getX()!=590-20)
			isTurnEnd=false;
	}
	float degree=theta*360/(2*3.14159265358979);
	if(degree>0)
	{
		
	}
	else
	{
		
	}
	if(isTurnEnd)
		endTurn();
}

void Controller::endTurn()
{
	arrow = new Arrow();
	for(int i=0;i<ballNum;i++)
	{
		//ball[i]->setX();
		//ball[i]->setY();
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