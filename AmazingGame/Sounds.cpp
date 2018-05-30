#include "stdafx.h"
#include "Sounds.h"

Sounds::Sounds() {
	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
	soundEffect = Mix_LoadWAV("Sounds/footSteps.wav");
	playerHurt = Mix_LoadWAV("Sounds/hurt.wav");
	playerFire = Mix_LoadWAV("Sounds/fire.wav");
	playerJump = Mix_LoadWAV("Sounds/jump.wav");
	gameOver = Mix_LoadWAV("Sounds/gameOver.wav");
	ghostDie = Mix_LoadWAV("Sounds/ghostDie.wav");
}
Sounds::~Sounds() {
	Mix_FreeChunk(soundEffect);
	Mix_FreeChunk(playerHurt);
	Mix_FreeChunk(playerFire);
	Mix_FreeChunk(playerJump);
	Mix_FreeChunk(gameOver);
	Mix_FreeChunk(ghostDie);
	soundEffect = NULL;
	playerHurt = NULL;
	playerFire = NULL;
	playerJump = NULL;
	gameOver = NULL;
	ghostDie = NULL;

	cout << endl << "Sounds Freed";
}

void Sounds::Play(char *name) {	
	if (name == "footSteps")
		Mix_PlayChannel(-1, soundEffect, 0);
	else if (name == "hurt")
		Mix_PlayChannel(-1, playerHurt, 0);
	else if (name == "fire")
		Mix_PlayChannel(-1, playerFire, 0);
	else if (name == "jump")
		Mix_PlayChannel(-1, playerJump, 0);
	else if (name == "gameOver")
		Mix_PlayChannel(-1, gameOver, 0);
	else if (name == "ghostDie")
		Mix_PlayChannel(-1, ghostDie, 0);
}

