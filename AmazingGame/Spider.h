#pragma once
#ifndef SPIDER_H
#define SPIDER_H
#include "main.h"
#include "Enemies.h"

class Spider : public Enemies {
public:
	Spider();
	~Spider();

	//Abstract derived from Enemies
	void SetAnimations();
	void CollisionDetection(vector<SDL_Rect> props, vector<bool> isStatic,SDL_Rect playerRect,SDL_Rect projectileRect, vector<SDL_Rect> otherEnemies, SDL_Rect background, int bLength, int enemyAmount);
	void Render(SDL_Rect background);
	void TakeDamage();

private:
	SDL_Rect currentAnimation[4];
};

#endif