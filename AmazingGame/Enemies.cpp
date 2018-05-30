#include "stdafx.h"
#include "Enemies.h"

Enemies::Enemies() {
	frameRate = 900; // default animation speed
	currentFrameRate = frameRate; // current animations speed
	currentFrame = 0; // the animation frame that is playing
}

Enemies::~Enemies() {
	if (enemyTex != NULL) {
		SDL_DestroyTexture(enemyTex);
		cout << endl << name << " destroyed";
	}
}

void Enemies::Initialize(SDL_Renderer *rend, char *_name,int _ID,int health) {
	name = _name;
	ren = rend;
	ID = _ID;
	invul = false;
	invulTime = 0;
	takingDamage = false;
	maxHealth = health;
	currentHealth = maxHealth;
	isDead = false;
}

void Enemies::SetRect(int _posX, int _posY, int _sizeWidth, int _sizeHeight) {
	//SDL_RECT
	startingX = _posX;
	startingY = _posY;
	posX = startingX;
	posY = startingY;
	sizeWidth = _sizeWidth;
	sizeHeight = _sizeHeight;
	enemyRect = { startingX,startingY,sizeWidth,sizeHeight };
}

void Enemies::SetMoveSpeed(int _moveSpeed) {
	moveSpeed = _moveSpeed;
}

int Enemies::GetID() {
	return ID;
}