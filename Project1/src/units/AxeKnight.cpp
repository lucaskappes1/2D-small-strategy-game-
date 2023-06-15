#include "AxeKnight.h"
#include "../Game.h"

AxeKnight::AxeKnight(SDL_Renderer* renderer, int x, int y, Game* game, bool isPlayer, bool isAdvancing)
{
	MAX_HP = 160;
	ATTACK_RELOAD_TIME = 70;
	mAdvancing = isAdvancing;
	mRenderer = renderer;
	mDestR = { x, y, 32, 32 };
	mCollisionR = { x, y, 32, 32 };
	mPosition = { (float)x, (float)y };
	mVelocity = isPlayer ? Vector2(60.0f, 0.0f) : Vector2(-60.0f, 0.0f);
	mGame = game;
	mIsPlayer = isPlayer;
	mHP = MAX_HP;
	mReloadCount = 0;
	mPercentHPBar = 1.0f;
	mArmor = 0;
	mDamage = 80;
	mCurrentFrame = 0;
	mFrameCount = 0;
	eState = WALKING;
	LoadAnimation();
}

void AxeKnight::Draw()
{
	switch (eState)
	{
	case AxeKnight::ATTACKING:
		mDestR.w = 77;
		if (eState != eLastFrameState)
		{
			mFrameCount = 0;
			mCurrentFrame = 0;
		}
		if (!mIsPlayer)
		{
			mDestR.x = mPosition.getIntX() - 25;
			SDL_RenderCopyEx(mRenderer, mAttackingAnimVec.at(mCurrentFrame), NULL, &mDestR, 0, nullptr, SDL_FLIP_HORIZONTAL);
		}
		else
		{
			mDestR.x = mPosition.getIntX() - 15;
			SDL_RenderCopy(mRenderer, mAttackingAnimVec.at(mCurrentFrame), NULL, &mDestR);
		}
		mFrameCount++;
		if (mFrameCount >= 5)
		{
			mFrameCount = 0;
			mCurrentFrame++;
			if (mCurrentFrame > 7)
			{
				mCurrentFrame = 0;
			}
		}
		RenderHPBar(mPosition.getIntX(), mPosition.getIntY() - 5, 28, 3, mPercentHPBar, { 0, 255, 0, 255 }, { 255, 0, 0, 255 });
		break;
	case AxeKnight::WALKING:
		mDestR.w = 32;
		if (eState != eLastFrameState)
		{
			mFrameCount = 0;
			mCurrentFrame = 0;
		}
		if (!mIsPlayer)
		{
			SDL_RenderCopyEx(mRenderer, mWalkingAnimVec.at(mCurrentFrame), NULL, &mDestR, 0, nullptr, SDL_FLIP_HORIZONTAL);
		}
		else
		{
			SDL_RenderCopy(mRenderer, mWalkingAnimVec.at(mCurrentFrame), NULL, &mDestR);
		}
		mFrameCount++;
		if (mFrameCount >= 5)
		{
			mFrameCount = 0;
			mCurrentFrame++;
			if (mCurrentFrame > 11)
			{
				mCurrentFrame = 0;
			}
		}
		RenderHPBar(mPosition.getIntX(), mPosition.getIntY() - 5, 28, 3, mPercentHPBar, { 0, 255, 0, 255 }, { 255, 0, 0, 255 });
		break;
	case AxeKnight::IDLE:
		mDestR.w = 32;
		mDestR.x = mPosition.getIntX();
		if (!mIsPlayer)
		{
			SDL_RenderCopyEx(mRenderer, mIdleTexture, NULL, &mDestR, 0, nullptr, SDL_FLIP_HORIZONTAL);
		}
		else
		{
			SDL_RenderCopy(mRenderer, mIdleTexture, NULL, &mDestR);
		}
		RenderHPBar(mPosition.getIntX(), mPosition.getIntY() - 5, 28, 3, mPercentHPBar, { 0, 255, 0, 255 }, { 255, 0, 0, 255 });
		break;
	case AxeKnight::DEATH:
		mDestR.w = 59;
		mDestR.h = 50;
		if (eState != eLastFrameState)
		{
			mFrameCount = 0;
			mCurrentFrame = 0;
			eLastFrameState = eState;
		}
		if (!mIsPlayer)
		{
			mDestR.x = mPosition.getIntX() - 20;
			SDL_RenderCopyEx(mRenderer, mDeathAnimVec.at(mCurrentFrame), NULL, &mDestR, 0, nullptr, SDL_FLIP_HORIZONTAL);
		}
		else
		{
			mDestR.x = mPosition.getIntX() - 20;
			SDL_RenderCopy(mRenderer, mDeathAnimVec.at(mCurrentFrame), NULL, &mDestR);
		}
		mFrameCount++;
		if (mFrameCount >= 5)
		{
			mFrameCount = 0;
			mCurrentFrame++;
			if (mCurrentFrame > 11)
			{
				mCurrentFrame = 11;
			}
		}
		break;
	}
}

