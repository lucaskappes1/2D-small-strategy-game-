#include "HeavyInfantry.h"
#include "../Game.h"

HeavyInfantry::HeavyInfantry(SDL_Renderer* renderer, int x, int y, Game* game, bool isPlayer, bool isAdvancing) 
{
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
	mDamage = 20;
	mFrameCount = 0;
	LoadAnimation();
}

void HeavyInfantry::Update(float deltaTime)
{
	if (mHP <= 0)
	{
		eLastFrameState = eState;
		eState = DEATH;
		mGame->KillObject(this);
		return;
	}
	GameObject* res = mGame->CollisionDetection(this);
	if (res == nullptr && mAdvancing)
	{
		mPosition += mVelocity * deltaTime;
		mDestR.x = mPosition.getIntX();
		mCollisionR.x = mPosition.getIntX();
		eLastFrameState = eState;
		eState = WALKING;
	}
	else if (res != nullptr)
	{
		if ((res->getIsPlayer() && !mIsPlayer) || (mIsPlayer && !res->getIsPlayer()))
		{
			eLastFrameState = eState;
			eState = ATTACKING;
			Attack(res);
		}
	}
	else
	{
		eLastFrameState = eState;
		eState = IDLE;
	}
	mReloadCount--;
}

void HeavyInfantry::Draw()
{
	switch (eState)
	{
	case GameObject::ATTACKING:
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
	case GameObject::WALKING:
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
	case GameObject::IDLE:
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
	case GameObject::DEATH:
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

void HeavyInfantry::Attack(GameObject* target)
{
	if (mReloadCount <= 0)
	{
		target->TakeDamage(mDamage);
		mReloadCount = ATTACK_RELOAD_TIME;
	}
}

void HeavyInfantry::TakeDamage(int DMG)
{
	DMG = DMG - mArmor;
	if (DMG <= 0)
	{
		mHP -= 1;
	}
	else
	{
		mHP -= DMG;
	}
	mPercentHPBar = (float)mHP / (float)MAX_HP;
}

void HeavyInfantry::RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor)
{
	Percent = Percent > 1.f ? 1.f : Percent < 0.f ? 0.f : Percent;
	SDL_Color old;
	SDL_GetRenderDrawColor(mRenderer, &old.r, &old.g, &old.g, &old.a);
	SDL_Rect bgrect = { x, y, w, h };
	SDL_SetRenderDrawColor(mRenderer, BGColor.r, BGColor.g, BGColor.b, BGColor.a);
	SDL_RenderFillRect(mRenderer, &bgrect);
	SDL_SetRenderDrawColor(mRenderer, FGColor.r, FGColor.g, FGColor.b, FGColor.a);
	int pw = (int)((float)w * Percent);
	int px = x + (w - pw);
	SDL_Rect fgrect = { px, y, pw, h };
	SDL_RenderFillRect(mRenderer, &fgrect);
	SDL_SetRenderDrawColor(mRenderer, old.r, old.g, old.b, old.a);
}

void HeavyInfantry::LoadAnimation()
{
	mTexture = mGame->getTexture(HEAVY_INFANTRY);
}
