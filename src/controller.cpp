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
#include "lcd.h"

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
						getItem++;//Parameter setting here
					ball[j]->collision(3);
				}
				else if (((ty + theight) > (by + bheight)) && (by>ty))
				{
					//left center
					if(target[i]->collision(2))
						getItem++;//Parameter setting here
					ball[j]->collision(2);
				}
				else if (((ty + theight + 2) > by) &&(ty + theight < by + bheight))
				{
					//left top
					if(target[i]->collision(1))
						getItem++;//Parameter setting here
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
						getItem++;//Parameter setting here
					ball[j]->collision(4);
				}
				else if (((ty + theight + 2) > by) && (ty + theight < by + bheight))
				{
					//center top
					if(target[i]->collision(0))
						getItem++;//Parameter setting here
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
						getItem++;//Parameter setting here
					ball[j]->collision(5);
				}
				else if (((ty + theight) >(by + bheight)) && (by>ty))
				{
					//right center
					if(target[i]->collision(6))
						getItem++;//Parameter setting here
					ball[j]->collision(6);
				}
				else if (((ty + theight + 2) > by) && (ty + theight < by + bheight))
				{
					//right top
					if(target[i]->collision(8))
						getItem++;//Parameter setting here
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
Controller::Controller(unsigned int * _fb, unsigned int * _background)
{
	//Turn is not started
	isTurnStarted=false;
	//Frame buffer
	fb=_fb;
	//Number of Target(random)
	targetNum=rand()%2+2;
	//Number of initial Ball(1)
	ballNum = 1;
	//Number of items you've gotten
	getItem = 0;
	//Set background
	background = _background;


	//Initialize member object
	for(int i=0; i<targetNum;i++)
	{
		int blockY;
		do
		{
			blockY=(rand()%6) * 80;
		}
		while(isBlockThere(222, blockY));
			
		target[i]=new block(222,blockY,46,80,0,0,(unsigned int *)yellowblock,fb,background,1);
	}
	button=new Button(650,35,46,80,0,0,(unsigned int *)buttonimage,fb,background);
	ball[0]=new Ball(589-20,240,20,20,0,0,(unsigned int *)ballimage,fb,background);
	bar[0]=new Bar(169,0,5,480,0,0,(unsigned int *)barimage,fb,background);
	bar[1]=new Bar(590,0,5,480,0,0,(unsigned int *)barimage,fb,background);
	arrow = new Arrow(543,217, 47,47,0,0,(unsigned int *)0, fb,background, 0);
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
		else if(x < 580)
		{
			arrow->setAngle(x, y);
			float theta=arrow->getAngle();
			float degree=theta*360/(2*3.14159265358979);
			if(degree<-52.5)
			{
				arrow->setImg((unsigned int *)sixtydeg);
			}
			else if(-52.5<=degree&&degree<-37.5)
			{
				arrow->setImg((unsigned int *)fourtyfivedeg);
			}
			else if(-37.5<=degree&&degree<-22.5)
			{
				arrow->setImg((unsigned int *)thirtydeg);
			}
			else if(-22.5=<degree&&degree<-5)
			{
				arrow->setImg((unsigned int *)fifteendeg);
			}
			else if(-5=<degree&&degree<5)
			{
				arrow->setImg((unsigned int *)zerodeg);
			}
			else if(5<degree&&degree<22.5)
			{
				arrow->setImg((unsigned int *)negfifteendeg);
			}
			else if(22.5<degree&&degree<37.5)
			{
				arrow->setImg((unsigned int *)negthirtydeg);
			}
			else if(37.5<degree&&degree<52.5)
			{
				arrow->setImg((unsigned int *)negfourtyfivedeg);
			}
			else if(52.5<degree)
			{
				arrow->setImg((unsigned int *)negsixtydeg);
			}
		}
	}
}

//move objects by frame
void Controller::update()
{
	bool isTurnEnd=true;
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
	if(isTurnEnd)
		endTurn();
}

//Drag blocks downward
//Collect balls
void Controller::endTurn()
{
	//generate arrow
	arrow = new Arrow(543,firstBallArriveY, 47,47,0,0,(unsigned int *)0, fb,background, 0);

	//Create more balls when you got items
	for(int i=0;i<getItem;i++)
	{
		ball[ballNum + i] = new Ball(589-20,240,20,20,0,0,(unsigned int *)ballimage,fb, background);
	}
		
	ballNum +=getItem;
	getItem = 0;

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