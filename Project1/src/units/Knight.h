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
private:
	const static int mGoldCost = 35;
	int mFrameCount;
	int mCurrentFrame;
	std::vector<SDL_Texture*> mWalkingAnimVec;
	std::vector<SDL_Texture*> mAttackingAnimVec;
	std::vector<SDL_Texture*> mDeathAnimVec;
	SDL_Texture* mIdleTexture;
	void LoadAnimation();
};
