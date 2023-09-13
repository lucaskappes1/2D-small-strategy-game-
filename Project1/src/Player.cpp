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
		GameObject* temp = new Knight(mGame->getRenderer(), mGame->getPlayerCreateUnitPosition(), HEIGHT - 110, mGame, 1, mIsAdvancing);
		ApplyUpgrade(temp);
		mGame->CreateUnit(temp);
		mUI->UpdateGoldText();
	}
}

void Player::CreateSpearKnight()
{
	if (mGold >= SpearKnight::getStaticGoldCost())
	{
		mGold -= SpearKnight::getStaticGoldCost();
		GameObject* temp = new SpearKnight(mGame->getRenderer(), mGame->getPlayerCreateUnitPosition(), HEIGHT - 110, mGame, 1, mIsAdvancing);
		ApplyUpgrade(temp);
		mGame->CreateUnit(temp);
		mUI->UpdateGoldText();
	}
}

void Player::CreateAxeKnight()
{
	if (mGold >= AxeKnight::getStaticGoldCost())
	{
		mGold -= AxeKnight::getStaticGoldCost();
		GameObject* temp = new AxeKnight(mGame->getRenderer(), mGame->getPlayerCreateUnitPosition(), HEIGHT - 110, mGame, 1, mIsAdvancing);
		ApplyUpgrade(temp);
		mGame->CreateUnit(temp);
		mUI->UpdateGoldText();
	}
}

void Player::CreateArcher()
{
	if (mGold >= Archer::getStaticGoldCost())
	{
		mGold -= Archer::getStaticGoldCost();
		GameObject* temp = new Archer(mGame->getRenderer(), mGame->getPlayerCreateUnitPosition(), HEIGHT - 110, mGame, 1, mIsAdvancing);
		ApplyUpgrade(temp);
		mGame->CreateUnit(temp);
		mUI->UpdateGoldText();
	}
}

void Player::CreateHeavyInfantry()
{
	if (mGold >= HeavyInfantry::getStaticGoldCost())
	{
		mGold -= HeavyInfantry::getStaticGoldCost();
		GameObject* temp = new HeavyInfantry(mGame->getRenderer(), mGame->getPlayerCreateUnitPosition(), HEIGHT - 110, mGame, 1, mIsAdvancing);
		ApplyUpgrade(temp);
		mGame->CreateUnit(temp);
		mUI->UpdateGoldText();
	}
}

void Player::CreateTower1()
{
	if (mGold >= Tower1::getStaticGoldCost() && mGame->getPlayerBuildingCount() < 3)
	{
		mGold -= Tower1::getStaticGoldCost();
		GameObject* temp = new Tower1(mGame->getRenderer(), mGame->getPlayerCreateUnitPosition(), HEIGHT - 175, mGame, 1);
		mGame->CreateUnit(temp);
		mUI->UpdateGoldText();
		mGame->IncreasePlayerBuildingCount();
	}
}

void Player::CreateTower2()
{
	if (mGold >= Tower2::getStaticGoldCost() && mGame->getPlayerBuildingCount() < 3)
	{
		mGold -= Tower2::getStaticGoldCost();
		GameObject* temp = new Tower2(mGame->getRenderer(), mGame->getPlayerCreateUnitPosition(), HEIGHT - 175, mGame, 1);
		mGame->CreateUnit(temp);
		mUI->UpdateGoldText();
		mGame->IncreasePlayerBuildingCount();
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
	if (mGold >= 150)
	{
		mGold -= 150;
		if (xDest >= 650)
		{
			xDest = 650;
		}
		Vector2 Dest((float)xDest, 658.0f);
		mGame->AddProjectile(new Rock({50.0f, 600.0f}, Dest, mGame->getRenderer(), mGame, mRockUpgradeLevel));
		mUI->UpdateGoldText();
		return true;
	}
	return false;
}

void Player::ApplyUpgrade(GameObject* unit)
{
	unit->setAttack(unit->getAttack() + mAttackUpgradeCount);
	unit->setArmor(unit->getArmor() + mArmorUpgradeCount);
}
