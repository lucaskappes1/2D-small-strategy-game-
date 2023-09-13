#include "Archer.h"
#include "../Game.h"
#include "Arrow.h"

Archer::Archer(SDL_Renderer* renderer, int x, int y, Game* game, bool isPlayer, bool isAdvancing)
{
	mPosition = { (float)x, (float)y };
	mVelocity = isPlayer ? Vector2(60.0f, 0.0f) : Vector2(-60.0f, 0.0f);
	mAdvancing = isAdvancing;
	mRenderer = renderer;
	mCollisionR = { x, y, 32, 32 };
	mDestR = { x, y, 32, 32 };
	mSrcR = { 0, 0, 686, 1055 };
	mGame = game;
	mIsPlayer = isPlayer;
	MAX_HP = 80;
	ATTACK_RELOAD_TIME = 40;
	mHP = MAX_HP;
	mReloadCount = 0;
	mPercentHPBar = 1.0f;
	mArmor = 4;
	mDamage = 18;
	mFrameCount = 0;
	mDeathAnimFrameCount = 0;
	LoadAnimation();
}

void Archer::Draw()
{
	switch (eState)
	{
	case Archer::ATTACKING:	
		if (eState != eLastFrameState)
		{
			mSrcR = { 0, 0, 756, 1070 };
			mFrameCount = 0;
		}
		if (mIsPlayer)
		{
			SDL_RenderCopyEx(mRenderer, mAttackTexture, &mSrcR, &mDestR, 0, nullptr, SDL_FLIP_HORIZONTAL);
		}
		else
		{
			SDL_RenderCopy(mRenderer, mAttackTexture, &mSrcR, &mDestR);
		}
		mFrameCount++;
		if (mFrameCount >= 5)
		{
			mFrameCount = 0;
			mSrcR.x += 756;
			if (mSrcR.x >= 3780)
			{
				mSrcR.x = 0;
				mSrcR.y += 1070;
				if (mSrcR.y >= 2140)
				{
					mSrcR.y = 0;
				}
			}
		}
		RenderHPBar(mPosition.getIntX(), mPosition.getIntY() - 5, 28, 3, mPercentHPBar, {0, 255, 0, 255}, {255, 0, 0, 255});
		break;
	case Archer::WALKING:		
		if (eState != eLastFrameState)
		{
			mSrcR = { 0, 0, 686, 1055 };
			mFrameCount = 0;
		}
		if (mIsPlayer)
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
			mSrcR.x += 686;
			if (mSrcR.x >= 3430)
			{
				mSrcR.x = 0;
				mSrcR.y += 1055;
				if (mSrcR.y >= 2110)
				{
					mSrcR.y = 0;
				}
			}
		}
		RenderHPBar(mPosition.getIntX(), mPosition.getIntY() - 5, 28, 3, mPercentHPBar, { 0, 255, 0, 255 }, { 255, 0, 0, 255 });
		break;
	case Archer::IDLE:		
		if (mIsPlayer)
		{
			SDL_RenderCopyEx(mRenderer, mIdleTexture, NULL, &mDestR, 0, nullptr, SDL_FLIP_HORIZONTAL);
		}
		else
		{
			SDL_RenderCopy(mRenderer, mIdleTexture, NULL, &mDestR);
		}
		RenderHPBar(mPosition.getIntX(), mPosition.getIntY() - 5, 28, 3, mPercentHPBar, { 0, 255, 0, 255 }, { 255, 0, 0, 255 });
		break;
	case Archer::DEATH:
		if (eState != eLastFrameState)
		{
			mSrcR = { 0, 0, 683, 1122 };
			mFrameCount = 0;
			eLastFrameState = eState;
		}
		if (mIsPlayer)
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
			mSrcR.x += 683;
			mDeathAnimFrameCount++;
			if (mDeathAnimFrameCount >= 6)
			{
				mSrcR.x -= 683;
			}
			if (mSrcR.x >= 3415)
			{
				mSrcR.x = 0;
				mSrcR.y += 1122;
				if (mSrcR.y >= 2244)
				{
					mSrcR.y = 0;

				}
			}
		}
		break;
	}
}

void Archer::Attack(GameObject* target)
{
	mGame->AddProjectile(new Arrow(mPosition, target, mRenderer, mGame, mDamage));
	mReloadCount = ATTACK_RELOAD_TIME;
}

void Archer::LoadAnimation()
{
	mTexture = mGame->getTexture(ARCHER_WALK);
	mIdleTexture = mGame->getTexture(ARCHER_IDLE);
	mAttackTexture = mGame->getTexture(ARCHER_ATTACK);
	mDeathTexture = mGame->getTexture(ARCHER_DEATH);
}
