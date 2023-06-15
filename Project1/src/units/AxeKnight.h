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
	
private:
	std::vector<SDL_Texture*> mWalkingAnimVec;
	std::vector<SDL_Texture*> mAttackingAnimVec;
	std::vector<SDL_Texture*> mDeathAnimVec;
	SDL_Texture* mIdleTexture;
	const static int mGoldCost = 60;
	int mCurrentFrame;
	void LoadAnimation();
	int mFrameCount;
};