#pragma once
class Player
{
public:
	Player(class Game* game);
	void CreateKnight();
	void CreateSpearKnight();
	void CreateAxeKnight();
	void CreateArcher();
	void ChangeOrder();
	void IncreaseGold(int amount);
	void UpgradeArmor();
	void UpgradeAttack();
	bool getIsPlayerAdvancing() { return mIsAdvancing; }
	void setUiPointer(class UI* Ui) { mUI = Ui; }
	inline int getGold() { return mGold; }
private:
	bool mIsAdvancing;
	int mGold;
	int mAttackUpgradeCount;
	int mArmorUpgradeCount;
	class UI* mUI;
	class Game* mGame;
};

