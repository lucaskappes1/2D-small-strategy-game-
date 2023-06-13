#include "Player.h"
#include "Game.h"
#include "units/GameObject.h"
#include "units/Knight.h"
#include "units/AxeKnight.h"
#include "units/SpearKnight.h"
#include "units/Archer.h"
#include "units/Projectile.h"
#include "UI/UI.h"

Player::Player( Game* game) : mGame(game), mGold(100), mArmorUpgradeCount(0), mAttackUpgradeCount(0)
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

bool Player::LaunchRock(int xDest)
{
	if (mGold >= 50)
	{
		mGold -= 150;
		Vector2 Dest((float)xDest, 658.0f);
		mGame->ThrowRock(new Projectile({50.0f, 600.0f}, {(float)xDest, 658.0f}, mGame->getRenderer(), mGame));
		mUI->UpdateGoldText();
		return true;
	}
	return false;
}
