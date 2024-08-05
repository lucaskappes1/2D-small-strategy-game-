#include "HeavyInfantry.h"
#include "../Game.h"
#include "../TextureManager.h"

SDL_Texture* HeavyInfantry::mTexture = nullptr;

HeavyInfantry::HeavyInfantry(SDL_Renderer* renderer, int x, int y, Game* game, bool isPlayer, bool isAdvancing) 
{
	MAX_HP = 400;
	ATTACK_RELOAD_TIME = 10;
	mAdvancing = isAdvancing;
	mIsPlayer = isPlayer;
	mRenderer = renderer;
	mPosition = { (float)x, (float)y };
	mVelocity = isPlayer ? Vector2(100.0f, 0.0f) : Vector2(-100.0f, 0.0f);
	mSrcR = { 45, 560, 78, 60 };
	mDestR = { x, y, 45,  38 };
	mCollisionR = { x, y, 32, 32 };
	mGame = game;
	mHP = MAX_HP;
	mReloadCount = 0;
	mPercentHPBar = 1.0f;
	mArmor = 14;
	mDamage = 17;
	mFrameCount = 0;
	LoadAnimation();
}

void HeavyInfantry::Draw()
{
	switch (eState)
	{
	case State::ATTACKING:
		if (eLastFrameState != eState)
		{
			mSrcR.x = 1581;
			mFrameCount = 0;
		}
		if (!mIsPlayer)
		{
			mDestR.x = mPosition.getIntX();
			mDestR.x -= 15;
			SDL_RenderCopyEx(mRenderer, mTexture, &mSrcR, &mDestR, 0, nullptr, SDL_FLIP_HORIZONTAL);
		}
		else
		{
			SDL_RenderCopy(mRenderer, mTexture, &mSrcR, &mDestR);
		}
		mFrameCount++;
		if (mFrameCount >= 5)
		{
			mFrameCount = 0;
			mSrcR.x += 128;
			if (mSrcR.x >= 2093)
			{
				mSrcR.x = 1581;
			}
		}
		RenderHPBar(mPosition.getIntX(), mPosition.getIntY() - 5, 28, 3, mPercentHPBar, { 0, 255, 0, 255 }, { 255, 0, 0, 255 });
		break;
	case State::WALKING:
		if (eLastFrameState != eState)
		{
			mSrcR.x = 557;
			mFrameCount = 0;
		}
		if (!mIsPlayer)
		{
			mDestR.x = mPosition.getIntX();
			mDestR.x -= 15;
			SDL_RenderCopyEx(mRenderer, mTexture, &mSrcR, &mDestR, 0, nullptr, SDL_FLIP_HORIZONTAL);
		}
		else
		{
			SDL_RenderCopy(mRenderer, mTexture, &mSrcR, &mDestR);
		}
		mFrameCount++;
		if (mFrameCount >= 5)
		{
			mFrameCount = 0;
			mSrcR.x += 128;
			if (mSrcR.x >= 1581)
			{
				mSrcR.x = 557;
			}
		}
		RenderHPBar(mPosition.getIntX(), mPosition.getIntY() - 5, 28, 3, mPercentHPBar, { 0, 255, 0, 255 }, { 255, 0, 0, 255 });
		break;
	case State::IDLE:
		mSrcR.x = 45;
		if (!mIsPlayer)
		{
			mDestR.x -= 15;
			SDL_RenderCopyEx(mRenderer, mTexture, &mSrcR, &mDestR, 0, nullptr, SDL_FLIP_HORIZONTAL);
		}
		else
		{
			SDL_RenderCopy(mRenderer, mTexture, &mSrcR, &mDestR);
		}
		RenderHPBar(mPosition.getIntX(), mPosition.getIntY() - 5, 28, 3, mPercentHPBar, { 0, 255, 0, 255 }, { 255, 0, 0, 255 });
		break;
	case State::DEATH:
		if (eLastFrameState != eState)
		{
			mSrcR.x = 2093;
			mFrameCount = 0;
			eLastFrameState = eState;
		}
		if (!mIsPlayer)
		{
			mDestR.x = mPosition.getIntX();
			mDestR.x -= 15;
			SDL_RenderCopyEx(mRenderer, mTexture, &mSrcR, &mDestR, 0, nullptr, SDL_FLIP_HORIZONTAL);
		}
		else
		{
			SDL_RenderCopy(mRenderer, mTexture, &mSrcR, &mDestR);
		}
		mFrameCount++;
		if (mFrameCount >= 5)
		{
			mFrameCount = 0;
			mSrcR.x += 128;
			if (mSrcR.x >= 3117)
			{
				mSrcR.x -= 128;
			}
		}
		break;
	}
}

void HeavyInfantry::LoadAnimation()
{
	mTexture = TextureManager::getTexture(HEAVY_INFANTRY);
}
