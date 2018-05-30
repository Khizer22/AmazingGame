#include "stdafx.h"
#include "Projectile.h"

Projectile::Projectile() {

}

Projectile::~Projectile() {
	if (fireTex != NULL) {
		SDL_DestroyTexture(fireTex);
		cout << endl << "Projectile destroyed";
	}
}

void Projectile::Initialize(SDL_Renderer *rend) {
	firing = false;
	fireDir = 0;

	ren = rend;
	posX = 0;
	posY = 0;
	int startingPosX = posX;
	int startingPosY = posY;
	fireRect = { startingPosX,startingPosY,0,0 };
	fireTex = IMG_LoadTexture(ren, "Images/fire.png");
}

void Projectile::Render(SDL_Rect background) {

	if (firing)
		posX += 0.8f * fireDir;

	fireRect.x = background.x + posX;
	fireRect.y = background.y + posY;

	//if (fireRect.x > 0 - fireRect.w && fireRect.x < SCREENWIDTH) { //if within screen
	SDL_RenderCopy(ren, fireTex, NULL, &fireRect);
	//}
}

void Projectile::CollisionDetection() {
	
}

void Projectile::Fire(int direction, float _posX, float _posY) {
	fireDir = direction;
	fireRect.w = 20;
	fireRect.h = 20;
	if (direction == -1)
		direction = 0;
	posX = _posX + (100 * direction);
	posY = _posY + 180;
	firing = true;
}

void Projectile::StopFiring() {
	fireRect.x = NULL;
	fireRect.y = NULL;
	firing = false;
}
