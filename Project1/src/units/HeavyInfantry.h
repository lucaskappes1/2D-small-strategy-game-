#pragma once
#include "MeleeUnit.h"

class HeavyInfantry : public MeleeUnit
{
public:
	HeavyInfantry(SDL_Renderer* renderer, int x, int y, class Game* game, bool isPlayer, bool isAdvancing);
	void Draw();
	inline static const int getStaticGoldCost() { return mGoldCost; }
	inline const int getGoldCost() const override { return mGoldCost; }
	static void LoadAnimation();
private:
	static SDL_Texture* mTexture;
	const static int mGoldCost = 380;
	int mFrameCount;
	bool mStateChanged;
};