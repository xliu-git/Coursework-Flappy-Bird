//CPS400 final project
//File name: ScoreBoard.h
//Description: This is the header file of ScoreBoard class.
//				methods description is shown below
#include "GameObject.h"

class ScoreBoard : public GameObject
{

public:
	
	//default constructor
	ScoreBoard();

	/////////////////////////////////////////
	//Draw()
	//Description: This method set up the brush color and pen color, and draw the scoreboard
	//input: POINT p (inherited from class GameObject)
	//output: none
	//return: bool
	///////////////////////////////////////
	virtual bool Draw(POINT p);

	///////////////////////////////////////
	//ClearObject
	//Description: This method clear the object on the screen
	//input: POINT p, int param  (as inherited from GameObject class)
	//output: none
	//return: bool
	///////////////////////////////////////
	virtual bool ClearObject(POINT p, int param);

	///////////////////////////////////////
	//getPos
	//Description: This method return the position of the scoreboard
	//input: none
	//output: none
	//return: POINT, representing the position of scoreboard
	///////////////////////////////////////
	virtual POINT GetPos();


private:
	
	POINT win;		//position of scoreboard window
};

