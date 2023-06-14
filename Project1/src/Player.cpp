#include "Player.h"
#include "Game.h"
#include "units/GameObject.h"
#include "units/Knight.h"
#include "units/AxeKnight.h"
#include "units/SpearKnight.h"
#include "units/Archer.h"
#include "units/Rock.h"
#include "units/HeavyInfantry.h"
#include "UI/UI.h"

Player::Player( Game* game) : mGame(game), mGold(100), mArmorUpgradeCount(0), mAttackUpgradeCount(0), mRockUpgradeLevel(0)
{
}

void Player::CreateKnight()
{
	if (mGold >= Knight::getStaticGoldCost())
	{
		mGold -= Knight::getStaticGoldCost();
		mGame->CreateKnight(1, mIsAdvancing, mAttackUpgradeCount, mArmorUpgradeCount);
		mUI->UpdateGoldText();
	}
}

void Player::CreateSpearKnight()
{
	int x = SpearKnight::getStaticGoldCost();
	if (mGold >= SpearKnight::getStaticGoldCost())
	{
		mGold -= SpearKnight::getStaticGoldCost();
		mGame->CreateSpearKnight(1, mIsAdvancing, mAttackUpgradeCount, mArmorUpgradeCount);
		mUI->UpdateGoldText();
	}
}

void Player::CreateAxeKnight()
{
	if (mGold >= AxeKnight::getStaticGoldCost())
	{
		mGold -= AxeKnight::getStaticGoldCost();
		mGame->CreateAxeKnight(1, mIsAdvancing, mAttackUpgradeCount, mArmorUpgradeCount);
		mUI->UpdateGoldText();
	}
}

void Player::CreateArcher()
{
	if (mGold >= Archer::getStaticGoldCost())
	{
		mGold -= Archer::getStaticGoldCost();
		mGame->CreateArcher(1, mIsAdvancing, mAttackUpgradeCount, mArmorUpgradeCount);
		mUI->UpdateGoldText();
	}
}

void Player::CreateHeavyInfantry()
{
	if (mGold >= HeavyInfantry::getStaticGoldCost())
	{
		mGold -= HeavyInfantry::getStaticGoldCost();
		mGame->CreateHeavyInfantry(1, mIsAdvancing, mAttackUpgradeCount, mArmorUpgradeCount);
		mUI->UpdateGoldText();
	}
}

void Player::ChangeOrder()
{
	mIsAdvancing = !mIsAdvancing;
	mGame->PlayerChangeOrder();
}

void Player::IncreaseGold(int amount)
{
	mGold += amount;
	mUI->UpdateGoldText();
}

void Player::UpgradeArmor()
{
	if (mGold >= 500)
	{
		mGold -= 500;
		mArmorUpgradeCount++;
	}
	mUI->UpdateGoldText();
}

void Player::UpgradeAttack()
{
	if (mGold >= 500)
	{
		mGold -= 500;
		mAttackUpgradeCount++;
	}
	mUI->UpdateGoldText();
}

void Player::UpgradeRock()
{
	if (mRockUpgradeLevel == 2)
	{
		return;
	}
	else
	{
		if (mGold >= 2000)
		{
			mGold -= 2000;
			mRockUpgradeLevel++;
			mUI->UpdateGoldText();
		}
	}
}

bool Player::LaunchRock(int xDest)
{
	if (mGold >= 125)
	{
		mGold -= 125;
		Vector2 Dest((float)xDest, 658.0f);
		mGame->ThrowRock(new Rock({50.0f, 600.0f}, Dest, mGame->getRenderer(), mGame, 1, mRockUpgradeLevel));
		mUI->UpdateGoldText();
		return true;
	}
	return false;
}
