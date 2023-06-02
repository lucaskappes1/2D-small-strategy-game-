#pragma once
#include "GameObject.h"

class SpearKnight : public GameObject
{
public:
	SpearKnight(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, class Game* game, bool isPlayer);
	void Update(float deltaTime);
	void Draw();
	void Attack(GameObject* target);
	virtual void TakeDamage(int DMG);
	inline static const int getStaticGoldCost() { return mGoldCost; }
	inline const int getGoldCost() const override { return mGoldCost; }
private:
	void RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor);
	const int MAX_HP = 120;
	const int ATTACK_RELOAD_TIME = 60;
	float mPercentHPBar;
	const static int mGoldCost = 80;
};