void AxeKnight::LoadAnimation()
{
	mWalkingAnimVec.emplace_back(mGame->getTexture(GREEK_WALK0));
	mWalkingAnimVec.emplace_back(mGame->getTexture(GREEK_WALK1));
	mWalkingAnimVec.emplace_back(mGame->getTexture(GREEK_WALK2));
	mWalkingAnimVec.emplace_back(mGame->getTexture(GREEK_WALK3));
	mWalkingAnimVec.emplace_back(mGame->getTexture(GREEK_WALK4));
	mWalkingAnimVec.emplace_back(mGame->getTexture(GREEK_WALK5));
	mWalkingAnimVec.emplace_back(mGame->getTexture(GREEK_WALK6));
	mWalkingAnimVec.emplace_back(mGame->getTexture(GREEK_WALK7));
	mWalkingAnimVec.emplace_back(mGame->getTexture(GREEK_WALK8));
	mWalkingAnimVec.emplace_back(mGame->getTexture(GREEK_WALK9));
	mWalkingAnimVec.emplace_back(mGame->getTexture(GREEK_WALK10));
	mWalkingAnimVec.emplace_back(mGame->getTexture(GREEK_WALK11));

	mAttackingAnimVec.emplace_back(mGame->getTexture(GREEK_ATTACK0));
	mAttackingAnimVec.emplace_back(mGame->getTexture(GREEK_ATTACK1));
	mAttackingAnimVec.emplace_back(mGame->getTexture(GREEK_ATTACK2));
	mAttackingAnimVec.emplace_back(mGame->getTexture(GREEK_ATTACK3));
	mAttackingAnimVec.emplace_back(mGame->getTexture(GREEK_ATTACK4));
	mAttackingAnimVec.emplace_back(mGame->getTexture(GREEK_ATTACK5));
	mAttackingAnimVec.emplace_back(mGame->getTexture(GREEK_ATTACK6));
	mAttackingAnimVec.emplace_back(mGame->getTexture(GREEK_ATTACK7));

	mDeathAnimVec.emplace_back(mGame->getTexture(GREEK_DEATH0));
	mDeathAnimVec.emplace_back(mGame->getTexture(GREEK_DEATH1));
	mDeathAnimVec.emplace_back(mGame->getTexture(GREEK_DEATH2));
	mDeathAnimVec.emplace_back(mGame->getTexture(GREEK_DEATH3));
	mDeathAnimVec.emplace_back(mGame->getTexture(GREEK_DEATH4));
	mDeathAnimVec.emplace_back(mGame->getTexture(GREEK_DEATH5));
	mDeathAnimVec.emplace_back(mGame->getTexture(GREEK_DEATH6));
	mDeathAnimVec.emplace_back(mGame->getTexture(GREEK_DEATH7));
	mDeathAnimVec.emplace_back(mGame->getTexture(GREEK_DEATH8));
	mDeathAnimVec.emplace_back(mGame->getTexture(GREEK_DEATH9));
	mDeathAnimVec.emplace_back(mGame->getTexture(GREEK_DEATH10));
	mDeathAnimVec.emplace_back(mGame->getTexture(GREEK_DEATH11));

	mIdleTexture = mGame->getTexture(GREEK_IDLE);
}
