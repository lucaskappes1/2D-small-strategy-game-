#pragma once
#include "GameObject.h"
#include <random>

class MeleeUnit : public GameObject
{
public:
	MeleeUnit();
	virtual void Update(float deltaTime);
	virtual void Attack(GameObject* target);
	virtual void TakeDamage(int DMG);
	int getBlockChance() { return mBlockChance; }
	void setBlockChance(int n) { mBlockChance = n; }
protected:
	void StartGenerator();
	void RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor);
	enum State eLastFrameState;
	int ATTACK_RELOAD_TIME;
	int mBlockChance = 0;
	float mPercentHPBar;
	int MAX_HP;

	std::mt19937 mGenerator;
	std::uniform_int_distribution<int> mDistribution;
};

