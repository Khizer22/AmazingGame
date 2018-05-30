#include "stdafx.h"
#include "Font.h"

Font::Font(SDL_Renderer *rend){
	ren = rend;
	fontTex = NULL;
	text = "";
}

Font::Font() {

}

Font::~Font() {
	if (fontTex != NULL) {
		SDL_DestroyTexture(fontTex);
		cout << endl << "text: \"" << text << "\" destroyed";
	}
}

void Font::LoadFont(char* _text,int x,int y, int w,int h) {
	text = _text;
	TTF_Font *font = TTF_OpenFont("Fonts/MyFont.ttf", 24);
	SDL_Color color = { 120, 0, 100 };

	SDL_Surface *Surface = TTF_RenderText_Solid(font, text, color);
	fontTex = SDL_CreateTextureFromSurface(ren, Surface);
	SDL_FreeSurface(Surface);
	TTF_CloseFont(font);

	fontRect = { x,y,w,h };
}

void Font::Render() {
	SDL_RenderCopy(ren,fontTex,NULL,&fontRect);
}

int Font::GetHeight() {
	return 1;
}

int Font::GetWidth() {
	return 1;
}