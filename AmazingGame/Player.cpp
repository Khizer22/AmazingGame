#include "stdafx.h"
#include "Player.h"

Player::Player(string nameOfPlayer, SDL_Renderer *playerRen) {

	name = nameOfPlayer;
	ren = playerRen;

	startingX = 200;
	startingY = 350;
	sizeWidth = 115;
	sizeHeight = 158;
	frameRate = 900;
	currentFrameRate = frameRate;
	
	initializeAnimations();
	startFrame = 1;
	endFrame = 1;
	currentFrame = 0;
	blinkTime = 0;
	flip = SDL_FLIP_NONE;
	moveRight = false;
	moveLeft = false;
	running = false;
	jumping = false;
	grounded = false;
	currentKeyStates = SDL_GetKeyboardState(NULL);

	maxHealth = 100;
	currentHealth = maxHealth;
	jumpSpeed = 0.7f;
	moveSpeed = 0.15f;
	currentMoveSpeed = moveSpeed;
	maxSpeed = 0.25f;
	posX = startingX;
	posY = startingY;
	gravity = 0;
	gravityInc = 0.001f;
	onObject = false;
	blah = false;
	isDead = false;
	invulnerable = false;
	invulTime = 0;
	takingDamage = false;
	damageDirection = 0;

	//Projectile
	projectile = new Projectile();
	projectile->Initialize(ren);
	firing = false;
	fireTime = 0;

	//Sounds
	Sounds sounds();

	playerRect = { startingX,startingY,sizeWidth,sizeHeight };
	
	//CHANGE TO STATIC LATER
	//Physics physics;
}

Player::~Player() {
	SDL_DestroyTexture(playerTexture);
	cout << endl << "player deleted";
	projectile->~Projectile();
}

//BUILD ANIMATIONS
void Player::initializeAnimations() {
	playerTexture = IMG_LoadTexture(ren, "Images/boySpriteSheet2.png");
	int spriteWidth = 115;
	int spriteHeight = 158;

	int q = 0;
	int y = 0;
	//Idle Animation 1-2, Walk Animation 3-6, Run Animation 7-12, Jump Animation 13-18
	for (int x = 0; x < 768; x = x + spriteWidth)
	{
		if (q == 6) {
			x = 0;
			y = 158;
		}
		if (q == 12) {
			x = 0;
			y = 316;
		}
		currentAnimation[q].x = x;
		currentAnimation[q].y = y;
		currentAnimation[q].w = spriteWidth;
		currentAnimation[q].h = spriteHeight;
		q++;
	}
}

//COLLISION

