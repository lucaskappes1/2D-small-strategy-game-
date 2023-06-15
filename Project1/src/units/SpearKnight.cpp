#include "SpearKnight.h"
#include "../Game.h"

SpearKnight::SpearKnight(SDL_Renderer* renderer, int x, int y, class Game* game, bool isPlayer, bool isAdvancing)
{
	MAX_HP = 200;
	ATTACK_RELOAD_TIME = 45;
	mAdvancing = isAdvancing;
	mIsPlayer = isPlayer;
	mRenderer = renderer;
	mPosition = { (float)x, (float)y };
	mVelocity = isPlayer ? Vector2(60.0f, 0.0f) : Vector2(-60.0f, 0.0f);
	mDestR = { x, y, 32,  32 };
	mCollisionR = { x, y, 32, 32 };
	mGame = game;
	mHP = MAX_HP;
	mReloadCount = 0;
	mPercentHPBar = 1.0f;
	mArmor = 12;
	mDamage = 34;
	mFrameCount = 0;
	mSrcR = { 0, 0, 191, 123 };
	LoadAnimation();
}

void SpearKnight::Draw()
{
	switch (eState)
	{
	case GameObject::ATTACKING:
		if (eLastFrameState != eState)
		{
			mSrcR.x = 0;
			mFrameCount = 0;
		}
		if (!mIsPlayer)
		{
			SDL_RenderCopyEx(mRenderer, mTextureAttack, &mSrcR, &mDestR, 0, nullptr, SDL_FLIP_HORIZONTAL);
		}
		else
		{
			SDL_RenderCopy(mRenderer, mTextureAttack, &mSrcR, &mDestR);
		}
		mFrameCount++;
		if (mFrameCount >= 5)
		{
			mFrameCount = 0;
			mSrcR.x += 235;
			if (mSrcR.x >= 1880)
			{
				mSrcR.x = 0;
			}
		}
		RenderHPBar(mPosition.getIntX(), mPosition.getIntY() - 5, 28, 3, mPercentHPBar, { 0, 255, 0, 255 }, { 255, 0, 0, 255 });
		break;
	case GameObject::WALKING:
		if (eLastFrameState != eState)
		{
			mSrcR.x = 0;
			mFrameCount = 0;
		}
		if (!mIsPlayer)
		{
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
			mSrcR.x += 191;
			if (mSrcR.x >= 1910)
			{
				mSrcR.x = 0;
			}
		}
		RenderHPBar(mPosition.getIntX(), mPosition.getIntY() - 5, 28, 3, mPercentHPBar, { 0, 255, 0, 255 }, { 255, 0, 0, 255 });
		break;
	case GameObject::IDLE:
		mSrcR.x = 1281;
		if (!mIsPlayer)
		{
			SDL_RenderCopyEx(mRenderer, mIdleTexture, &mSrcR, &mDestR, 0, nullptr, SDL_FLIP_HORIZONTAL);
		}
		else
		{
			SDL_RenderCopy(mRenderer, mIdleTexture, &mSrcR, &mDestR);
		}
		RenderHPBar(mPosition.getIntX(), mPosition.getIntY() - 5, 28, 3, mPercentHPBar, { 0, 255, 0, 255 }, { 255, 0, 0, 255 });
		break;
	case GameObject::DEATH:
		if (eLastFrameState != eState)
		{
			mSrcR.x = 0;
			mFrameCount = 0;
			eLastFrameState = eState;
		}
		if (!mIsPlayer)
		{
			SDL_RenderCopyEx(mRenderer, mDeathTexture, &mSrcR, &mDestR, 0, nullptr, SDL_FLIP_HORIZONTAL);
		}
		else
		{
			SDL_RenderCopy(mRenderer, mDeathTexture, &mSrcR, &mDestR);
		}
		mFrameCount++;
		if (mFrameCount >= 5)
		{
			mFrameCount = 0;
			mSrcR.x += 163;
			if (mSrcR.x >= 1304)
			{
				mSrcR.x -= 163;
			}
		}
		break;
	}
}

void SpearKnight::LoadAnimation()
{
	mTexture = mGame->getTexture(SPEARMAN_WALK);
	mTextureAttack = mGame->getTexture(SPEARKMAN_ATTACK);
	mIdleTexture = mGame->getTexture(SPEARMAN_IDLE);
	mDeathTexture = mGame->getTexture(SPEARMAN_DEATH);
}
