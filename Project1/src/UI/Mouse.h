#pragma once
#include "SDL.h"

class Mouse
{
public:
	Mouse(SDL_Texture* tex, SDL_Renderer* renderer);
	void Update();
	void Draw();
	const SDL_Rect& getCollisionRect() const { return mPoint; }
private:
	SDL_Texture* mTexture;
	SDL_Renderer* mRenderer;
	SDL_Rect mDestR;
	SDL_Rect mPoint;
};

