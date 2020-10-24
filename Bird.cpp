//CPS400 final project
//File name: Bird.cpp
//Description: This file is the implementation of bird class.
//				
#include "Bird.h"


//default constructor
Bird::Bird()
{
	//draw the background first
	POINT background;
	background.x = 2;
	background.y = 2;
	GameObject::Draw(background);

	//initilize the bird's position and radius
	p.x = GetWindowWidth() / 3;
	p.y = GetWindowHeight() / 2;
	radius = 25;
}

//set the pen color and brush color, and draw the bird
bool Bird::Draw(POINT p)
{
	fs.SetPenColor(RED);
	fs.SetBrushColor(RED);
	
	fs.FilledCircle(p, radius);
	return true;
}

//return the radius of the bird
int Bird::getRadius() 
{ 
	return radius;
}

//clear the bird on screen
bool Bird::ClearObject(POINT p, int height)
{
	fs.SetPenColor(ORANGE);
	fs.SetBrushColor(ORANGE);
	fs.FilledCircle(p, radius);

	return true;
}

//get the position of the bird
POINT Bird::GetPos()
{
	return p;
}

//set the position of the bird
void Bird::setPosition(POINT pos)
{
	p = pos;
}