void Player::CollisionDetection(vector<SDL_Rect> enemyRect,int enemyAmount,vector<SDL_Rect> propsRect,vector<bool> _isTrigger,vector<bool> _isStatic,int propsAmount,int _bLength,int _bHeight) {
	onObject = false;
	bLength = _bLength;
	bHeight = _bHeight;

	//Constraints player in level
	if (posX + sizeWidth > bLength) {
		posX -= currentMoveSpeed;
	}
	else if (posX < 0)
		posX += currentMoveSpeed;

	//Collision with Props
	for (int i = 0; i < propsAmount; i++) {
		if (!_isTrigger.at(i)){
			if (playerRect.x + playerRect.w - 15 > propsRect.at(i).x
				&& playerRect.x + 15 < propsRect.at(i).x + propsRect.at(i).w
				&& playerRect.y + playerRect.h - 5 > propsRect.at(i).y
				&& playerRect.y < propsRect.at(i).y + propsRect.at(i).h
				)
			{
				if (playerRect.y + playerRect.h - 5 < propsRect.at(i).y + propsRect.at(i).h / 2)
				{
						//If player is falling downwards then stay on top of object
					if (gravity > jumpSpeed || blah == true) { 
						posY = propsRect.at(i).y - playerRect.h + 6 ;
						blah = true;
						onObject = true;
						jumping = false;
						grounded = true;
						if (startFrame == 15 && endFrame == 16 || startFrame == 16)
						PlayAnimation(1, 1);
					}
					else if (playerRect.x + playerRect.w - 15 < propsRect.at(i).x + propsRect.at(i).w / 2 + 1) {
							posX -= currentMoveSpeed;
					}
					else if (playerRect.x + 15 > propsRect.at(i).x + propsRect.at(i).w / 2 - 1) {
							posX += currentMoveSpeed;
					}
				}
				else if (playerRect.x + playerRect.w - 15 < propsRect.at(i).x + propsRect.at(i).w / 2 + 1) {
					if (_isStatic.at(i))
						posX -= currentMoveSpeed;  //movespeed/2 maybe
				}
				else if (playerRect.x + 15 > propsRect.at(i).x + propsRect.at(i).w / 2 - 1) {
					if (_isStatic.at(i))
						posX += currentMoveSpeed;
				}
				else if (playerRect.y > propsRect.at(i).y + propsRect.at(i).h / 2 && _isStatic.at(i))
				{
					jumping = false;
				}
			}
		}
	}

	//Collision with Enemies
	for (int i = 0; i < enemyAmount; i++) {
		if (playerRect.x + playerRect.w - 35 > enemyRect.at(i).x
			&& playerRect.x + 35 < enemyRect.at(i).x + enemyRect.at(i).w
			&& playerRect.y + playerRect.h - 15 > enemyRect.at(i).y
			&& playerRect.y + 15 < enemyRect.at(i).y + enemyRect.at(i).h
			)
		{/*
			if (playerRect.y + playerRect.h < enemyRect.at(i).y + enemyRect.at(i).h / 2)
				posX -= currentMoveSpeed; */
			if (playerRect.x + playerRect.w  < enemyRect.at(i).x + enemyRect.at(i).w / 2) {
				if (invulnerable == false)
					damageDirection = TakeDamage(-1);
			}
			else if (playerRect.x  > enemyRect.at(i).x + enemyRect.at(i).w / 2) {
				if (invulnerable == false)
					damageDirection = TakeDamage(1);
			}
		}
	}

	if (invulnerable) {
		if (takingDamage) {
			posX += damageDirection * (0.15f + currentMoveSpeed);
			posY -= 0.3f;
		}
		SDL_SetTextureAlphaMod(playerTexture, 150);
		invulTime += 0.01f;
		if (invulTime >= 30) {
			invulnerable = false;
			invulTime = 0;
		}
		else if (invulTime >= 3)
			takingDamage = false;
	}
	else {
		SDL_SetTextureAlphaMod(playerTexture, 255);
	}

	if (currentHealth <= 0)
		Dead();
	
}

//HANDLE MOVEMENT
void Player::Move(SDL_Rect Background) {
	backgroundRect = Background;

	//Movement left and right
	if (moveRight == true && moveLeft == false) {
		posX += currentMoveSpeed;
		PlayAnimation(3, 6);
		flip = SDL_FLIP_NONE;
		moveLeft = false;
		//if (grounded)
			//sounds.Play("footSteps");
	}
	if (moveLeft == true && moveRight == false)
	{
		posX -= currentMoveSpeed;
		PlayAnimation(3, 6);
		flip = SDL_FLIP_HORIZONTAL;
		moveRight = false;
		//if (grounded)
			//sounds.Play("footSteps");
	}
	//Running
	if (running)
	{
		if (currentMoveSpeed < maxSpeed)
			currentMoveSpeed += 0.01f;
		if (startFrame != 1 && startFrame != 15 &&startFrame != 16 ) //need to rework this
			PlayAnimation(7, 12);
	}
	else if (!running) {
		currentMoveSpeed = moveSpeed;
	}
	//Grounded
	if (grounded) {
		gravity = 0;
	}

	//Jumping
	if (jumping) {
		posY -= jumpSpeed;
		PlayAnimation(15, 16);
	}

	//Moving player when camera doesnt move
	if (Background.x >= 0)
		playerRect.x = posX;
	else if (Background.x <= -(bLength)+SCREENWIDTH)
		playerRect.x = posX + -(bLength)+SCREENWIDTH;

	//maybe change posY,posX to int
	if (posY >= 350) {
		jumping = false;
		posY = 350;
		grounded = true;
		if (startFrame == 15 || startFrame == 16)
			PlayAnimation(1, 1);
	}
	else if (posY < 350) {
		if (!onObject) {
			blah = false;
			grounded = false;
			gravity += gravityInc;
			posY += gravity;
			if (startFrame != 15)
				PlayAnimation(16, 16);
		}
	}
	playerRect.y = posY;
}

