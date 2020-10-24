//CPS400 final project
//File Name:Barrier.h
//Description: This class is inherited from GameObject class. And this class is to generate barriers.
//				Methods description is shown below;
#include "GameObject.h"
#include "Bird.h"
#include<vector>

class Barrier : public GameObject
{
	
public:
	//default constructor
	Barrier();
	
	///////////////////////////////////////
	//Draw()
	//Description: This method set up the brush color and pen color, and call the GenBarrier function
	//input: POINT p (inherited from class GameObject)
	//output: none
	//return: bool
	///////////////////////////////////////
	virtual bool Draw(POINT p);

	///////////////////////////////////////
	//GenBarrier()
	//Description: This method randomize barrier's hight and draw the moving barriers
	//input: none
	//output: none
	//return: none
	///////////////////////////////////////
	void GenBarrier();

	///////////////////////////////////////
	//ClearObject
	//Description: This method clear the object on the screen
	//input: POINT p, int param (as inherited from GameObject class)
	//output: none
	//return: bool
	///////////////////////////////////////
	virtual bool ClearObject(POINT p, int param);

	///////////////////////////////////////
	//GetPos
	//Description: This method return the position of first barrier.
	//input: none
	//output: none
	//return: POINT
	///////////////////////////////////////
	virtual POINT GetPos();

	///////////////////////////////////////
	//operator overloading ==
	//Description: if two objects are overlapped with each other, then return
	//input: Bird* b
	//output: current score
	//return: if overlap: return true
	//			else return false
	///////////////////////////////////////
	bool operator==(Bird* b);

	///////////////////////////////////////
	//operator overloading !=
	//Description: if two objects are not overlapped, then return
	//input: Bird* b
	//output: current score
	//return: if overlap: return false
	//			else return true
	///////////////////////////////////////
	bool operator!=(Bird* b);

private:

	int initial_height = 150;
	//barrier's height
	int first_bottom_height = initial_height;
	int first_upper_height = initial_height;
	int second_bottom_height = initial_height;
	int second_upper_height = initial_height;
	int third_bottom_height = initial_height;
	int third_upper_height = initial_height;

	//position of all barriers
	POINT FirstB_bottom;
	POINT FirstB_upper;
	POINT SecondB_bottom;
	POINT SecondB_upper;
	POINT ThirdB_bottom;
	POINT ThirdB_upper;
};

