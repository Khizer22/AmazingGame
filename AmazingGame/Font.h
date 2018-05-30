#pragma once
#ifndef FONT_H
#define FONT_H
#include "main.h"
class Font {
	friend class Menu;
public:
	Font(SDL_Renderer*);
	Font();
	~Font();
	
	void LoadFont(char* _text,int x,int y,int w, int h);
	void Render();

	int GetWidth();
	int GetHeight();
private:
	char* text;
	stringstream ss;
	int x;
	int y;

	SDL_Rect fontRect;
	SDL_Renderer *ren;
	SDL_Texture *fontTex;

};

#endif
