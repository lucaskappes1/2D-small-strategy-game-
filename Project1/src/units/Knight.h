#pragma once
#include "MeleeUnit.h"
#include <vector>

class Knight :  public MeleeUnit
{
public:
	Knight(SDL_Renderer* renderer, int x, int y, class Game* game, bool isPlayer, bool isAdvancing);
	void Draw();
	inline static const int getStaticGoldCost() { return mGoldCost; }
	inline const int getGoldCost() const override { return mGoldCost; }
	static void LoadAnimation();
private:
	const static int mGoldCost = 35;
	int mFrameCount;
	int mCurrentFrame;
	static std::vector<SDL_Texture*> mWalkingAnimVec;
	static std::vector<SDL_Texture*> mAttackingAnimVec;
	static std::vector<SDL_Texture*> mDeathAnimVec;
	static SDL_Texture* mIdleTexture;
};
