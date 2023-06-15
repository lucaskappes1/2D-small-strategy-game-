#pragma once
#include "GameObject.h"

class MeleeUnit : public GameObject
{
public:
	MeleeUnit();
	virtual void Update(float deltaTime);
	virtual void Attack(GameObject* target);
	virtual void TakeDamage(int DMG);
protected:
	void RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor);
	enum State eLastFrameState;
	int ATTACK_RELOAD_TIME;
	float mPercentHPBar;
	int MAX_HP;
};

