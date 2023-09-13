#pragma once
#include "Building.h"

class Castle :  public Building
{
public:
	Castle(SDL_Renderer* renderer, int x, int y, class Game* game, bool isPlayer);
	void Draw();
	void Attack(GameObject* target);
private:
	const int ATTACK_RELOAD_TIME = 50;
	void LoadAnimation();
};