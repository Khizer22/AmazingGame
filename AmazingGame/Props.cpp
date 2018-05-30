#include "stdafx.h"
#include "Props.h"

Props::Props(SDL_Renderer *rend,char *spriteFileName,int x,int y,int w,int h,bool _isTrigger,bool _isStatic,int _ID) {
	ren = rend;
	startingX = x;
	startingY = y;
	sizeWidth = w;
	sizeHeight = h;

	posX = startingX;
	posY = startingY;
	isTrigger = _isTrigger;
	isStatic = _isStatic;
	ID = _ID;

	texFileName = spriteFileName;
}
Props::Props() {
	//propsTex = NULL;
}

Props::~Props() {
	if (propsTex != NULL) {
		SDL_DestroyTexture(propsTex);
		cout << endl << "Prop: " << texFileName << " destroyed";
	}
}

void Props::InitializeProps() {
	propsRect = { startingX,startingY,sizeWidth,sizeHeight };
	propsTex = IMG_LoadTexture(ren,texFileName);
}

void Props::Render(SDL_Rect background, SDL_Rect playerRect, vector<SDL_Rect> otherPropsRect,vector<bool> _isTrigger, int propAmount,int bLength) {
	//if !isAnimated
	//box collision
	if (propsRect.x > 0 - propsRect.w && propsRect.x < SCREENWIDTH) {  //if within screen
		if (!isTrigger && !isStatic) {
			//Colliding with player
			if (playerRect.x + playerRect.w - 35 > propsRect.x
				&& playerRect.x + 35 < propsRect.x + propsRect.w
				&& playerRect.y + playerRect.h - 15 > propsRect.y
				&& playerRect.y + 15 < propsRect.y + propsRect.h
				)
			{
				if (playerRect.y + playerRect.h < propsRect.y + propsRect.h / 2)
					posX = posX;
				else if (playerRect.x + playerRect.w - 35 < propsRect.x + propsRect.w / 2)
					posX += 1;
				//posX = posX;
				else if (playerRect.x + 35 > propsRect.x + propsRect.w / 2)
					posX -= 1;
				//posX = posX;
			}
			//Colliding with other STATIC props
			for (int i = 0; i < propAmount; i++) {
				if (!_isTrigger.at(i) && i != ID) {
					if (propsRect.x + propsRect.w > otherPropsRect.at(i).x
						&& propsRect.x < otherPropsRect.at(i).x + otherPropsRect.at(i).w
						&& propsRect.y + propsRect.h  > otherPropsRect.at(i).y
						&& propsRect.y < otherPropsRect.at(i).y + otherPropsRect.at(i).h
						)
					{
						/*  if collding from above
						if (propsRect.y + propsRect.h  < otherPropsRect[i].y + otherPropsRect[i].h / 2)
						{
							//dont really need right now
						}  */
						if (propsRect.x + propsRect.w < otherPropsRect.at(i).x + otherPropsRect.at(i).w / 2) {
							posX -= 1;
						}
						else if (propsRect.x > otherPropsRect.at(i).x + otherPropsRect.at(i).w / 2) {
							posX += 1;
						}
					}
				}
			}

			//Colliding with Borders
			if (propsRect.x + sizeWidth > background.x + bLength) {
				posX -= 1;
			}
			else if (propsRect.x < background.x)
				posX += 1;

		}
	}

	propsRect.x = background.x + posX;
	propsRect.y = background.y + posY; //+ 120

	if (propsRect.x > 0 - propsRect.w && propsRect.x < SCREENWIDTH) { //if within screen
		SDL_RenderCopy(ren, propsTex, NULL, &propsRect);
	}
} 
