#include "stdafx.h"
#include "SDLFunctions.h"

SDL_Texture *loadTexture(SDL_Renderer *ren, char *imageName) {

	SDL_Surface *image = IMG_Load(imageName);
	SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, image);
	SDL_FreeSurface(image);

	return tex;
}
