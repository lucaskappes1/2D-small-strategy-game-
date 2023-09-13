#pragma once
#include "Building.h"
class Tower2 :
    public Building
{
public:
	Tower2(SDL_Renderer* renderer, int x, int y, class Game* game, bool isPlayer);
	void Draw();
	void Attack(GameObject* target);
private:
	const int ATTACK_RELOAD_TIME = 110;
	const int mArmor = 5;
	void LoadAnimation();
};
