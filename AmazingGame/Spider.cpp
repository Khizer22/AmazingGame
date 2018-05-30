#include "stdafx.h"
#include "Spider.h"

Spider::Spider() {
}

Spider::~Spider() {
}

void Spider::Render(SDL_Rect background) {
	if (currentHealth <= 0)
		isDead = true;

	animClip = &currentAnimation[currentFrame / currentFrameRate];

	if (!isDead) {
		enemyRect.x = background.x + posX;
		enemyRect.y = background.y + posY;
		SDL_RenderCopyEx(ren, enemyTex, animClip, &enemyRect, 0, NULL, flip);
	}
	else {
		enemyRect.x = -100;
		enemyRect.y = -100;
	}

	//Animating
	currentFrame++;
	if (currentFrame / currentFrameRate >= 3)
		currentFrame = 0;

	//if ((currentFrame / currentFrameRate) < (startFrame - 1) || (currentFrame / currentFrameRate) > (endFrame - 0.1))
	//currentFrame = (startFrame - 1) * currentFrameRate;

}

void Spider::SetAnimations() {
	//ANIMATIONS
	enemyTex = IMG_LoadTexture(ren, "Images/spider.png");
	int spriteWidth = 84; //per frame
	int spriteHeight = 65;

	int q = 0;
	int y = 0;
	//walk 0-3
	for (int x = 166; x < 500; x = x + spriteWidth)
	{
		currentAnimation[q].x = x;
		currentAnimation[q].y = y;
		currentAnimation[q].w = spriteWidth;
		currentAnimation[q].h = spriteHeight;
		q++;
	}
}

void Spider::CollisionDetection(vector<SDL_Rect> props, vector<bool> isStatic,SDL_Rect playerRect,SDL_Rect projectileRect, vector<SDL_Rect> otherEnemies, SDL_Rect background, int bLength, int enemyAmount) {

	//Colliding with player
	if (playerRect.x + playerRect.w - 40 > enemyRect.x
		&& playerRect.x + 40 < enemyRect.x + enemyRect.w
		&& playerRect.y + playerRect.h - 20 > enemyRect.y
		&& playerRect.y + 20 < enemyRect.y + enemyRect.h
		)
	{
		if (playerRect.y + playerRect.h < enemyRect.y + enemyRect.h / 2)
			posX = posX;
		else if (playerRect.x + playerRect.w - 35 < enemyRect.x + enemyRect.w / 2)
			posX = posX;
		else if (playerRect.x + 35 > enemyRect.x + enemyRect.w / 2)
			posX = posX;
	}
	else if (playerRect.x + playerRect.w - 40 < enemyRect.x) {
		posX -= 0.1f;
		flip = SDL_FLIP_HORIZONTAL;
	}
	else if (playerRect.x > enemyRect.x + enemyRect.w - 40) {
		posX += 0.1f;
		flip = SDL_FLIP_NONE;
	}

	//Colliding with other Enemies 
	for (int i = 0; i < enemyAmount ; i++) {
		if (i != GetID()) {
			if (enemyRect.x + enemyRect.w > otherEnemies.at(i).x
				&& enemyRect.x < otherEnemies.at(i).x + otherEnemies.at(i).w
				&& enemyRect.y + enemyRect.h  > otherEnemies.at(i).y
				&& enemyRect.y < otherEnemies.at(i).y + otherEnemies.at(i).h
				)
			{
				/*  if collding from above
				if (propsRect.y + propsRect.h  < otherPropsRect[i].y + otherPropsRect[i].h / 2)
				{
				//dont really need right now
				}  */
				if (enemyRect.x + enemyRect.w < otherEnemies.at(i).x + otherEnemies.at(i).w / 2) {
					posX -= 1;
				}
				else if (enemyRect.x > otherEnemies.at(i).x + otherEnemies.at(i).w / 2) {
					posX += 1;
				}
			}
		}
	}

	//Colliding with Props
	for (int i = 0; i < props.size(); i++) {
		if (isStatic.at(i) == true) {
			if (enemyRect.x + enemyRect.w > props.at(i).x
				&& enemyRect.x < props.at(i).x + props.at(i).w
				&& enemyRect.y + enemyRect.h  > props.at(i).y
				&& enemyRect.y < props.at(i).y + props.at(i).h
				)
			{
				/*  if collding from above
				if (propsRect.y + propsRect.h  < otherPropsRect[i].y + otherPropsRect[i].h / 2)
				{
				//dont really need right now
				}  */
				if (enemyRect.x + enemyRect.w < props.at(i).x + props.at(i).w / 2) {
					posX -= 1;
				}
				else if (enemyRect.x > props.at(i).x + props.at(i).w / 2) {
					posX += 1;
				}
			}
		}
		
	}

	//Colliding with Projeciles
	if (projectileRect.x + projectileRect.w > enemyRect.x
		&& projectileRect.x  < enemyRect.x + enemyRect.w
		&& projectileRect.y + projectileRect.h  > enemyRect.y
		&& projectileRect.y  < enemyRect.y + enemyRect.h
		)
	{
		if (invul == false)
			takingDamage = true;
	}
	if (takingDamage)
		TakeDamage();

	//Colliding with Borders
	if (enemyRect.x + sizeWidth > background.x + bLength) {
		posX -= 1;
	}
	else if (enemyRect.x < background.x)
		posX += 1;

}

void Spider::TakeDamage() {

	if (invul == false) {
		SDL_SetTextureColorMod(enemyTex, 100, 0, 0);
		currentHealth -= 10;
		invul = true;
		if (flip == SDL_FLIP_HORIZONTAL)
		{
			posX += 30;
		}
		else posX -= 30;
	}
	if (invul == true)
		invulTime += 0.01f;

	if (invulTime > 7)
	{
		takingDamage = false;
		SDL_SetTextureColorMod(enemyTex, 255, 255, 255);
		invulTime = 0;
		invul = false;
	}
}