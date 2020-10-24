//CPS400 final project
//File name: Bird.h
//Description: This is the header file of bird class.
//				methods description is shown below


#ifndef __BIRD__
#define __BIRD__

#include "GameObject.h"

class Bird : public GameObject
{

public:

	//default constructor
	Bird();

	///////////////////////////////////////
	//Draw()
	//Description: This method set up the brush color and pen color, and draw the bird
	//input: POINT p (inherited from class GameObject)
	//output: none
	//return: bool
	///////////////////////////////////////
	virtual bool Draw(POINT p);

	///////////////////////////////////////
	//ClearObject
	//Description: This method clear the object on the screen
	//input: POINT p, int param (radius) (as inherited from GameObject class)
	//output: none
	//return: bool
	///////////////////////////////////////
	virtual bool ClearObject(POINT p, int param);

	///////////////////////////////////////
	//getRadius
	//Description: This method return the radius of the bird
	//input: none
	//output: none
	//return: int, representing radius
	///////////////////////////////////////
	int getRadius();

	///////////////////////////////////////
	//getPos
	//Description: This method return the positionof the bird
	//input: none
	//output: none
	//return: POINT, representing the position of bird
	///////////////////////////////////////
	virtual POINT GetPos();

	///////////////////////////////////////
	//setPosition
	//Description: This method set the position of the bird
	//input: POINT pos
	//output: none
	//return: none
	///////////////////////////////////////
	void setPosition(POINT pos);

private:

	POINT p;	//position of the bird
	int radius;	//radius of the bird
};

#endif