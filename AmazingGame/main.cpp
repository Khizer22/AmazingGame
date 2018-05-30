// main.cpp : Defines the entry point for the console application.
//by Khizer Mahboob
#include "stdafx.h"
#include "AmazingGame.h"

int main(int argc, char *argv[])
{
	AmazingGame *mainGame = new AmazingGame();
	mainGame->StartGame();
	delete mainGame;

	cout << endl;
	system("PAUSE");

    return 0;
}
