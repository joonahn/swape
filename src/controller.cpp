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
#include "sixtydeg.h"
#include "fourtyfivedeg.h"
#include "thirtydeg.h"
#include "fifteendeg.h"
#include "zerodeg.h"
#include "negfifteendeg.h"
#include "negthirtydeg.h"
#include "negfourtyfivedeg.h"
#include "negsixtydeg.h"

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
					printf("Controller::collision");
					//left bottom
					if(target[i]->collision(3))
						getItem++;//Parameter setting here
					ball[j]->collision(3);
				}
				else if (((ty + theight) > (by + bheight)) && (by>ty))
				{
					printf("Controller::collision");
					//left center
					if(target[i]->collision(2))
						getItem++;//Parameter setting here
					ball[j]->collision(2);
				}
				else if (((ty + theight + 2) > by) &&(ty + theight < by + bheight))
				{
					printf("Controller::collision");
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
					printf("Controller::collision");
					//center bottom
					if(target[i]->collision(4))
						getItem++;//Parameter setting here
					ball[j]->collision(4);
				}
				else if (((ty + theight + 2) > by) && (ty + theight < by + bheight))
				{
					printf("Controller::collision");
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
					printf("Controller::collision");
					//right bottom
					if(target[i]->collision(5))
						getItem++;//Parameter setting here
					ball[j]->collision(5);
				}
				else if (((ty + theight) >(by + bheight)) && (by>ty))
				{
					printf("Controller::collision");
					//right center
					if(target[i]->collision(6))
						getItem++;//Parameter setting here
					ball[j]->collision(6);
				}
				else if (((ty + theight + 2) > by) && (ty + theight < by + bheight))
				{
					printf("Controller::collision");
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
		if(i!=targetNum)
		{
			delete t;
			for(;i<targetNum-1;i++)
			{
				target[i]=target[i+1];
			}
			target[targetNum-1]=(Target *)0;
			targetNum--;
		}
	}
}

void Controller::launch()
{
	printf("launch start!\n");
	float tangent=arrow->getTangent();
	tangent *=-1;
	int speed=3;
	startTurn();
	for(int i=0; i<ballNum;i++)
	{
		ball[i]->setVy(speed*Q_rsqrt(1+tangent*tangent)*tangent);

		// ball[i]->setVy((((int)tangent)>0)?(speed*Q_rsqrt(1+tangent*tangent)*tangent * (-1)):(speed*Q_rsqrt(1+tangent*tangent)*tangent));//sin
		ball[i]->setVx(speed*Q_rsqrt(1+tangent*tangent) * (-1));//cos
		printf("Vx, Vy : %d %d\n", ((int)ball[i]->getVx()), ((int)ball[i]->getVy()));
		printf("tangent: %d %f \n",(int)tangent, tangent);
	}
	//not implemented here
}

//Constructor : generate initial blocks
Controller::Controller(unsigned int * _background)
{
	//Initial Target Number
	int initialTargetNum = rand()%2+2;
	//Turn is not started
	isTurnStarted=false;
	//Frame buffer
	fb=0;
	//Number of initial Ball(1)
	ballNum = 1;
	//Number of items you've gotten
	getItem = 0;
	//Set background
	background = _background;
	turnNum=1;

	
	//Initialize member object
	for(targetNum = 0;targetNum < initialTargetNum; targetNum++)
	{
		int blockY;
		do
		{
			blockY=(rand()%6) * 80;
		}
		while(isBlockThere(222, blockY));
			
		target[targetNum]=new block(222,blockY,46,80,0,0,(unsigned int *)yellowblock,fb,background,turnNum);
	}
	int itemY;
	do
	{
		itemY=(rand()%6)*80;
	}
	while(isBlockThere(222,itemY));
	target[targetNum++]=new item(222,itemY,46,80,0,0,(unsigned int*)itemblock,fb,background,1);
	
	button=new Button(650,35,46,80,0,0,(unsigned int *)buttonimage,fb,background);
	ball[0]=new Ball(589-20,240,20,20,0,0,(unsigned int *)ballimage,fb,background);
	bar[0]=new Bar(169,0,5,480,0,0,(unsigned int *)barimage,fb,background);
	bar[1]=new Bar(590,0,5,480,0,0,(unsigned int *)barimage,fb,background);
	arrow = new Arrow(542,228, 47,47,0,0,(unsigned int *)zerodeg, fb,background, 0);
}