//HANDDLE INPUTS
void Player::HandleEvent(SDL_Event &event) {
	/*
	switch (event.type) {
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_RIGHT:
			moveRight = true;
			moveLeft = false;
			break;
		case SDLK_LEFT:
			moveLeft = true;
			moveRight = false;
			break;
		default:
			break;
		}
		break;
	case SDL_KEYUP:
		switch (event.key.keysym.sym) {
		case SDLK_RIGHT:
			moveRight = false;
			moveLeft = false;
			PlayAnimation(1, 1);
			cout << "neither ||||";
			break;
		case SDLK_LEFT:
			moveRight = false;
			moveLeft = false;
			PlayAnimation(1, 1);
			cout << "neither ||||";
			break;
		default:
			break;
		}
	}	
	*/

	if (currentKeyStates[SDL_SCANCODE_X]) {
		if (!firing && !isDead) {
			firing = true;
		}
	}

	if (currentKeyStates[SDL_SCANCODE_SPACE]) {
		if (!jumping && grounded) {
			jumping = true;
			sounds.Play("jump");
		}
	}
	else if (currentKeyStates[SDL_SCANCODE_C]) {
		if (!jumping)
			running = true; 
	}
	else {
			running = false;
	}

	//alternate method, does the same thing
	if (currentKeyStates[SDL_SCANCODE_LEFT])
	{
		moveLeft = true;
		moveRight = false;
	}
	else if (currentKeyStates[SDL_SCANCODE_RIGHT])
	{
		moveRight = true;
		moveLeft = false;
	}
	else
	{
		moveRight = false;
		moveLeft = false;
		PlayAnimation(1, 1);
	}	
}

//RENDER
void Player::Render(){

	//Slow down blink animation
	if (startFrame < 3 && endFrame < 3) {
		blinkTime += 1;
		if (blinkTime > 15000 && blinkTime < 15500) {
			startFrame = 2;
			endFrame = 2;
		}
		else if (blinkTime > 15500) {
			blinkTime = 0;
			startFrame = 1;
			endFrame = 1;
		}
	}
	else if (startFrame == 7 && endFrame == 12) {
		currentFrameRate = frameRate/2;
	}
	else if (startFrame == 15 && endFrame == 16) {
		currentFrameRate = frameRate;
		if (currentFrame / currentFrameRate > 14.9)
			startFrame = 16;
	}
	else currentFrameRate = frameRate;

	//Animation control and Render
	animClip = &currentAnimation[currentFrame / currentFrameRate];


	SDL_RenderCopyEx(ren, playerTexture, animClip, &playerRect, 0, NULL, flip);

	currentFrame++;
	if ((currentFrame / currentFrameRate) < (startFrame - 1) || (currentFrame / currentFrameRate) > (endFrame - 0.1))
		currentFrame = (startFrame - 1) * currentFrameRate;
	
	//PROJECTILE
	if (firing) {
		if (fireTime <= 0) { //Initialize projectile fire
			int dir = 0;
			if (flip)
				dir = -1;
			else dir = 1;
			projectile->Fire(dir, posX, posY);
			sounds.Play("fire");
		}		

		fireTime += 0.01f;
		projectile->Render(backgroundRect);

		if (fireTime > 5) {
			projectile->StopFiring();
			fireTime = 0;
			firing = false;
		}
	}
	
}

//in game
void Player::PlayAnimation(int bFrame, int eFrame) {
	startFrame = bFrame;
	endFrame = eFrame;
}

void Player::SpawnPlayer(int x, int y) {
	posX = x;
	posY = y;
}

float Player::GetPosX() {
	return posX;
}
float Player::GetPosY() {
	return posY;
}

int Player::TakeDamage(int direction) {
	takingDamage = true;
	currentHealth -= 20;
	invulnerable = true;
	sounds.Play("hurt");
	cout << "player hit for 10 damage dawg";

	return direction;
}

void Player::Dead() {
	sounds.Play("gameOver");
	SDL_SetTextureColorMod(playerTexture, 250, 0, 0);
	flip = SDL_FLIP_VERTICAL;
	isDead = true;
}

SDL_Rect Player::GetProjectileRect() {
	return projectile->fireRect;
}







