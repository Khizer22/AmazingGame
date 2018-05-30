#pragma once

#ifndef PROPS_H
#define PROPS_H
#include "main.h"
#include "Player.h"


class Props {
public:
	Props(SDL_Renderer*,char*,int,int,int,int,bool,bool,int);
	Props();
	~Props();

	void Render(SDL_Rect, SDL_Rect, vector<SDL_Rect> otherPropsRect,vector<bool> _isTrigger,int,int);
	void InitializeProps();

	SDL_Rect propsRect;
	bool isTrigger;
	bool isStatic;
	int ID;
private:
	SDL_Renderer *ren;
	SDL_Texture *propsTex = NULL;
	SDL_Rect propsAnimClip;
	SDL_Rect background;

	int startingX, startingY, sizeWidth, sizeHeight;
	int posX, posY;
	char *texFileName;
	//bool isAnimated;

};

#endif