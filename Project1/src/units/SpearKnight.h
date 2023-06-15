#pragma once
#include "MeleeUnit.h"

class SpearKnight : public MeleeUnit
{
public:
	SpearKnight(SDL_Renderer* renderer, int x, int y, class Game* game, bool isPlayer, bool isAdvancing);
	void Draw();
	inline static const int getStaticGoldCost() { return mGoldCost; }
	inline const int getGoldCost() const override { return mGoldCost; }
private:
	SDL_Texture* mTextureAttack;
	SDL_Texture* mIdleTexture;
	SDL_Texture* mDeathTexture;
	const static int mGoldCost = 80;
	void LoadAnimation();
	int mFrameCount;
	bool mStateChanged;
};