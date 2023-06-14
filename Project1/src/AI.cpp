#include "AI.h"
#include "Game.h"
#include <vector>
#include <iostream>
#include "units/Rock.h"

AI::AI(Game* game) : mRng(mRd()), mVariation(1,100), mIsActive(false), mArmorUpgradeCount(3), mAttackUpgradeCount(3), mRockUpgradeLevel(1)
{
	mGame = game;
	eState = ATTACKING;
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
	int x = 0;;
	for (GameObject* i : temp)
	{
		if (i->getIsPlayer())
		{
			if (i->getX() > XPOSTHRESHOLD)
			{
				if (i->getX() > TOUGHXPOSTHRESHOLD)
				{
					eState = ENEMYATTHEGATES;
				}
				else
				{
					eState = UNDERATTACK;
				}
			}
			playerCount++;
			x += i->getX();
		}
		else
		{
			AICount++;
		}
	}
	mEnemyMiddle = x / playerCount;
	if (eState == UNDERATTACK || eState == ENEMYATTHEGATES)
	{
		Act();
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
	switch (eState)
	{
	case ATTACKING:
		if (temp < 70 && temp > 40)
		{
			mGame->CreateSpearKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
			mGame->CreateAxeKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
			mGame->CreateArcher(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
			mGame->CreateSpearKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
			mGame->CreateKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		}
		else if (temp > 20 && temp <= 40)
		{
			mGame->CreateKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
			mGame->CreateKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
			mGame->CreateKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
			mGame->CreateSpearKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
			mGame->CreateAxeKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		}
		else if (temp <= 20)
		{
			mGame->CreateHeavyInfantry(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
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
		if (temp < 10)
		{
			if (mEnemyMiddle <= 220)
			{
				mEnemyMiddle = 220;
			}
			Vector2 Dest((float)(mEnemyMiddle), 658.0f);
			mGame->ThrowRock(new Rock({ 974.0f, 600.0f }, Dest, mGame->getRenderer(), mGame, 0, mRockUpgradeLevel));
		}
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
		if (temp < 60 && temp > 30)
		{
			mGame->CreateKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
			mGame->CreateAxeKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
			mGame->CreateArcher(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		}
		else if (temp < 30)
		{
			mGame->CreateHeavyInfantry(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
			mGame->CreateArcher(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
			mGame->CreateArcher(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		}
		else 
		{
			mGame->CreateSpearKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
			mGame->CreateArcher(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
			mGame->CreateAxeKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		}
		break;
	case ENEMYATTHEGATES:
		if (temp < 20)
		{
			if (mEnemyMiddle <= 220)
			{
				mEnemyMiddle = 220;
			}
			Vector2 Dest((float)(mEnemyMiddle), 658.0f);
			mGame->ThrowRock(new Rock({ 974.0f, 600.0f }, Dest, mGame->getRenderer(), mGame, 0, mRockUpgradeLevel));
		}
		mGame->ClearAIQueue();
		mGame->CreateHeavyInfantry(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		mGame->CreateSpearKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		mGame->CreateSpearKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		mGame->CreateSpearKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		mGame->CreateSpearKnight(0, 1, mAttackUpgradeCount, mArmorUpgradeCount);
		break;
	}
}