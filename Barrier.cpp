//CPS400 final project
//File Name:Barrier.cpp
//Description: This this the implementation of Barrier class.

#include "Barrier.h"
#include <thread>
#include <time.h>
#include <stdlib.h>

#define B_MOVE_SIZE 2

using namespace std;

//default constructor
Barrier::Barrier(){}

//set the pen and brush color and call the function to draw barriers
bool Barrier::Draw(POINT p)
{
	fs.SetPenColor(borderColor);
	fs.SetBrushColor(fillColor);
	GenBarrier();
	
	return true;
}


//generate barriers and draw
void Barrier::GenBarrier()
{
	srand((unsigned int)time(0));

	//randomize three barrier's division of upper and lower height
	//initially, first three barriers' heights are 150
	int first = rand() % 6 + 1;
	int second = rand() % 6 + 1;
	int third = rand() % 6 + 1;

	//initially first barrier start at 170
	FirstB_bottom.x = 170;				
	FirstB_bottom.y = GetWindowHeight() - initial_height - 2 * borderWidth - 7;	
	FirstB_upper.x = 170;
	FirstB_upper.y = 2;
	
	//initially second barrier start at 420
	SecondB_bottom.x = 420; 
	SecondB_bottom.y = GetWindowHeight() - initial_height - 2 * borderWidth - 7;
	SecondB_upper.x = 420;
	SecondB_upper.y = 2;

	//initially third barrier start at 670
	ThirdB_bottom.x = 670;
	ThirdB_bottom.y = GetWindowHeight() - initial_height - 2 * borderWidth - 7;
	ThirdB_upper.x = 670;
	ThirdB_upper.y = 2;

	//initially, draw all barriers.
	fs.FilledRectangle(FirstB_bottom, initial_height, 100);
	fs.FilledRectangle(FirstB_upper, initial_height, 100);

	fs.FilledRectangle(SecondB_bottom, initial_height, 100);
	fs.FilledRectangle(SecondB_upper, initial_height, 100);

	fs.FilledRectangle(ThirdB_bottom, initial_height, 100);
	fs.FilledRectangle(ThirdB_upper, initial_height, 100);

	//labels are used to count the barriers that has been passed.
	int label1 = 0, label2 = 0, label3 = 0;

	//inside the loop, make all barriers moving towards left and generate random heights
	while (1)
	{
		//if game over, then stop
		if (GameObject::stop == 1)
		{
			break;
		}

		//clear barriers at last position.
		ClearObject(FirstB_bottom, first_bottom_height);
		ClearObject(FirstB_upper, first_upper_height);

		ClearObject(SecondB_bottom, second_bottom_height);
		ClearObject(SecondB_upper, second_upper_height);

		ClearObject(ThirdB_bottom, third_bottom_height);
		ClearObject(ThirdB_upper, third_upper_height);

		//set barriers' position at next position.
		fs.SetPenColor(BLUE);
		fs.SetBrushColor(BLUE);
		FirstB_bottom.x -= B_MOVE_SIZE;	
		FirstB_upper.x -= B_MOVE_SIZE;
		SecondB_bottom.x -= B_MOVE_SIZE;	
		SecondB_upper.x -= B_MOVE_SIZE;
		ThirdB_bottom.x -= B_MOVE_SIZE;	
		ThirdB_upper.x -= B_MOVE_SIZE;

		//draw barrier's at next position
		fs.FilledRectangle(FirstB_bottom, first_bottom_height, 100);
		fs.FilledRectangle(FirstB_upper, first_upper_height, 100);

		fs.FilledRectangle(SecondB_bottom, second_bottom_height, 100);
		fs.FilledRectangle(SecondB_upper, second_upper_height, 100);

		fs.FilledRectangle(ThirdB_bottom, third_bottom_height, 100);
		fs.FilledRectangle(ThirdB_upper, third_upper_height, 100);
		Sleep(20);
		
		//if first barrier hit the most left of the game window
		if (FirstB_bottom.x <= 2)
		{
			//indicate first barrier passed.
			label1 = 1;
			//make the first barrier disapper
			ClearObject(FirstB_bottom, first_bottom_height);
			ClearObject(FirstB_upper, first_upper_height);

			//keep moving the second and third barriers
			while (1) 
			{
				if (GameObject::stop == 1)
				{
					break;
				}

				ClearObject(SecondB_bottom, second_bottom_height);
				ClearObject(SecondB_upper, second_upper_height);

				ClearObject(ThirdB_bottom, third_bottom_height);
				ClearObject(ThirdB_upper, third_upper_height);

				fs.SetPenColor(BLUE);
				fs.SetBrushColor(BLUE);
				SecondB_bottom.x -= B_MOVE_SIZE;
				SecondB_upper.x -= B_MOVE_SIZE;
				ThirdB_bottom.x -= B_MOVE_SIZE;	
				ThirdB_upper.x -= B_MOVE_SIZE;

				fs.FilledRectangle(SecondB_bottom, second_bottom_height, 100);
				fs.FilledRectangle(SecondB_upper, second_upper_height, 100);

				fs.FilledRectangle(ThirdB_bottom, third_bottom_height, 100);
				fs.FilledRectangle(ThirdB_upper, third_upper_height, 100);
				Sleep(20);

				//until the third barrier move to it's initial position, break the loop
				if (ThirdB_bottom.x == 420)
				{
					break;
				}
			}

			//generate new barrier's height
			first = rand() % 6 + 1;
			first_bottom_height = 300 / first;
			first_upper_height = GetWindowHeight() - 250 - first_bottom_height;

			//new barrier will appear at the right of the game window
			FirstB_bottom.x = 670;
			FirstB_bottom.y = GetWindowHeight() - first_bottom_height - 2 * borderWidth - 7;
			FirstB_upper.x = 670;
			FirstB_upper.y = 2;
			fs.FilledRectangle(FirstB_bottom, first_bottom_height, 100);
			fs.FilledRectangle(FirstB_upper, first_upper_height, 100);
		}
		
		//same for second barrier
		if (SecondB_bottom.x <= 2)
		{
			//indicate second barrier passed
			label2 = 1;
			ClearObject(SecondB_bottom, second_bottom_height);
			ClearObject(SecondB_upper, second_upper_height);
			while (1)
			{
				if (GameObject::stop)
				{
					break;
				}
				ClearObject(FirstB_bottom, first_bottom_height);
				ClearObject(FirstB_upper, first_upper_height);

				ClearObject(ThirdB_bottom, third_bottom_height);
				ClearObject(ThirdB_upper, third_upper_height);

				fs.SetPenColor(BLUE);
				fs.SetBrushColor(BLUE);
				FirstB_bottom.x -= B_MOVE_SIZE;
				FirstB_upper.x -= B_MOVE_SIZE;
				ThirdB_bottom.x -= B_MOVE_SIZE;	
				ThirdB_upper.x -= B_MOVE_SIZE;

				fs.FilledRectangle(FirstB_bottom, first_bottom_height, 100);
				fs.FilledRectangle(FirstB_upper, first_upper_height, 100);

				fs.FilledRectangle(ThirdB_bottom, third_bottom_height, 100);
				fs.FilledRectangle(ThirdB_upper, third_upper_height, 100);
				Sleep(20);

				if (FirstB_bottom.x == 420)
				{
					break;
				}
			}

			second = rand() % 6 + 1;
			second_bottom_height = 300 / second;
			second_upper_height = GetWindowHeight() - 250 - second_bottom_height;

			SecondB_bottom.x = 670;
			SecondB_bottom.y = GetWindowHeight() - second_bottom_height - 2 * borderWidth - 7;
			SecondB_upper.x = 670;
			SecondB_upper.y = 2;
			fs.FilledRectangle(SecondB_bottom, second_bottom_height, 100);
			fs.FilledRectangle(SecondB_upper, second_upper_height, 100);
		}
		
		//same for third barrier
		if (ThirdB_bottom.x <= 2)
		{
			//indicate third barrier passed
			label3 = 1;
			//if one round(every three barriers) is passed
			if (label1 && label2 && label3) {
				GameObject::numBarriers = GameObject::numBarriers + 3;
				
				//reset the label flag
				label1 = 0;
				label2 = 0;
				label3 = 0;
			}

			ClearObject(ThirdB_bottom, third_bottom_height);
			ClearObject(ThirdB_upper, third_upper_height);
			while (1)
			{
				if (GameObject::stop == 1)
				{
					break;
				}
				ClearObject(FirstB_bottom, first_bottom_height);
				ClearObject(FirstB_upper, first_upper_height);

				ClearObject(SecondB_bottom, second_bottom_height);
				ClearObject(SecondB_upper, second_upper_height);



				fs.SetPenColor(BLUE);
				fs.SetBrushColor(BLUE);
				FirstB_bottom.x -= B_MOVE_SIZE;	
				FirstB_upper.x -= B_MOVE_SIZE;
				SecondB_bottom.x -= B_MOVE_SIZE;	
				SecondB_upper.x -= B_MOVE_SIZE;

				fs.FilledRectangle(FirstB_bottom, first_bottom_height, 100);
				fs.FilledRectangle(FirstB_upper, first_upper_height, 100);

				fs.FilledRectangle(SecondB_bottom, second_bottom_height, 100);
				fs.FilledRectangle(SecondB_upper, second_upper_height, 100);

				Sleep(20);

				if (SecondB_bottom.x == 420)
				{
					break;
				}
			}

			third = rand() % 6 + 1;
			third_bottom_height = 300 / third;
			third_upper_height = GetWindowHeight() - 250 - third_bottom_height;

			ThirdB_bottom.x = 670;
			ThirdB_bottom.y = GetWindowHeight() - third_bottom_height - 2 * borderWidth - 7;
			ThirdB_upper.x = 670;
			ThirdB_upper.y = 2;
			fs.FilledRectangle(ThirdB_bottom, third_bottom_height, 100);
			fs.FilledRectangle(ThirdB_upper, third_upper_height, 100);
		}
	}
}


