#pragma once

class Player
{
public:
	Player(class Game* game);
	void CreateKnight();
	void CreateSpearKnight();
	void CreateAxeKnight();
	void CreateArcher();
	void CreateHeavyInfantry();
	void CreateCatapult();
	void CreateTower1();
	void CreateTower2();
	void ChangeOrder();
	void IncreaseGold(int amount);
	void UpgradeArmor();
	void UpgradeAttack();
	void UpgradeRock();
	void BuyShieldUpgrade();
	void BuyArcherUpgrade();
	void BuyTowerUpgrade();
	bool LaunchRock(int xDest);
	bool getIsPlayerAdvancing() { return mIsAdvancing; }
	void setUiPointer(class UI* Ui) { mUI = Ui; }
	inline int getGold() { return mGold; }
private:
	void ApplyUpgrade(class GameObject* unit);
	bool mIsAdvancing;
	int mGold;
	int mPlatinum;
	int mAttackUpgradeCount;
	int mArmorUpgradeCount;
	int mRockUpgradeLevel;
	class UpgradeList* mUpgrade;
	class UI* mUI;
	class Game* mGame;
};

