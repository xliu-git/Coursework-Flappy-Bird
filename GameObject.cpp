//CPS400 final project
//File name: GameObject.cpp
//Description: This is the implementation file of GameObject class. This class is an abstract class.
//				
#include "GameObject.h"
#include <iostream>

using namespace std;

//constructor
GameObject::GameObject()
	:fs(WINDOW_MAXX, WINDOW_MAXY),
	borderWidth(DEFAULT_PEN_WIDTH),
	borderColor(BLUE),
	fillColor(BLUE)
{
}

//set border color
bool GameObject::SetBorderColor(SHAPE_COLOR color)
{
	borderColor = color;
	return true;
}

//set brush color
bool GameObject::SetFillColor(SHAPE_COLOR color)
{
	fillColor = color;
	return true;
}

unsigned int GameObject::GetWindowWidth()
{
	return WINDOW_MAXX - 4; 
}

unsigned int GameObject::GetWindowHeight()
{
	return WINDOW_MAXY - 28;
}

bool GameObject::Draw(POINT p)
{

	fs.SetBrushColor(ORANGE);
	fs.SetPenColor(ORANGE);

	fs.FilledRectangle(p, GetWindowHeight() - 2 * borderWidth - 9, GetWindowWidth() - 2 * borderWidth - 10);
	return 0;
}

//set the game over flag for derived class
void GameObject::setStop(int s)
{
	if (s)
	{
		stop = 1;
	}
	else
	{
		stop = 0;
	}
}

