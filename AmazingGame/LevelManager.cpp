#include "stdafx.h"
#include "LevelManager.h"

LevelManager::LevelManager(SDL_Renderer *rend) {
	ren = rend;
	levelLoaded = false;
	ID = -1;
	currentLevel = 0;
	maxLevel = 4;
}
LevelManager::LevelManager() {}

LevelManager::~LevelManager() {
	for (int i = 0; i < enemies.size(); i++) {
		enemies.at(i)->~Enemies();
	}
	cout << endl << "Level Manager Deleted";
}

void LevelManager::SetLevel(int _level,Player* player) {
	level = _level;

	if (levelLoaded == false) {
		if (level == 0)
		{
			//Background
			background.InitializeBackground(ren, "Images/blacknesssssssssssss.jpg", 0, -120, 1279, 720);
		}
		else if (level == 1) //stage 1
		{			
			//Background
			background.InitializeBackground(ren,"Images/background.jpg",0,-120, 1279, 720);
			
			//Enemies
			tempEnemies = { {} };

			tempEnemies.at(0) = new Ghost();

			enemies.swap(tempEnemies);

			for (int i = 0; i < enemies.size(); i++) {
				enemies.at(i)->Initialize(ren, "GhostMang", i,30);
				enemies.at(i)->SetRect(30 * ((1) * 50), 230, 100, 100);
				enemies.at(i)->SetMoveSpeed(10);
				enemies.at(i)->SetAnimations();
			}			

			//Props
			//props.clear();
			temp = {
				{ ren,"Images/box.png",350,470,150,150,false,false,GetID() },
				{ ren,"Images/box.png",550,470,150,150,false,false,GetID() },
				{ ren,"Images/wall.png",800,294,213,350,false,true,GetID() },
				{ ren,"Images/flag.png",1279 - 200,350,200,176,true,true,GetID() },
				{ ren,"Images/cactus.png",100,244,220,420,true,true,GetID() },
				{ ren,"Images/cactus.png",500,244,220,420,true,true,GetID() }
			};

			props.swap(temp);

			for (int i = 0; i < props.size(); i++) {
				props.at(i).InitializeProps();
			}

			player->SpawnPlayer(100, 100);
		}
		else if (level == 2) {
			//Background
			background.InitializeBackground(ren, "Images/background2.png", 0, -120, 1279, 720);

			//Enemies
			tempEnemies = { {} };

			tempEnemies.at(0) = new Ghost();

			enemies.swap(tempEnemies);

			for (int i = 0; i < enemies.size(); i++) {
				enemies.at(i)->Initialize(ren, "StrongerGhost", i,60);
				enemies.at(i)->SetRect(30 * ((1) * 50), 530, 150, 150);
				enemies.at(i)->SetMoveSpeed(10);
				enemies.at(i)->SetAnimations();
			}

			temp = {
				{ ren,"Images/box.png",350,470,150,150,false,false,GetID() }
			};

			props.swap(temp);

			for (int i = 0; i < props.size(); i++) {
				props.at(i).InitializeProps();
			}

			player->SpawnPlayer(100, 100);
		}
		else if (level == 3) {
			//Background
			background.InitializeBackground(ren, "Images/level22.jpg", 0,-120, 3248, 720);

			//Enemies
			tempEnemies = { {}, {} ,{},{} };
		
			tempEnemies.at(0) = new Spider();
			tempEnemies.at(1) = new Spider();
			tempEnemies.at(2) = new Ghost();
			tempEnemies.at(3) = new Ghost();

			enemies.swap(tempEnemies);

			for (int i = 0; i < enemies.size(); i++) {
				if (i < 2) {
					enemies.at(i)->Initialize(ren, "SpiderMang", i,60);
					enemies.at(i)->SetRect(30 * ((i) * 100), 500, 150, 150);
				}
				else {
					enemies.at(i)->Initialize(ren, "GhostMang", i,30);
					enemies.at(i)->SetRect(30 * ((i - 2) * 150), 100, 150, 150);
				}
				enemies.at(i)->SetMoveSpeed(10);
				enemies.at(i)->SetAnimations();
			}

			//Props
			//props.clear();
			 temp = { 
			{ ren,"Images/box.png",350,470,150,150,false,false,GetID() },
			{ ren,"Images/box.png",550,470,150,150,false,false,GetID() },
			{ ren,"Images/wall.png",800,294,213,350,false,true,GetID() },
			{ ren,"Images/flag.png",1279 - 200,350,200,176,true,false,GetID() },
			{ ren,"Images/boulder.png",1800,144,220,229,false,true,GetID() },
			{ ren,"Images/fire.png",800,144,100,100,true,true,GetID() }
			 };

			props.swap(temp);
			
			for (int i = 0; i < props.size(); i++) {
				props.at(i).InitializeProps();
			}		

			//Player
			player->SpawnPlayer(100, 100);
		}
		else if (level == 4) {
			//Background
			background.InitializeBackground(ren, "Images/background4.png", 0, -120, 3600, 720);

			//Enemies
			tempEnemies = { {},{} ,{},{},{},{},{}};

			tempEnemies.at(0) = new Spider();
			tempEnemies.at(1) = new Spider();
			tempEnemies.at(2) = new Spider();
			tempEnemies.at(3) = new Spider();
			tempEnemies.at(4) = new Ghost();
			tempEnemies.at(5) = new Ghost();
			tempEnemies.at(6) = new Ghost();

			enemies.swap(tempEnemies);

			for (int i = 0; i < enemies.size(); i++) {
				if (i < 4) {
					enemies.at(i)->Initialize(ren, "SpiderMang", i, 60);
					enemies.at(i)->SetRect(30 * ((i) * 100), 500, 150, 150);
				}
				else {
					enemies.at(i)->Initialize(ren, "GhostMang", i, 30);
					enemies.at(i)->SetRect(30 * ((i - 4) * 150), 100, 150, 150);
				}
				enemies.at(i)->SetMoveSpeed(10);
				enemies.at(i)->SetAnimations();
			}

			//Props
			//props.clear();
			temp = {
				{ ren,"Images/box.png",350,470,150,150,false,false,GetID() },
				{ ren,"Images/box.png",2400,470,150,150,false,false,GetID() },
				{ ren,"Images/box.png",850,470,150,150,false,false,GetID() },
				{ ren,"Images/box.png",1500,470,150,150,false,false,GetID() },
				{ ren,"Images/box.png",1250,470,150,150,false,false,GetID() },
				{ ren,"Images/wall.png",2000,294,213,350,false,true,GetID() },
				{ ren,"Images/wall.png",3000,294,213,350,false,true,GetID() },
				{ ren,"Images/fire.png",1900,194,50,100,true,false,GetID() },
				{ ren,"Images/fire.png",500,294,10,20,true,false,GetID() },
			};

			props.swap(temp);

			for (int i = 0; i < props.size(); i++) {
				props.at(i).InitializeProps();
			}

			//Player
			player->SpawnPlayer(100, 100);
		}
		levelLoaded = true;
	}
}

void LevelManager::RenderBackground() {
	//for (int i = 0; i < props.size(); i++) {
		//props.at(i).Render(background,;
		//SDL_Rect background, SDL_Rect playerRect, vector<SDL_Rect> otherPropsRect,vector<bool> _isTrigger, int propAmount) {
	//}
}

void LevelManager::RenderForeground() {

}

int LevelManager::GetLevel() {
	return level;
}

void LevelManager::TransverseLevel(int nextLevel,Player* player) {
	currentLevel = nextLevel;
	levelLoaded = false;

	props.clear();
	temp.clear();

	enemies.clear();
	tempEnemies.clear();

	background.~Background();

	SetLevel(nextLevel,player);

	cout << "level set to " << nextLevel;
}

int LevelManager::GetID() {
	ID += 1;
	return ID;
}
