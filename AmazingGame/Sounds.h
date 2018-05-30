#pragma once
#ifndef SOUNDS_H
#define SOUNDS_H
#include "main.h"
#include <SDL_mixer.h>

class Sounds {
public:
	Sounds();
	~Sounds();
	void Play(char *name);
private:
	Mix_Chunk *soundEffect;
	Mix_Chunk *playerHurt;
	Mix_Chunk *playerFire;
	Mix_Chunk *playerJump;
	Mix_Chunk *gameOver;
	Mix_Chunk *ghostDie;
};


#endif