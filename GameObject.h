//CPS400 final project
//File name: GameObject.h
//Description: This is the header file of GameObject class. This class is an abstract class.
//				Barrier, Bird, ScoreBoard classes are all inherited from it.
//				methods description is shown below
#ifndef __GAMEOBJECT__
#define __GAMEOBJECT__


#include "FilledShapes.h"
#include <windows.h>

#define WINDOW_MAXX 800
#define WINDOW_MAXY 600
#define DEFAULT_PEN_WIDTH 5

class GameObject
{

public:
	//Default constructor
	GameObject();

	
	/////////////////////////////////////////
	//Draw()
	//Description: This is a virtual function
	//input: POINT p 
	//output: none
	//return: bool
	///////////////////////////////////////
	virtual bool Draw(POINT p) = 0;

	/////////////////////////////////////////
	//SetFillColor()
	//Description: This method set the brush color
	//input: SHAPE_COLOR fillColor
	//output: none
	//return: bool
	///////////////////////////////////////
	bool SetFillColor(SHAPE_COLOR fillColor);

	/////////////////////////////////////////
	//SetBorderColor()
	//Description: This method set the pen color
	//input: SHAPE_COLOR borderColor
	//output: none
	//return: bool
	///////////////////////////////////////
	bool SetBorderColor(SHAPE_COLOR borderColor);

	/////////////////////////////////////////
	//GetWindowWidth()
	//Description: This method return the filled shape window width
	//input: none
	//output: none
	//return: unsigned int
	///////////////////////////////////////
	unsigned int GetWindowWidth();

	/////////////////////////////////////////
	//GetWindowHeight()
	//Description: This method return the filled shape window height
	//input: none
	//output: none
	//return: unsigned int
	///////////////////////////////////////
	unsigned int GetWindowHeight();

	/////////////////////////////////////////
	//ClearObject()
	//Description: This method is a virtual method for clear object
	//input: POINT p, int param
	//output: none
	//return: bool
	///////////////////////////////////////
	virtual bool ClearObject(POINT p, int param) = 0;

	/////////////////////////////////////////
	//GetPos()
	//Description: This method is a virtual method for getting objects' positions
	//input: none
	//output: none
	//return: bool
	///////////////////////////////////////
	virtual POINT GetPos() = 0;

	/////////////////////////////////////////
	//setStop()
	//Description: This method takes in the game over flag stop the game
	//input: int s
	//output: none
	//return: none
	///////////////////////////////////////
	void setStop(int s);

	int numBarriers = 0;		//initial value of score
	//int getScore();
	//void setScore(int score);
protected:

	FilledShapes fs;
	unsigned int borderWidth;
	SHAPE_COLOR borderColor;
	SHAPE_COLOR fillColor;
	int stop = 0;				//stop = 0 means game isn't over
	//int numBarriers = 0;
};

#endif // ! __GAMEOBJECT__