#include "stdafx.h"
#include "Menu.h"

Menu::Menu(SDL_Renderer *rend,LevelManager *_levelManager) {
	ren = rend;
	font = new Font(ren);
	levelManager = _levelManager;
	paused = false;
}
Menu::Menu() {
	cout << "menu created";
}

Menu::~Menu() {
	//delete font;
	for (int i = 0; i < menuTextures.size(); i++) {
		if (menuTextures.at(i) != NULL)
			SDL_DestroyTexture(menuTextures.at(i));
	}
	cout << endl << "Menu Deleted";
}

void Menu::InitializeMenu()
{
	//NOT DESTROYING TEXTURE ,INSTEAD OVERWRITING TEXTURE INSTEAD I THINK ) - nvm ******remove this later
	//Start Game
	font->LoadFont("Start Game",300, 100, 300, 100);
	menuTextures.push_back(font->fontTex);
	menuRects.push_back(font->fontRect);

	//Quit Game
	font->LoadFont("Quit", 300, 200, 150, 100);
	menuTextures.push_back(font->fontTex);
	menuRects.push_back(font->fontRect);

	//PAUSE MENU
	//Continue
	font->LoadFont("Continue", 300, 100, 300, 100);
	menuTextures.push_back(font->fontTex);
	menuRects.push_back(font->fontRect);

	//Exit Game
	font->LoadFont("Exit Game", 300, 200, 300, 100);
	menuTextures.push_back(font->fontTex);
	menuRects.push_back(font->fontRect);

	font->LoadFont("YOU ARE DEAD", 300, 200, 350, 100);
	menuTextures.push_back(font->fontTex);
	menuRects.push_back(font->fontRect);

	font->LoadFont("Game Finished, woot!", 150, 200, 550, 100);
	menuTextures.push_back(font->fontTex);
	menuRects.push_back(font->fontRect);

	//font->~Font(); //deleting it now since it is not required later //doesnt work if I do, darn
}

void Menu::ActivateMenu(int menuType) {
	if (menuType == 1) {
		for (int i = 0; i < menuRects.size() - 4; i++)
			SDL_RenderCopy(ren, menuTextures.at(i), NULL, &menuRects.at(i));
	}
	else if (menuType == 2) {
		for (int i = 2; i < menuRects.size() - 2; i++)
			SDL_RenderCopy(ren, menuTextures.at(i), NULL, &menuRects.at(i));
	}
}

void Menu::HandleEvents(SDL_Event& e, Player *player, bool &gameRunning) {
	int mouseX;
	int mouseY;

	switch (e.type) {
	case SDL_MOUSEBUTTONDOWN:
		switch (e.button.button) {

		case SDL_BUTTON_LEFT:
			SDL_GetMouseState(&mouseX, &mouseY);

			if (mouseX > menuRects.at(0).x && mouseX < menuRects.at(0).x + menuRects.at(0).w &&
				mouseY > menuRects.at(0).y && mouseY < menuRects.at(0).y + menuRects.at(0).h
				)
				levelManager->TransverseLevel(1, player); //Start Game

			else if (mouseX > menuRects.at(1).x && mouseX < menuRects.at(1).x + menuRects.at(1).w &&
					mouseY > menuRects.at(1).y && mouseY < menuRects.at(1).y + menuRects.at(1).h
				)
				gameRunning = false;                       //Exit Game

			break;
		default:
			break;
		}
	}
}

void Menu::StartGame() {
	int level = 1;
}

void Menu::QuitGame() {
	bool gameRunning = false;
}

void Menu::PauseMenu(SDL_Event& e, bool &gameRunning) {
	int mouseX;
	int mouseY;

	switch (e.type) {
	case SDL_MOUSEBUTTONDOWN:
		switch (e.button.button) {

		case SDL_BUTTON_LEFT:
			SDL_GetMouseState(&mouseX, &mouseY);
			if (mouseX > menuRects.at(2).x && mouseX < menuRects.at(2).x + menuRects.at(2).w &&
				mouseY > menuRects.at(2).y && mouseY < menuRects.at(2).y + menuRects.at(2).h
				)
				paused = false;

			else if (mouseX > menuRects.at(3).x && mouseX < menuRects.at(3).x + menuRects.at(3).w &&
				mouseY > menuRects.at(3).y && mouseY < menuRects.at(3).y + menuRects.at(3).h
				)
				gameRunning = false;

			break;
		default:
			break;
		}
	}
	
}

void Menu::PlayerDead() {
	SDL_RenderCopy(ren, menuTextures.at(4), NULL, &menuRects.at(4));
}

void Menu::Win() {
	SDL_RenderCopy(ren, menuTextures.at(5), NULL, &menuRects.at(5));
}