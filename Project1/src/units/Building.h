#pragma once
#include "GameObject.h"

class Building  : public GameObject
{
public:
	Building(SDL_Renderer* renderer, int x, int y, class Game* game, bool isPlayer);
	void Update(float deltaTime);
	virtual void TakeDamage(int DMG);
protected:
	void RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor);
	float mPercentHPBar;
	float MAX_HP;
};

