#pragma once
#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "main.h"
#include "Player.h"

class Background {
public:
	Background();
	~Background();

	void Render(Player *player, SDL_Rect Viewport);
	void InitializeBackground(SDL_Renderer *ren,char *name,int x,int y,int length,int height);
	int GetLength();
	int GetHeight();

	SDL_Rect backgroundRect;

private:
	int length;
	int height;

	SDL_Texture *backgroundTex;
	SDL_Renderer *ren;


};

#endif