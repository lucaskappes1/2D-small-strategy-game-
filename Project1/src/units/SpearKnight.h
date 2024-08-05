#pragma once
#include "MeleeUnit.h"

class SpearKnight : public MeleeUnit
{
public:
	SpearKnight(SDL_Renderer* renderer, int x, int y, class Game* game, bool isPlayer, bool isAdvancing);
	void Draw();
	inline static const int getStaticGoldCost() { return mGoldCost; }
	inline const int getGoldCost() const override { return mGoldCost; }
	static void LoadAnimation();
private:
	static SDL_Texture* mTexture;
	static SDL_Texture* mTextureAttack;
	static SDL_Texture* mIdleTexture;
	static SDL_Texture* mDeathTexture;
	const static int mGoldCost = 80;
	int mFrameCount;
	bool mStateChanged;
};