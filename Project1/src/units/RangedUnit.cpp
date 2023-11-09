#include "RangedUnit.h"
#include "../Game.h"

RangedUnit::RangedUnit()
{
	mPercentHPBar = 1.0f;
}

void RangedUnit::Update(float deltaTime)
{
	if (mHP <= 0)
	{
		eLastFrameState = eState;
		eState = State::DEATH;
		mGame->KillObject(this);
		return;
	}
	GameObject* res2 = mGame->CollisionDetection(this);
	if (mReloadCount < 0)
	{
		mTarget = mGame->RangedAttackDetection(this, mRange);
		if (mTarget != nullptr)
		{
			Attack(mTarget);
			mProjectileCount++;
			if (mProjectileCount < mProjectileNumber)
			{
				mReloadCount = 6;
			}
			else
			{
				mProjectileCount = 0;
			}
			eLastFrameState = eState;
			eState = State::ATTACKING;
		}
	}
	if (mTarget == nullptr && res2 == nullptr && mAdvancing)
	{
		mPosition += mVelocity * deltaTime;
		mDestR.x = mPosition.getIntX();
		mCollisionR.x = mPosition.getIntX();
		eLastFrameState = eState;
		eState = State::WALKING;
	}
	else if(mTarget == nullptr)
	{
		eLastFrameState = eState;
		eState = State::IDLE;
	}
	mReloadCount--;
}

void RangedUnit::TakeDamage(int DMG)
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

void RangedUnit::IncreaseRange(int range)
{
	mRange += range;
}

void RangedUnit::RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor)
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
