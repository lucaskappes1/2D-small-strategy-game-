#pragma once
#include "Building.h"
class Tower1 :
    public Building
{
public:
	Tower1(SDL_Renderer* renderer, int x, int y, class Game* game, bool isPlayer);
	void Draw();
	inline static const int getStaticGoldCost() { return mGoldCost; }
	static void LoadAnimation();
	void Attack(GameObject* target);
private:
	static SDL_Texture* mTexture;
	const static int mGoldCost = 500;
};
