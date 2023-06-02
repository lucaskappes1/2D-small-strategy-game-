#pragma once
#include "GameObject.h"
class Archer :
    public GameObject
{
public:
	Archer(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, class Game* game, bool isPlayer);
	void Update(float deltaTime);
	void Draw();
	void Attack(GameObject* target);
	virtual void TakeDamage(int DMG);
	inline const static int getStaticGoldCost() { return mGoldCost; }
	inline const int getGoldCost() const override { return mGoldCost; }
private:
	void RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor);
	float mPercentHPBar;
	const int MAX_HP = 60;
	const int ATTACK_RELOAD_TIME = 40;
	const static int mGoldCost = 55;
};

