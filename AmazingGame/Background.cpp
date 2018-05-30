#include "stdafx.h"
#include "Background.h"

Background::Background() {
}

Background::~Background() {
	if (backgroundTex != NULL) {
		SDL_DestroyTexture(backgroundTex);
		cout << endl << "background deleted";
	}
}

void Background::InitializeBackground(SDL_Renderer *rend,char *name,int x, int y, int _length, int _height) {
	ren = rend;
	length = _length;
	height = _height;
	backgroundTex =IMG_LoadTexture(rend,name);
	backgroundRect = { x,y,length,height };
}

void Background::Render(Player *player, SDL_Rect Viewport) {
	//background follows player
	backgroundRect.x = -((player->GetPosX() + player->sizeWidth / 2) - SCREENWIDTH / 2);

	/* dont need this yet, will be required on bigger levels
	backgroundRect.y = (player->GetPosY() + player->sizeHeight / 2) - SCREENHEIGHT / 2; 
	*/

	//background constraints to be within screen
	
	if (backgroundRect.x > 0)
		backgroundRect.x = 0;

	if (backgroundRect.y > 0)
		backgroundRect.y = 0;

	if (backgroundRect.x < -(length)+SCREENWIDTH)
		backgroundRect.x = -(length)+SCREENWIDTH;

	if (backgroundRect.y > height - SCREENHEIGHT)
		backgroundRect.y = height - SCREENHEIGHT;

	SDL_RenderCopy(ren, backgroundTex, NULL, &backgroundRect);
}

int Background::GetLength() {
	return length;
}

int Background::GetHeight() {
	return height;
}