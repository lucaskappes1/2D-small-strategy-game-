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
		eState = DEATH;
		mGame->KillObject(this);
		return;
	}
	GameObject* res = mGame->RangedAttackDetection(this, 210);
	GameObject* res2 = mGame->CollisionDetection(this);
	if (res2 == nullptr && mAdvancing)
	{
		mPosition += mVelocity * deltaTime;
		mDestR.x = mPosition.getIntX();
		mCollisionR.x = mPosition.getIntX();
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
