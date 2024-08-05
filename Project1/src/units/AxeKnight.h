#pragma once
#include "MeleeUnit.h"
#include <vector>

class AxeKnight :  public MeleeUnit
{
public:
	AxeKnight(SDL_Renderer* renderer, int x, int y, class Game* game, bool isPlayer, bool isAdvancing);
	void Draw();
	inline static const int getStaticGoldCost() { return mGoldCost; }
	inline const int getGoldCost() const override { return mGoldCost; }
	static void LoadAnimation();

private:
	static std::vector<SDL_Texture*> mWalkingAnimVec;
	static std::vector<SDL_Texture*> mAttackingAnimVec;
	static std::vector<SDL_Texture*> mDeathAnimVec;
	static SDL_Texture* mIdleTexture;
	const static int mGoldCost = 60;
	int mCurrentFrame;
	int mFrameCount;
};