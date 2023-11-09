#include "UpgradeList.h"
#include "../units/Archer.h"
#include "../units/AxeKnight.h"
#include "../units/HeavyInfantry.h"
#include "../units/Knight.h"
#include "../units/SpearKnight.h"
#include "../units/Tower1.h"
#include "../units/Tower2.h"
#include <iostream>

UpgradeList::UpgradeList()
{
	DefineArcherUpgrade();
	DefineAxeKnightUpgrade();
	DefineHeavyInfantryUpgrade();
	DefineKnightUpgrade();
	DefineSpearKnightUpgrade();
	DefineTower1Upgrade();
	DefineTower2Upgrade();
}

void UpgradeList::ApplyUpgrade(Archer* unit)
{
	for (auto& i : mArcherUpgrade)
	{
		if (i.first)
		{
			i.second(unit);
		}
	}
}

void UpgradeList::ApplyUpgrade(AxeKnight* unit)
{
	for (auto& i : mAxeKnightUpgrade)
	{
		if (i.first)
		{
			i.second(unit);
		}
	}
}

void UpgradeList::ApplyUpgrade(HeavyInfantry* unit)
{
	for (auto& i : mHeavyInfantryUpgrade)
	{
		if (i.first)
		{
			i.second(unit);
		}
	}
}

void UpgradeList::ApplyUpgrade(Knight* unit)
{
	for (auto& i : mKnightUpgrade)
	{
		if (i.first)
		{
			i.second(unit);
		}
	}
}

void UpgradeList::ApplyUpgrade(SpearKnight* unit)
{
	for (auto& i : mSpearKnightUpgrade)
	{
		if (i.first)
		{
			i.second(unit);
		}
	}
}

void UpgradeList::ApplyUpgrade(Tower1* unit)
{
	for (auto& i : mTower1Upgrade)
	{
		if (i.first)
		{
			i.second(unit);
		}
	}
}

void UpgradeList::ApplyUpgrade(Tower2* unit)
{
	for (auto& i : mTower2Upgrade)
	{
		if (i.first)
		{
			i.second(unit);
		}
	}
}

void UpgradeList::DefineArcherUpgrade()
{
	mArcherUpgrade.emplace_back(std::make_pair(false, [](Archer* unit)
		{
			unit->setProjectileNumber(3);
			unit->setAttackReloadTime(unit->getAttackReloadTime() * 2);
		}));
}

void UpgradeList::DefineAxeKnightUpgrade()
{
	mAxeKnightUpgrade.emplace_back(std::make_pair(false, [](AxeKnight* unit)
		{
			unit->setBlockChance(35);
		}));
}

void UpgradeList::DefineHeavyInfantryUpgrade()
{
}

void UpgradeList::DefineKnightUpgrade()
{
	mKnightUpgrade.emplace_back(std::make_pair(false, [](Knight* unit)
		{
			unit->setBlockChance(25);
		}));
}

void UpgradeList::DefineSpearKnightUpgrade()
{
	mSpearKnightUpgrade.emplace_back(std::make_pair(false, [](SpearKnight* unit)
		{
			unit->setBlockChance(20);
		}));
}

void UpgradeList::DefineTower1Upgrade()
{
	mTower1Upgrade.emplace_back(std::make_pair(false, [](Tower1* unit)
		{
			unit->setProjectileNumber(3);
			unit->setAttackReloadTime(unit->getAttackReloadTime() * 2);
		}));
}

void UpgradeList::DefineTower2Upgrade()
{
	mTower2Upgrade.emplace_back(std::make_pair(false, [](Tower2* unit)
		{
			unit->setProjectileNumber(3);
			unit->setAttackReloadTime(unit->getAttackReloadTime() * 2);
		}));
}
