#pragma once
#include <vector>
#include <functional>

class UpgradeList
{
public:
	UpgradeList();
	void ApplyUpgrade(class Archer* unit);
	void ApplyUpgrade(class AxeKnight* unit);
	void ApplyUpgrade(class HeavyInfantry* unit);
	void ApplyUpgrade(class Knight* unit);
	void ApplyUpgrade(class SpearKnight* unit);
	void ApplyUpgrade(class Tower1* unit);
	void ApplyUpgrade(class Tower2* unit);

private:

	void DefineArcherUpgrade();
	void DefineAxeKnightUpgrade();
	void DefineHeavyInfantryUpgrade();
	void DefineKnightUpgrade();
	void DefineSpearKnightUpgrade();
	void DefineTower1Upgrade();
	void DefineTower2Upgrade();





	std::vector<std::pair<bool, std::function<void(class Archer* unit)>>> mArcherUpgrade;
	std::vector<std::pair<bool, std::function<void(class AxeKnight* unit)>>> mAxeKnightUpgrade;
	std::vector<std::pair<bool, std::function<void(class HeavyInfantry* unit)>>> mHeavyInfantryUpgrade;
	std::vector<std::pair<bool, std::function<void(class Knight* unit)>>> mKnightUpgrade;
	std::vector<std::pair<bool, std::function<void(class SpearKnight* unit)>>> mSpearKnightUpgrade;
	std::vector<std::pair<bool, std::function<void(class Tower1* unit)>>> mTower1Upgrade;
	std::vector<std::pair<bool, std::function<void(class Tower2* unit)>>> mTower2Upgrade;
	
};
