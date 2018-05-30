#pragma once
#ifndef ENEMIES_H
#define ENEMIES_H
#include "main.h"
class Enemies {
public:
	//Enemies(SDL_Renderer *ren,char *name, int startingX, int startingY,int enemyType);
	Enemies();
	~Enemies();
	
	void SetMoveSpeed(int _moveSpeed);
	void SetRect(int posX, int posY,int sizeWidth,int sizeHeight);
	void Initialize(SDL_Renderer *rend, char *_name,int _ID,int health);

	int GetID();

	virtual void Render(SDL_Rect background) = 0;
	virtual void CollisionDetection(vector<SDL_Rect> props, vector<bool> isStatic,SDL_Rect playerRect, SDL_Rect projectileRect, vector<SDL_Rect> otherEnemies, SDL_Rect background, int bLength, int enemyAmount) = 0;
	virtual void SetAnimations() = 0;
	virtual void TakeDamage() = 0;

	SDL_Renderer *ren;
	SDL_Texture *enemyTex;
	SDL_Rect enemyRect;
	SDL_Rect *animClip;
	SDL_RendererFlip flip;
	
	int sizeWidth;
	float posX;
	float posY;
	int startingX;
	int startingY;
	int currentFrameRate;
	int currentFrame;
	char *name;

	//Damage
	bool invul;
	float invulTime;
	bool takingDamage;
	int maxHealth;
	int currentHealth;
	bool isDead;
private:
	int frameRate;		
	int sizeHeight;
	float moveSpeed;
	int ID;
	//float jumpSpeed;	

	

};

#endif