void Controller::touchHandler(int x, int y)
{
	printf("%d %d\n", x, y);
	//button
	if (!isTurnStarted)
	{
		printf("isTurnStarted! %d %d\n", (int)(button->getX()),(int)(button->getY()));
		float data1 = button->getX();
		float data2 = button->getX() + button->getW();
		if (x > data1 && x < data2)
		{
			printf("x>button->getX\n");
			if (y > button->getY() && y < button->getY() + button->getH())
			{
				printf("y>button->getY\n");
				launch();
			}
		}
		//Arrow Move Should be implemented
		else if(x < 580)
		{
			arrow->setTangent(x, y);
			float tangent=arrow->getTangent();
			if(tangent<-1.303225)
			{
				arrow->setImg((unsigned int *)negsixtydeg);
			}
			else if(-1.303225<=tangent&&tangent<-0.767326)
			{
				arrow->setImg((unsigned int *)negfourtyfivedeg);
			}
			else if(-0.767326<=tangent&&tangent<-0.414213)
			{
				arrow->setImg((unsigned int *)negthirtydeg);
			}
			else if(-0.414213<=tangent&&tangent<-0.087486)
			{
				arrow->setImg((unsigned int *)negfifteendeg);
			}
			else if(-0.087486<=tangent&&tangent<0.087486)
			{
				arrow->setImg((unsigned int *)zerodeg);
			}
			else if(0.087486<=tangent&&tangent<0.414213)
			{
				arrow->setImg((unsigned int *)fifteendeg);
			}
			else if(0.414213<=tangent&&tangent<0.767326)
			{
				arrow->setImg((unsigned int *)thirtydeg);
			}
			else if(0.767326<=tangent&&tangent<1.303225)
			{
				arrow->setImg((unsigned int *)fourtyfivedeg);
			}
			else if(1.303225<=tangent)
			{
				arrow->setImg((unsigned int *)sixtydeg);
			}
		}
	}
}

//move objects by frame
void Controller::update(unsigned int * fb)
{
	detectCollision();

	//Move - Draw Background
	for (int i = 0;i < targetNum;i++)
		target[i]->move(fb);
	for (int i = 0;i < ballNum;i++)
		ball[i]->move(fb);
	for(int i = 0;i<2;i++)
		bar[i]->move(fb);
	button->move(fb);
	arrow->move(fb);

	//Draw
	for(int i=0;i<targetNum;i++)
		target[i]->draw(fb);
	for(int i=0;i<ballNum;i++)
		ball[i]->draw(fb);
	for(int i = 0;i<2;i++)
		bar[i]->draw(fb);
	button->draw(fb);
	if(!isTurnStarted)
		arrow->draw(fb);



	if(isTurnStarted)
	{
		bool isTurnEnd=true;
		for(int i=0;i<ballNum;i++)
		{
			if(ball[i]->getX()!=590-20)
			{
				isTurnEnd=false;
			}
			else if(firstBallArriveY==-1)
			{
				firstBallArriveY = ball[i]->getY();
			}
		}
		if(isTurnEnd)
			endTurn();
	}	

}

//Drag blocks downward
//Collect balls
void Controller::endTurn()
{
	turnNum++;
	//delete arrow;
	//Create more balls when you got items
	for(int i=0;i<getItem;i++)
	{
		ball[ballNum + i] = new Ball(589-20,240,20,20,0,0,(unsigned int *)ballimage,fb, background);
	}
	
	ballNum +=getItem;
	getItem = 0;

	//Collect balls
	for(int i=0;i<ballNum;i++)
	{
		// ball[i]->setX(591-21);
		// ball[i]->setY(firstBallArriveY);
		ball[i]->moveto(591-21, firstBallArriveY);
	}

	//Move Arrow
	arrow->setY(firstBallArriveY-12);

	//Drag Objects downward
	for(int i=0;i<targetNum;i++)
	{
		int tmpX = target[i]->getX();
		if(tmpX==498)
		{
			gameOver();
			return;
		}
		// target[i]->setX(tmpX+46);
		target[i]->moveto(tmpX+46, target[i]->getY());
	}
	int addingTargetNum=rand()%2+3;
	for(; targetNum < targetNum+addingTargetNum; targetNum++)
	{
		int blockY;
		do
		{
			blockY=(rand()%6) * 80;
		}
		while(isBlockThere(222, blockY));
			
		target[targetNum]=new block(222,blockY,46,80,0,0,(unsigned int *)yellowblock,fb,background,turnNum);
	}
	int itemY;
	do
	{
		itemY=(rand()%6)*80;
	}
	while(isBlockThere(222,itemY));
	target[targetNum++]=new item(222,itemY,46,80,0,0,(unsigned int*)itemblock,fb,background,1);

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
	isTurnStarted = true;
	firstBallArriveY = -1;
}