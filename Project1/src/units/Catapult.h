#pragma once
#include "RangedUnit.h"

class Catapult : public RangedUnit
{
public:
	Catapult(SDL_Renderer* renderer, int x, int y, class Game* game, bool isPlayer, bool isAdvancing);
	void Draw();
	void Attack(GameObject* target);
	inline const static int getStaticGoldCost() { return mGoldCost; }
	inline const int getGoldCost() const override { return mGoldCost; }
private:
	const static int mGoldCost = 425;
	void LoadAnimation();
	SDL_Texture* mAttackTexture;
	SDL_Texture* mIdleTexture;
	SDL_Texture* mDeathTexture;
	int mFrameCount;
	int mDeathAnimFrameCount;
};

