#include "Archer.h"
#include "../Game.h"

Archer::Archer(SDL_Renderer* renderer, int x, int y, Game* game, bool isPlayer)
{
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
	LoadAnimation();
}

void Archer::Update(float deltaTime)
{
	if (mHP <= 0)
	{
		mGame->RemoveObject(this);
	}
	GameObject* res = mGame->RangedAttackDetection(this, 210);
	GameObject* res2 = mGame->CollisionDetection(this);	
	if (res == nullptr && res2 == nullptr)
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
	if (res != nullptr)
	{
		Attack(res);
		eLastFrameState = eState;
		eState = ATTACKING;
	}
	mReloadCount--;
}

void Archer::Draw()
{
	if (eState == ATTACKING)
	{
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

	}

	if (eState == WALKING)
	{
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
	}

	float temp = mHP / MAX_HP;
	RenderHPBar(mX, mY - 5, 28, 3, mPercentHPBar, { 0, 255, 0, 255 }, { 255, 0, 0, 255 });
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

void Archer::StaticLoadAnimation()
{
	
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
	mTexture = mGame->getTexture( ARCHER_WALK);
	mAttackTexture = mGame->getTexture(ARCHER_ATTACK);
}
