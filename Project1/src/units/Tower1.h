#pragma once
#include "Building.h"
class Tower1 :
    public Building
{
public:
	Tower1(SDL_Renderer* renderer, int x, int y, class Game* game, bool isPlayer);
	void Draw();
	inline static const int getStaticGoldCost() { return mGoldCost; }
	void Attack(GameObject* target);
private:
	const static int mGoldCost = 500;
	void LoadAnimation();
};
