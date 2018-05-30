#pragma once
#ifndef GHOST_H
#define GHOST_H
#include "main.h"
#include "Enemies.h"
#include "Sounds.h"

class Ghost : public Enemies {
public:
	Ghost();
	~Ghost();

	//Abstract derived from Enemies
	void SetAnimations(); 
	void CollisionDetection(vector<SDL_Rect> props, vector<bool> isStatic,SDL_Rect playerRect, SDL_Rect projectileRect, vector<SDL_Rect> otherEnemies, SDL_Rect background,int bLength, int enemyAmount);
	void Render(SDL_Rect background); 
	void TakeDamage();

private:	
	SDL_Rect currentAnimation[3];
	Sounds sounds;
};

#endif