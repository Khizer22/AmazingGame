#pragma once
#ifndef AMAZINGGAME_H
#define AMAZINGGAME_H
#include "main.h"
#include "SDLFunctions.h"
#include "Player.h"
#include "Background.h"
#include "Props.h"
#include "Finish.h"
#include "LevelManager.h"
#include "Font.h"
#include "Menu.h"

class AmazingGame {
private:
	SDL_Window *win;
	SDL_Renderer *ren;
	SDL_Rect Viewport;
	SDL_Event event;

	bool gameRunning;

	void InitializeGame();

public:
	AmazingGame();
	~AmazingGame();
	void StartGame();
};

#endif


