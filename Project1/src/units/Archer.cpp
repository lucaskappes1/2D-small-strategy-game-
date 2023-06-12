#include "Archer.h"
#include "../Game.h"

Archer::Archer(SDL_Renderer* renderer, int x, int y, Game* game, bool isPlayer, bool isAdvancing)
{
	mAdvancing = isAdvancing;
	mRenderer = renderer;
	mX = x;
	mY = y;
	mCollisionR = { x, y, 32, 32 };
	mDestR = { x, y, 32, 32 };
	mSrcR = { 0, 0, 686, 1055 };
	mGame = game;
	mIsPlayer = isPlayer;
	mHP = MAX_HP;
	mReloadCount = 0;
	mPercentHPBar = 1.0f;
	mArmor = 4;
	mDamage = 18;
	mFrameCount = 0;
	mDeathAnimFrameCount = 0;
	LoadAnimation();
}

void Archer::Update(float deltaTime)
{
	if (mHP <= 0)
	{
		eLastFrameState = eState;
		eState = DEATH;
		mGame->KillObject(this);
		return;
	}
	GameObject* res = mGame->RangedAttackDetection(this, 210);
	GameObject* res2 = mGame->CollisionDetection(this);	
	if (res2 == nullptr && mAdvancing)
	{
		if (mIsPlayer)
		{
			mX = mX + 1;
		}
		else
		{
			mX = mX - 1;
		}
		mDestR.x = mX;
		mCollisionR.x = mX;
		eLastFrameState = eState;
		eState = WALKING;
	}
	else if (res != nullptr)
	{
		Attack(res);
		eLastFrameState = eState;
		eState = ATTACKING;
	}
	else
	{
		eLastFrameState = eState;
		eState = IDLE;
	}
	mReloadCount--;
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
		RenderHPBar(mX, mY - 5, 28, 3, mPercentHPBar, { 0, 255, 0, 255 }, { 255, 0, 0, 255 });
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
		RenderHPBar(mX, mY - 5, 28, 3, mPercentHPBar, { 0, 255, 0, 255 }, { 255, 0, 0, 255 });
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
		RenderHPBar(mX, mY - 5, 28, 3, mPercentHPBar, { 0, 255, 0, 255 }, { 255, 0, 0, 255 });
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
	if (mReloadCount <= 0)
	{
		target->TakeDamage(mDamage);
		mReloadCount = ATTACK_RELOAD_TIME;
	}
}

void Archer::TakeDamage(int DMG)
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

void Archer::RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor)
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

void Archer::LoadAnimation()
{
	mTexture = mGame->getTexture(ARCHER_WALK);
	mIdleTexture = mGame->getTexture(ARCHER_IDLE);
	mAttackTexture = mGame->getTexture(ARCHER_ATTACK);
	mDeathTexture = mGame->getTexture(ARCHER_DEATH);
}
