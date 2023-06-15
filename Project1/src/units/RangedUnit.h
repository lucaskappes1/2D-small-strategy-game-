#pragma once
#include "GameObject.h"

class RangedUnit : public GameObject
{
public:
	RangedUnit();
	void Update(float deltaTime);
	virtual void TakeDamage(int DMG);
protected:
	float mPercentHPBar;
	int MAX_HP;
	int ATTACK_RELOAD_TIME;
	enum State eLastFrameState;
	void RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor);
};

