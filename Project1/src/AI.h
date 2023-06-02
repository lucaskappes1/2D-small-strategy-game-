#pragma once

#include <random>

class AI
{
public:
	AI(class Game* game);
	virtual void Act();
	const float& getGoldMultiplier() const { return mGoldMultiplier; }
protected:
	float mGoldMultiplier = 1;
	virtual void ChangeState();
	class Game* mGame;
	enum State {UNDERATTACK, ATTACKING, NUMBERDISADVANTAGE, NUMBERADVANTAGE, ENEMYATTHEGATES} eState;
	const int XPOSTHRESHOLD = 500;
	const int TOUGHXPOSTHRESHOLD = 650;
	std::random_device mRd;
	std::mt19937 mRng;
	std::uniform_int_distribution<int> mVariation;
};

class AIhard : public AI
{
public:
	AIhard(class Game* game) : AI(game) { mGoldMultiplier = 0.75f; }
	void Act();
protected:
};
