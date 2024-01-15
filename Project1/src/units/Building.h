#pragma once
#include "GameObject.h"

class Building  : public GameObject
{
public:
	Building(SDL_Renderer* renderer, int x, int y, class Game* game, bool isPlayer);
	void Update(float deltaTime);
	virtual void TakeDamage(int DMG);
	void setProjectileNumber(int n) { mProjectileNumber = n; }
	int getAttackReloadTime() { return ATTACK_RELOAD_TIME; }
	void setAttackReloadTime(int n) { ATTACK_RELOAD_TIME = n; }
	virtual void OnDeathAction() {}
protected:
	int mRange;
	void RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor);
	float mPercentHPBar;
	float MAX_HP;
	int mProjectileNumber;
	int mProjectileCount = 0;
	int ATTACK_RELOAD_TIME;
};

