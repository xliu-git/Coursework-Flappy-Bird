//CPS 400 final project
//File name: FlappyBird.cpp
//Description: This file includes the main method of the game Flappy Bird. User is controlling a bird, which can fly up and down by pressding 'w', 's'
//				or up/down arrow key. The goal for the user is to control the bird and dodge the barriers that moving from right to left. If the bird 
//				hit the barrier, the game is over, and a score will be displayed.

#include <windows.h>
#include <strsafe.h>
#include <iostream>
#include <vector>
#include <stdlib.h>

using std::cout;
using std::endl;
using namespace std;
#include <conio.h> // for user input with getch()
#include "GameObject.h"
#include "ScoreBoard.h"
#include "Barrier.h"
#include "Bird.h"
#include "FilledShapes.h"
#include "OutOfBoundException.h"

#define MAX_THREADS 4
#define MOVE_SIZE 5  // number of pixels to move each time
#define ARROW_UP    72
#define ARROW_DOWN  80

//create vector of pointers
vector<GameObject*> obj;
Barrier* myBarrierPtr = new Barrier();
Bird* myBirdPtr = new Bird();
ScoreBoard* myScoreBoardPtr = new ScoreBoard();

//handle the event of draw bird first
HANDLE hEvent;

int stop = 0;	//indicate game over;

///////////////////////////////
//birdInDomain
//description: if 
//input: int y_pos, represents the bird's y position
//output: none
//return: int, represents the bird's y position
////////////////////////////////////
int birdInDomain(int y_pos)
{
	if (y_pos - 25 - MOVE_SIZE < 2 || y_pos + 25 + MOVE_SIZE > obj[0]->GetWindowHeight() - 28)
	{
		throw OutOfBoundException();
	}
	return y_pos;
}

typedef struct _MyData {
	unsigned int up;
	unsigned int down;
} MYDATA, * PMYDATA;

// THREAD 1
// keep drawing the barriers
DWORD WINAPI ThreadProc1(LPVOID lpParam)
{
	//not using this POINT
	POINT p; 
	p.x = 0;
	p.y = 0;

	//down casting
	Barrier* myBarrier;
	myBarrier = dynamic_cast<Barrier*>(obj[0]);
	if (obj[0] != NULL)
	{
		//wait for bird to be draw first
		WaitForSingleObject(hEvent, INFINITE);
		obj[0]->Draw(p);
	}
	
	return 0;
}

// THREAD 2
// Handles user input. 
DWORD WINAPI ThreadProc2(LPVOID lpParam)
{
	PMYDATA pData;
	int input;

	// Cast the parameter to the correct data type.
	pData = (PMYDATA)lpParam;

	while (1)
	{
		input = _getch();
		if (input == 'w' || input == ARROW_UP) pData->up++;
		if (input == 's' || input == ARROW_DOWN) pData->down++;
	}

	return 0;
}

//Thread 3
//control the bird
DWORD WINAPI ThreadProc3(LPVOID lpParam)
{
	PMYDATA pData;
	POINT p;		//current position
	POINT prevP;	//previous position
	Bird* myBird;

	pData = (PMYDATA)lpParam;
	
	//down casting
	myBird = dynamic_cast<Bird*>(obj[1]);

	//initilize the current bird position and previous bird position
	p.x = obj[1]->GetPos().x;
	p.y = obj[1]->GetPos().y;
	prevP = p;

	int prevUP = 0;
	int prevDOWN = 0;

	//at the beginning of the game, draw the bird in the middle of the screen
	if (prevUP == 0 && prevDOWN == 0)
	{
		obj[1]->Draw(p);
	}

	while (1)
	{
		//if game over, break the loop
		if (stop == 1)
		{
			break;
		}
		
		// if the w key is entered in thread 2, manage the bird upward
		if (pData->up != prevUP)
		{
			prevUP = pData->up;
			obj[1]->ClearObject(prevP, 0);
			myBird->setPosition(p);
			p.y -= MOVE_SIZE;
			prevP = p;
			
			obj[1]->Draw(p);

			// if bird's next position out of bound, then catch the exception and let bird stay at last position
			
			try {
				birdInDomain(p.y);
			}
			catch (OutOfBoundException& outofboundexception)
			{
				cout << "Exception occurred: " << outofboundexception.what() << endl;
				obj[1]->ClearObject(prevP, 0);
				p.y += MOVE_SIZE;
				prevP = p;
				obj[1]->Draw(p);
			}
		}
		// if the s key is entered in thread 2, manage the bird upward
		if (pData->down != prevDOWN)
		{
			prevDOWN = pData->down;
			obj[1]->ClearObject(prevP, 0);
			myBird->setPosition(p);
			p.y += MOVE_SIZE;
			prevP = p;
			
			obj[1]->Draw(p);

			// if bird's next position out of bound, then catch the exception and let bird stay at last position

			try {
				birdInDomain(p.y);
			}
			catch (OutOfBoundException& outofboundexception)
			{
				cout << "Exception occurred: " << outofboundexception.what() << endl;
				obj[1]->ClearObject(prevP, 0);
				p.y -= MOVE_SIZE;
				prevP = p;
				obj[1]->Draw(p);
			}
		}
		//draw bird first
		SetEvent(hEvent);
	}
	return 0;
}

