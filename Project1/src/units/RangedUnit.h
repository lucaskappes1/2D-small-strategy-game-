#pragma once
#include "GameObject.h"

class RangedUnit : public GameObject
{
public:
	RangedUnit();
	void Update(float deltaTime);
	virtual void TakeDamage(int DMG);
	void IncreaseRange(int range);
	int getAttackReloadTime() { return ATTACK_RELOAD_TIME; }
	void setProjectileNumber(int n) { mProjectileNumber = n; }
	void setAttackReloadTime(int n) { ATTACK_RELOAD_TIME = n; }
protected:
	GameObject* mTarget;
	float mPercentHPBar;
	int MAX_HP;
	int mRange;
	int ATTACK_RELOAD_TIME;
	int mProjectileNumber;
	int mProjectileCount = 0;
	enum State eLastFrameState;
	void RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor);
};

