#include "stdafx.h"
#include "AmazingGame.h"

AmazingGame::AmazingGame() {
	cout << "Controls\n----------------------------------------------" << endl;
	cout << "Arrow Keys - Move\nC - Sprint\nSpaceBar - Jump";
	gameRunning = true;
}

AmazingGame::~AmazingGame() {
	try {
		SDL_DestroyRenderer(ren);
	}
	catch (exception e) {
		cout << endl << "naan";
	}
	SDL_DestroyWindow(win);
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}

void AmazingGame::StartGame() {
	InitializeGame();

	//Set Viewport
	SDL_Rect Viewport = { 0,0, SCREENWIDTH, SCREENHEIGHT };

	//Create Main Character
	Player *player = new Player("CoolDude", ren);
	//cout << endl << "Welcome " << player->name << "\n";

	//Create Background
	LevelManager* levelManager = new LevelManager(ren);

	//Menu
	Menu menu(ren,levelManager);
	menu.InitializeMenu();

	//Gameplay here
	while (gameRunning) {
		//This also initializes background ,props 
		if (levelManager->levelLoaded == false)
			levelManager->SetLevel(levelManager->currentLevel, player);

		SDL_RenderClear(ren);
		levelManager->background.Render(player,Viewport);
		SDL_RenderSetViewport(ren, &Viewport);	

		//if levelloaded = false{
		int propsAmount = levelManager->props.size();
		int enemyAmount = levelManager->enemies.size();
		vector<SDL_Rect> tempEnemyRect(enemyAmount);
		vector<SDL_Rect> tempRect(propsAmount);
		vector<bool> isTrigger(propsAmount);
		vector<bool> isStatic(propsAmount);
		int bLength = levelManager->background.GetLength();
		int bHeight = levelManager->background.GetHeight();
		SDL_Rect projectileRect = player->GetProjectileRect();

		for (int i = 0; i < enemyAmount; i++) {
			tempEnemyRect.at(i) = levelManager->enemies.at(i)->enemyRect;
		}
		
		for (int i = 0; i < propsAmount;i++) { //dont need this every frame *****
			tempRect.at(i) = levelManager->props.at(i).propsRect;
			isTrigger.at(i) = levelManager->props.at(i).isTrigger;
			isStatic.at(i) = levelManager->props.at(i).isStatic;
		}

		//If not in MainMenu
		if (levelManager->GetLevel() != 0) { 			
			//PLAYER STUFF
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						menu.paused = true;
						break;
					default:
						break;
					}
				}
				if (menu.paused)
					menu.PauseMenu(event, gameRunning);
				else
					player->HandleEvent(event);    //Player Input
			}
			if (!menu.paused && player->isDead == false) {
				//Player
				player->Move(levelManager->background.backgroundRect);
				player->CollisionDetection(tempEnemyRect, enemyAmount, tempRect, isTrigger, isStatic, propsAmount, bLength, bHeight);
				//player->Render();
			}
			else if (!menu.paused && player->isDead == true)
				menu.PlayerDead();
			player->Render(); // lel
		}
		else {			
			//MainMenu
			menu.ActivateMenu(1);
			while (SDL_PollEvent(&event))
				menu.HandleEvents(event,player,gameRunning);
		}

		//Render Stage Props
		for (int i = 0; i < propsAmount; i++) {
			levelManager->props.at(i).Render(levelManager->background.backgroundRect, player->playerRect, tempRect, isTrigger, propsAmount,bLength);
		}

		//Render Enemies
		for (int i = 0; i <enemyAmount; i++) {
			if (!menu.paused && levelManager->enemies.at(i)->isDead == false)
				levelManager->enemies.at(i)->CollisionDetection(tempRect,isStatic,player->playerRect,projectileRect,tempEnemyRect, levelManager->background.backgroundRect,bLength,enemyAmount);
			levelManager->enemies.at(i)->Render(levelManager->background.backgroundRect);
		}

		//Update LevelGoals
		if (levelManager->currentLevel != 0) {			
			int q = 0;
			for (int i = 0; i < levelManager->enemies.size(); i++) {
				if (levelManager->enemies.at(i)->isDead) {
					q++;
				}
			}
			if (q == levelManager->enemies.size()) {
				if (levelManager->currentLevel < levelManager->maxLevel) {
					int nextLevel = levelManager->currentLevel + 1;
					levelManager->TransverseLevel(nextLevel, player);
				}
				else if (!menu.paused)
				{
					menu.Win();
				}
			}			
		}
		//Render Pause Menu
		if (menu.paused) {
			menu.ActivateMenu(2);
		}
		//Render Everything
		if (gameRunning)
			SDL_RenderPresent(ren);
	}
	//Destroying local stuff
	//if SDL_QUIT
	delete player;
	delete levelManager;
}

void AmazingGame::InitializeGame() {
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	IMG_Init(IMG_INIT_PNG);	
	SDL_Init(SDL_INIT_AUDIO);
	SDL_CreateWindowAndRenderer(SCREENWIDTH, SCREENHEIGHT, NULL, &win, &ren);
	SDL_Surface *screen = SDL_GetWindowSurface(win);	
}