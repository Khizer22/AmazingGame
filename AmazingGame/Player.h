#pragma once

#ifndef PLAYER_H
#define PLAYER_H
#include "main.h"
#include "Projectile.h"
#include "Sounds.h"

class Player {
public:
	Player(string, SDL_Renderer*);
	~Player();
	
	void CollisionDetection(vector<SDL_Rect> enemyRect,int enemyAmount,vector<SDL_Rect> ,vector<bool>,vector<bool>,int,int,int);
	void HandleEvent(SDL_Event& e);
	void Move(SDL_Rect);
	void Render();
	void SpawnPlayer(int x,int y);

	SDL_Rect GetProjectileRect();

	float GetPosX();
	float GetPosY();

	string name;
	SDL_Rect playerRect;

	bool isDead;
	int sizeHeight;
	int sizeWidth;

private:
	int maxHealth;
	int currentHealth;
	float moveSpeed;
	float maxSpeed;
	float jumpSpeed;
	float currentMoveSpeed;
	int startingX;
	int startingY;
	int blinkTime;
	float posX, posY;

	int startFrame;
	int endFrame;

	int currentFrame;
	int currentFrameRate;
	int frameRate;
	const int runFrames = 25; //dont really use need

	SDL_Renderer *ren;
	SDL_Rect *animClip;
	SDL_Texture *playerTexture;
	SDL_Rect currentAnimation[25];
	SDL_RendererFlip flip;
	SDL_Rect backgroundRect;
	//DAMAGE/ANIMATION
	int damageDirection;
	bool takingDamage;
	float invulTime;
	bool invulnerable;
	int TakeDamage(int direction);
	void Dead();
	void initializeAnimations();
	void PlayAnimation(int, int);

	//STATS
	float gravity;
	float gravityInc;
	bool moveRight;
	bool moveLeft;
	bool running;
	bool jumping;
	bool grounded;
	bool onObject;
	bool blah;
	const Uint8* currentKeyStates;

	//FIRE
	Projectile *projectile;
	bool firing;
	float fireTime;

	//Sounds
	Sounds sounds;

	int bLength;
	int bHeight;
};

#endif