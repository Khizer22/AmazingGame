#pragma once

#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H
#include "main.h"
#include "Props.h"
#include "Player.h"
#include "Ghost.h"
#include "Spider.h"
#include "Background.h"

class LevelManager {
public:
	LevelManager(SDL_Renderer*);
	LevelManager();
	~LevelManager();

	void SetLevel(int,Player*);
	//void Update();
	void RenderForeground();
	void RenderBackground();
	int GetLevel();
	void TransverseLevel(int,Player*);

	vector<Props> props;
	vector<Enemies*> enemies;
	Background background;
	bool levelLoaded;

	int currentLevel;
	int maxLevel;
private:
	SDL_Renderer *ren;
	vector<Props> temp;
	vector<Enemies*> tempEnemies;

	int level;
	int ID;
	
	int GetID();
};



#endif