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
	static void LoadAnimation();
private:
	const static int mGoldCost = 425;
	static SDL_Texture* mAttackTexture;
	static SDL_Texture* mIdleTexture;
	static SDL_Texture* mDeathTexture;
	static SDL_Texture* mTexture;
	int mFrameCount;
	int mDeathAnimFrameCount;
};

