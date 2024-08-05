#include "Catapult.h"
#include "Rock.h"
#include "../Game.h"
#include "../TextureManager.h"

SDL_Texture* Catapult::mTexture = nullptr;

Catapult::Catapult(SDL_Renderer* renderer, int x, int y, Game* game, bool isPlayer, bool isAdvancing)
{
	mPosition = { (float)x, (float)y };
	mVelocity = isPlayer ? Vector2(20.0f, 0.0f) : Vector2(-20.0f, 0.0f);
	mAdvancing = isAdvancing;
	mRenderer = renderer;
	mCollisionR = { x, y, 32, 32 };
	mDestR = { x, y, 32, 32 };
	mSrcR = { 0, 0, 686, 1055 };
	mGame = game;
	mIsPlayer = isPlayer;
	MAX_HP = 150;
	ATTACK_RELOAD_TIME = 120;
	mHP = MAX_HP;
	mReloadCount = 0;
	mPercentHPBar = 1.0f;
	mArmor = 4;
	mDamage = 18;
	mFrameCount = 0;
	mDeathAnimFrameCount = 0;
	mRange = 300;
	mProjectileNumber = 1;
	LoadAnimation();
}

void Catapult::Draw()
{
	switch (Catapult::eState)
	{
	case State::ATTACKING:
		if (eState != eLastFrameState)
		{
			mSrcR = { 256, 256, 128, 128 };
			mFrameCount = 0;
		}
		if (mIsPlayer)
		{
			SDL_RenderCopy(mRenderer, mTexture, &mSrcR, &mDestR);
		}
		else
		{
			SDL_RenderCopyEx(mRenderer, mTexture, &mSrcR, &mDestR, 0, nullptr, SDL_FLIP_HORIZONTAL);
		}
		mFrameCount++;
		if (mFrameCount >= 5)
		{
			mFrameCount = 0;
			mSrcR.x += 128;
			if (mSrcR.x >= 768)
			{
				mSrcR.x = 256;
				eLastFrameState = State::ATTACKING;
				eState = State::IDLE;
			}
		}
		RenderHPBar(mPosition.getIntX(), mPosition.getIntY() - 5, 28, 3, mPercentHPBar, { 0, 255, 0, 255 }, { 255, 0, 0, 255 });
		break;
	case State::WALKING:
		if (eState != eLastFrameState)
		{
			mSrcR = { 0, 256, 128, 128};
			mFrameCount = 0;
		}
		if (mIsPlayer)
		{
			SDL_RenderCopy(mRenderer, mTexture, &mSrcR, &mDestR);
		}
		else
		{
			SDL_RenderCopyEx(mRenderer, mTexture, &mSrcR, &mDestR, 0, nullptr, SDL_FLIP_HORIZONTAL);
		}
		mFrameCount++;
		if (mFrameCount >= 5)
		{
			mFrameCount = 0;
			mSrcR.x += 128;
			if (mSrcR.x >= 256)
			{
				mSrcR.x = 0;
			}
		}
		RenderHPBar(mPosition.getIntX(), mPosition.getIntY() - 5, 28, 3, mPercentHPBar, { 0, 255, 0, 255 }, { 255, 0, 0, 255 });
		break;
	case State::IDLE:
		mSrcR = { 0, 256, 128, 128 };
		if (mIsPlayer)
		{
			SDL_RenderCopy(mRenderer, mTexture, &mSrcR, &mDestR);
		}
		else
		{
			SDL_RenderCopyEx(mRenderer, mTexture, &mSrcR, &mDestR, 0, nullptr, SDL_FLIP_HORIZONTAL);
		}
		RenderHPBar(mPosition.getIntX(), mPosition.getIntY() - 5, 28, 3, mPercentHPBar, { 0, 255, 0, 255 }, { 255, 0, 0, 255 });
		break;
	case State::DEATH:
		break;
	}
}

void Catapult::Attack(GameObject* target)
{
	mGame->AddProjectile(new Rock(mPosition, target->getPositionVec() + (Vector2(2.0f, 0.0f) * mVelocity.getX()), mRenderer, mGame, 0));
	mReloadCount = ATTACK_RELOAD_TIME;
}

void Catapult::LoadAnimation()
{
	mTexture = TextureManager::getTexture(CATAPULT);
}
