//CPS400 final project
//File name: ScoreBoard.cpp
//Description: This is the implementation file of ScoreBoard class.
//				

#include "ScoreBoard.h"

//constructor
ScoreBoard::ScoreBoard()
{
	//initialize the scoreboard position
	win.x = GetWindowWidth() / 3 ;
	win.y = GetWindowHeight() / 3 ;
}

//set the pen color and brush color and draw the scoreboard
bool ScoreBoard::Draw(POINT p)
{
	fs.SetPenColor(GREEN);
	fs.SetBrushColor(GREEN);

	fs.FilledRectangle(win, 100, 200, "****");
	return true;
}

//score board only appear at the end of game, there is no need for clear
bool ScoreBoard::ClearObject(POINT p, int height)
{
	return true;
}

//get position of scoreboard
POINT ScoreBoard::GetPos()
{
	return win;
}
