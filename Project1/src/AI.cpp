#include "AI.h"
#include "Game.h"
#include <vector>
#include <iostream>

AI::AI(Game* game) : mRng(mRd()), mVariation(1,100)
{
	mGame = game;
	eState = UNDERATTACK;
}

void AI::Act()
{
	//int temp = mVariation(mRng);
	ChangeState();
	switch (eState)
	{
	case ATTACKING:
		mGame->CreateSpearKnight(0);
		mGame->CreateKnight(0);
		mGame->CreateArcher(0);
		break;
	case UNDERATTACK:
		mGame->CreateSpearKnight(0);
		mGame->CreateArcher(0);
		mGame->CreateArcher(0);
		break;
	case NUMBERDISADVANTAGE:
		mGame->CreateSpearKnight(0);
		mGame->CreateArcher(0);
		mGame->CreateKnight(0);
		mGame->CreateArcher(0);
		mGame->CreateAxeKnight(0);
		mGame->CreateArcher(0);
		break;
	case NUMBERADVANTAGE:
		mGame->CreateArcher(0);
		mGame->CreateArcher(0);
		break;
	case ENEMYATTHEGATES:
		mGame->ClearAIQueue();
		mGame->CreateSpearKnight(0);
		mGame->CreateSpearKnight(0);
		mGame->CreateSpearKnight(0);
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
	int temp = mVariation(mRng);
	ChangeState();
	switch (eState)
	{
	case ATTACKING:
		if (temp < 50 && temp > 20)
		{
			mGame->CreateSpearKnight(0);
			mGame->CreateAxeKnight(0);
			mGame->CreateArcher(0);
			mGame->CreateSpearKnight(0);
			mGame->CreateKnight(0);
		}
		else if (temp <= 20)
		{
			mGame->CreateSpearKnight(0);
			mGame->CreateAxeKnight(0);
			mGame->CreateArcher(0);
			mGame->CreateArcher(0);
			mGame->CreateKnight(0);
		}
		else
		{
			mGame->CreateSpearKnight(0);
			mGame->CreateKnight(0);
			mGame->CreateArcher(0);
			mGame->CreateArcher(0);
			mGame->CreateAxeKnight(0);
		}
		break;
	case UNDERATTACK:
		mGame->CreateSpearKnight(0);
		mGame->CreateSpearKnight(0);
		mGame->CreateArcher(0);
		mGame->CreateArcher(0);
		break;
	case NUMBERDISADVANTAGE:
		mGame->CreateSpearKnight(0);
		mGame->CreateArcher(0);
		mGame->CreateKnight(0);
		mGame->CreateArcher(0);
		mGame->CreateAxeKnight(0);
		mGame->CreateArcher(0);
		mGame->CreateArcher(0);
		break;
	case NUMBERADVANTAGE:
		if (temp < 40)
		{
			mGame->CreateKnight(0);
			mGame->CreateArcher(0);
		}
		else 
		{
			mGame->CreateSpearKnight(0);
			mGame->CreateArcher(0);
		}
		break;
	case ENEMYATTHEGATES:
		mGame->ClearAIQueue();
		mGame->CreateSpearKnight(0);
		mGame->CreateSpearKnight(0);
		mGame->CreateSpearKnight(0);
		mGame->CreateSpearKnight(0);
		mGame->CreateSpearKnight(0);
		break;
	}
}
