#pragma once
#include <random>
#include "Vector2.h"

class AI
{
public:
	AI(class Game* game);
	virtual void Act();
	inline const float& getGoldMultiplier() const { return mGoldMultiplier; }
	inline void Activate() { mIsActive = true; }
	inline void Deactivate() { mIsActive = false; }
	void UpgradeAttack() { mAttackUpgradeCount++; }
	void UpgradeArmor() { mArmorUpgradeCount++; }
	virtual void ChangeState();
	bool mIsActive;
protected:
	void CreateKnight();
	void CreateSpearKnight();
	void CreateAxeKnight();
	void CreateArcher();
	void CreateHeavyInfantry();
	void ApplyUpgrade(class GameObject* unit);
	int mAttackUpgradeCount;
	int mArmorUpgradeCount;
	int mRockUpgradeLevel;
	bool mIsAdvancing;
	float mGoldMultiplier = 1;
	int mEnemyMiddle;
	class Game* mGame;
	enum State {UNDERATTACK, ATTACKING, NUMBERDISADVANTAGE, NUMBERADVANTAGE, ENEMYATTHEGATES} eState;
	const int XPOSTHRESHOLD = 600;
	const int TOUGHXPOSTHRESHOLD = 800;
	std::random_device mRd;
	std::mt19937 mRng;
	std::uniform_int_distribution<int> mVariation;
};

class AIhard : public AI
{
public:
	AIhard(class Game* game) : AI(game) { mGoldMultiplier = 0.7f; }
	void Act();
protected:
};
