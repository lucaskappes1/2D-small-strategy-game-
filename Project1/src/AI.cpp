#include "AI.h"
#include "Game.h"
#include <vector>
#include <iostream>

AI::AI(Game* game) : mRng(mRd()), mVariation(1,100), mIsActive(false), mArmorUpgradeCount(0), mAttackUpgradeCount(0)
{
	mGame = game;
	eState = UNDERATTACK;
}

void AI::Act()
{
	if (!mIsActive)
	{
		return;
	}
	ChangeState();
	switch (eState)
	{
	case ATTACKING:
		mGame->CreateSpearKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		mGame->CreateKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		mGame->CreateArcher(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		break;
	case UNDERATTACK:
		mGame->CreateSpearKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		mGame->CreateArcher(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		mGame->CreateArcher(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		break;
	case NUMBERDISADVANTAGE:
		mGame->CreateSpearKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		mGame->CreateArcher(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		mGame->CreateKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		mGame->CreateArcher(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		mGame->CreateAxeKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		mGame->CreateArcher(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		break;
	case NUMBERADVANTAGE:
		mGame->CreateArcher(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		mGame->CreateArcher(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		break;
	case ENEMYATTHEGATES:
		mGame->ClearAIQueue();
		mGame->CreateSpearKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		mGame->CreateSpearKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		mGame->CreateSpearKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		break;
	}
}

void AI::ChangeState()
{
	const std::vector<GameObject*>& temp = mGame->GetGameObjectVector();
	int playerCount= 0;
	int AICount = 0;
	for (GameObject* i : temp)
	{
		if (i->getIsPlayer())
		{
			if (i->getX() > XPOSTHRESHOLD)
			{
				int temp = mVariation(mRng);
				if(temp < 30)
					mGame->SplashDamage(200, XPOSTHRESHOLD - 80, 200);
				if (i->getX() > TOUGHXPOSTHRESHOLD)
				{
					eState = ENEMYATTHEGATES;
					return;
				}
				eState = UNDERATTACK;
				return;
			}
			playerCount++;
		}
		else
		{
			AICount++;
		}
	}
	if (playerCount > AICount + 4)
	{
		eState = NUMBERDISADVANTAGE;
		return;
	}
	else if (AICount > playerCount + 4)
	{
		eState = NUMBERADVANTAGE;
		return;
	}
	eState = ATTACKING;

	return;
}

void AIhard::Act()
{
	if (!mIsActive)
	{
		return;
	}
	int temp = mVariation(mRng);
	ChangeState();
	switch (eState)
	{
	case ATTACKING:
		if (temp < 50 && temp > 20)
		{
			mGame->CreateSpearKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
			mGame->CreateAxeKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
			mGame->CreateArcher(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
			mGame->CreateSpearKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
			mGame->CreateKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		}
		else if (temp <= 20)
		{
			mGame->CreateSpearKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
			mGame->CreateAxeKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
			mGame->CreateArcher(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
			mGame->CreateArcher(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
			mGame->CreateArcher(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
			mGame->CreateArcher(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
			mGame->CreateKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		}
		else
		{
			mGame->CreateSpearKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
			mGame->CreateKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
			mGame->CreateArcher(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
			mGame->CreateArcher(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
			mGame->CreateArcher(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
			mGame->CreateAxeKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		}
		break;
	case UNDERATTACK:
		mGame->CreateSpearKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		mGame->CreateSpearKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		mGame->CreateArcher(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		mGame->CreateArcher(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		break;
	case NUMBERDISADVANTAGE:
		mGame->CreateSpearKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		mGame->CreateArcher(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		mGame->CreateKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		mGame->CreateArcher(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		mGame->CreateAxeKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		mGame->CreateArcher(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		mGame->CreateArcher(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		break;
	case NUMBERADVANTAGE:
		if (temp < 40)
		{
			mGame->CreateKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
			mGame->CreateArcher(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		}
		else 
		{
			mGame->CreateSpearKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
			mGame->CreateArcher(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		}
		break;
	case ENEMYATTHEGATES:
		mGame->ClearAIQueue();
		mGame->CreateSpearKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		mGame->CreateSpearKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		mGame->CreateSpearKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		mGame->CreateSpearKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		mGame->CreateSpearKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		break;
	}
}