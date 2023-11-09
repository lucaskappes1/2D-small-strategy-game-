#include "AI.h"
#include "Game.h"
#include <vector>
#include <iostream>
#include "units/Rock.h"

AI::AI(Game* game) : mRng(mRd()),
	mVariation(1,100),
	mIsActive(false), 
	mArmorUpgradeCount(3), 
	mAttackUpgradeCount(3), 
	mRockUpgradeLevel(1),
	mIsAdvancing(1)
{
	mGame = game;
	eState = ATTACKING;
}

void AI::CreateKnight()
{
	Knight* temp = new Knight(mGame->getRenderer(), mGame->getAICreateUnitPosition(), HEIGHT - 110, mGame, 0, mIsAdvancing);
	ApplyUpgrade(temp);
	mGame->CreateUnit(temp);
}

void AI::CreateSpearKnight()
{
	SpearKnight* temp = new SpearKnight(mGame->getRenderer(), mGame->getAICreateUnitPosition(), HEIGHT - 110, mGame, 0, mIsAdvancing);
	ApplyUpgrade(temp);
	mGame->CreateUnit(temp);
}

void AI::CreateAxeKnight()
{
	AxeKnight* temp = new AxeKnight(mGame->getRenderer(), mGame->getAICreateUnitPosition(), HEIGHT - 110, mGame, 0, mIsAdvancing);
	ApplyUpgrade(temp);
	mGame->CreateUnit(temp);
}

void AI::CreateArcher()
{
	Archer* temp = new Archer(mGame->getRenderer(), mGame->getAICreateUnitPosition(), HEIGHT - 110, mGame, 0, mIsAdvancing);
	ApplyUpgrade(temp);
	mGame->CreateUnit(temp);
}

void AI::CreateHeavyInfantry()
{
	HeavyInfantry* temp = new HeavyInfantry(mGame->getRenderer(), mGame->getAICreateUnitPosition(), HEIGHT - 110, mGame, 0, mIsAdvancing);
	ApplyUpgrade(temp);
	mGame->CreateUnit(temp);
}

void AI::CreateTower1()
{
	if (mGame->getAIBuildingCount() < 3)
	{
		Tower1* temp = new Tower1(mGame->getRenderer(), mGame->getAICreateUnitPosition(), HEIGHT - 175, mGame, 0);
		mGame->CreateUnit(temp);
		mGame->IncreaseAIBuildingCount();
	}
}

void AI::CreateTower2()
{
	if (mGame->getAIBuildingCount() < 3)
	{
		Tower2* temp = new Tower2(mGame->getRenderer(), mGame->getAICreateUnitPosition(), HEIGHT - 175, mGame, 0);
		mGame->CreateUnit(temp);
		mGame->IncreaseAIBuildingCount();
	}
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
		CreateSpearKnight();
		CreateKnight();
		CreateArcher();
		break;
	case UNDERATTACK:
		CreateSpearKnight();
		CreateArcher();
		CreateArcher();
		break;
	case NUMBERDISADVANTAGE:
		CreateSpearKnight();
		CreateArcher();
		CreateKnight();
		CreateArcher();
		CreateAxeKnight();
		CreateArcher();
		break;
	case NUMBERADVANTAGE:
		CreateArcher();
		CreateArcher();
		break;
	case ENEMYATTHEGATES:
		mGame->ClearAIQueue();
		CreateSpearKnight();
		CreateSpearKnight();
		CreateSpearKnight();
		break;
	}
}

void AI::ChangeState()
{
	const std::vector<GameObject*>& temp = mGame->GetGameObjectVector();
	int playerCount= 0;
	int AICount = 0;
	int x = 0;
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
	if (playerCount != 0)
	{
		mEnemyMiddle = x / playerCount;
	}
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

void AI::ApplyUpgrade(GameObject* unit)
{
	unit->setAttack(unit->getAttack() + mAttackUpgradeCount);
	unit->setArmor(unit->getArmor() + mArmorUpgradeCount);
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
			CreateSpearKnight();
			CreateAxeKnight();
			CreateArcher();
			CreateSpearKnight();
			CreateKnight();
		}
		else if (temp > 20 && temp <= 40)
		{
			CreateKnight();
			CreateKnight();
			CreateKnight();
			CreateSpearKnight();
			CreateAxeKnight();
		}
		else if (temp <= 20)
		{
			CreateHeavyInfantry();
			CreateArcher();
			CreateArcher();
			CreateArcher();
			CreateArcher();
			CreateKnight();
		}
		else
		{
			CreateSpearKnight();
			CreateKnight();
			CreateArcher();
			CreateArcher();
			CreateArcher();
			CreateAxeKnight();
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
			mGame->AddProjectile(new Rock({ 974.0f, 600.0f }, Dest, mGame->getRenderer(), mGame, mRockUpgradeLevel));
		}
		CreateSpearKnight();
		CreateSpearKnight();
		CreateArcher();
		CreateArcher();
		break;
	case NUMBERDISADVANTAGE:
		CreateSpearKnight();
		CreateArcher();
		CreateKnight();
		CreateArcher();
		CreateAxeKnight();
		CreateArcher();
		CreateArcher();
		break;
	case NUMBERADVANTAGE:
		if (temp < 60 && temp > 30)
		{
			CreateKnight();
			CreateAxeKnight();
			CreateArcher();
		}
		else if (temp < 30)
		{
			CreateHeavyInfantry();
			CreateArcher();
			CreateArcher();
		}
		else 
		{
			CreateSpearKnight();
			CreateArcher();
			CreateAxeKnight();
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
			mGame->AddProjectile(new Rock({ 974.0f, 600.0f }, Dest, mGame->getRenderer(), mGame, mRockUpgradeLevel));
		}
		mGame->ClearAIQueue();
		CreateHeavyInfantry();
		CreateSpearKnight();
		CreateSpearKnight();
		CreateSpearKnight();
		CreateSpearKnight();
		break;
	}
}