//Thread 4
// keep tracking if the bird hit the barriers or not, if bird hits a barrier, display the current score
DWORD WINAPI ThreadProc4(LPVOID lpParam) {
	Bird* myBird;
	Barrier* myBarrier;

	//down casting
	myBarrier = dynamic_cast<Barrier*>(obj[0]);
	myBird = dynamic_cast<Bird*>(obj[1]);
	Sleep(20);		

	while (1)
	{
		//if hit, game over
		if (*myBarrier == myBird)
		{
			stop = 1;
			obj[0]->setStop(1);
			break;
		}
	}
	return 1;
}


void main()
{
	PMYDATA pData;
	DWORD dwThreadId[MAX_THREADS];
	HANDLE hThread[MAX_THREADS];
	
	// Allocate memory for thread data.
	pData = (PMYDATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
		sizeof(MYDATA));

	if (pData == NULL)
		ExitProcess(2);

	// Initialize global data
	pData->down = 0;
	pData->up = 0;

	obj.push_back(myBarrierPtr);
	obj.push_back(myBirdPtr);
	obj.push_back(myScoreBoardPtr);

	ScoreBoard* myScoreBoard;
	myScoreBoard = dynamic_cast<ScoreBoard*>(obj[2]);

	//create event that draw the bird
	hEvent = CreateEvent(
		NULL,
		false,
		false,
		L"TRY"
	);

	// Create THREAD 1
	hThread[0] = CreateThread(
		NULL,              // default security attributes
		0,                 // use default stack size  
		ThreadProc1,        // thread function 
		NULL,             // argument to thread function 
		0,                 // use default creation flags 
		&dwThreadId[0]);   // returns the thread identifier 

	// Check the return value for success. 
	if (hThread[0] == NULL)
	{
		ExitProcess(0);
	}
	
	// Create THREAD 2
	hThread[1] = CreateThread(
		NULL,              // default security attributes
		0,                 // use default stack size  
		ThreadProc2,        // thread function 
		pData,             // argument to thread function 
		0,                 // use default creation flags 
		&dwThreadId[1]);   // returns the thread identifier 

	// Check the return value for success. 
	if (hThread[1] == NULL)
	{
		ExitProcess(0);
	}
	
	// Create THREAD 3
	hThread[2] = CreateThread(
		NULL,              // default security attributes
		0,                 // use default stack size  
		ThreadProc3,        // thread function 
		pData,             // argument to thread function 
		0,                 // use default creation flags 
		&dwThreadId[2]);   // returns the thread identifier 

	// Check the return value for success. 

	if (hThread[2] == NULL)
	{
		ExitProcess(0);
	}
	
	// Create THREAD 4
	hThread[3] = CreateThread(
		NULL,              // default security attributes
		0,                 // use default stack size  
		ThreadProc4,        // thread function 
		NULL,             // argument to thread function 
		0,                 // use default creation flags 
		&dwThreadId[3]);   // returns the thread identifier 

	// Check the return value for success. 

	if (hThread[3] == NULL)
	{
		ExitProcess(0);
	}
	
	//the beginning of game, until player hit a barrier and game over
	while (1)
	{
		if (stop)
		{
			Sleep(20);
			
			//draw the "game over window"
			POINT result;
			result.x = 100;
			result.y = 100;
			obj[2]->Draw(result);
			Sleep(1000);
			break;
		}
	}

	// Free the memory allocated by the caller for the thread 
	// data structure.
	HeapFree(GetProcessHeap(), 0, pData);
	for (int i = 0; i < MAX_THREADS; i++)
	{
		CloseHandle(hThread[i]);
	}

	//close the event handle
	CloseHandle(hEvent);
	
}
