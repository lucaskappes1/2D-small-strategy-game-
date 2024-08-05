#pragma once
#include "Building.h"
class Tower2 :
    public Building
{
public:
	Tower2(SDL_Renderer* renderer, int x, int y, class Game* game, bool isPlayer);
	void Draw();
	inline static const int getStaticGoldCost() { return mGoldCost; }
	void Attack(GameObject* target);
	static void LoadAnimation();
private:
	static SDL_Texture* mTexture;
	const static int mGoldCost = 850;
};
