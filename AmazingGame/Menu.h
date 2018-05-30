#pragma once
#ifndef MENU_H
#define MENU_H
#include "main.h"
#include "Font.h"
#include "LevelManager.h"
#include <cmath>

class Menu {
public :
	Menu(SDL_Renderer*,LevelManager*);
	Menu();
	~Menu();

	bool paused;

	void PlayerDead();
	void Win();

	void HandleEvents(SDL_Event& e,Player *player,bool &gameRunning);
	void PauseMenu(SDL_Event& e, bool &gameRunning);
	void ActivateMenu(int menuType);
	void InitializeMenu();
private:
	SDL_Renderer *ren;
	void StartGame();
	void QuitGame();

	Font *font;
	LevelManager *levelManager;

	vector<SDL_Rect> menuRects;
	vector<SDL_Texture*> menuTextures;



};


#endif