//draw the object with the same color as background
bool Barrier::ClearObject(POINT p, int height)
{
	fs.SetPenColor(ORANGE);
	fs.SetBrushColor(ORANGE);
	fs.FilledRectangle(p, height, 100);

	return true;
}


//return the position of First bottom barrier
POINT Barrier::GetPos()
{
	return FirstB_bottom;
}

//overloading ==
bool Barrier::operator==(Bird* b)
{
	//if bird hit the first barrier, update score and return
	if ((b->GetPos().y - b->getRadius() < this->first_upper_height || b->GetPos().y + b->getRadius() > this->FirstB_bottom.y) && b->GetPos().x + b->getRadius() > this->FirstB_bottom.x && b->GetPos().x + b->getRadius() < this->FirstB_bottom.x + 100) {
		cout << "score:" << GameObject::numBarriers + 3 << endl;
		return true;
	}
	//if bird hit the second barrier, update score and return
	if ((b->GetPos().y - b->getRadius() < this->second_upper_height || b->GetPos().y + b->getRadius() > this->SecondB_bottom.y) && b->GetPos().x + b->getRadius() > this->SecondB_bottom.x && b->GetPos().x + b->getRadius() < this->SecondB_bottom.x + 100) {
		cout << "score:" << GameObject::numBarriers + 1 << endl;
		return true;
	}
	//if bird hit the third barrier, update score and return
	if ((b->GetPos().y - b->getRadius() < this->third_upper_height || b->GetPos().y + b->getRadius() > this->ThirdB_bottom.y) && b->GetPos().x + b->getRadius() > this->ThirdB_bottom.x && b->GetPos().x + b->getRadius() < this->ThirdB_bottom.x + 100) {
		cout << "score:" << GameObject::numBarriers + 2 << endl;
		return true;
	}

	return false;
}

//negation of result from ==
bool Barrier::operator!=(Bird* b)
{
	if (*this == b) return false;
	else return true;
}