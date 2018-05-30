#pragma once

#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "main.h"

class Projectile {
public:
	Projectile();
	~Projectile();
	void Render(SDL_Rect background);
	void Fire(int direction, float posX, float posY);
	void CollisionDetection();
	void StopFiring();
	void Initialize(SDL_Renderer *rend);

	float posX, posY;

	SDL_Rect fireRect;
	SDL_Texture *fireTex;
private:
	SDL_Renderer *ren;

	bool firing;
	int fireDir;
};

#endif