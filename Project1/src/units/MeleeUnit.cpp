#include "MeleeUnit.h"
#include "../Game.h"

MeleeUnit::MeleeUnit() : mPercentHPBar(1.0f)
{
		StartGenerator();	
}

void MeleeUnit::Update(float deltaTime)
{
	if (mHP <= 0)
	{
		eLastFrameState = eState;
		eState = State::DEATH;
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
		eState = State::WALKING;
	}
	else if (res != nullptr)
	{
		if ((res->getIsPlayer() && !mIsPlayer) || (mIsPlayer && !res->getIsPlayer()))
		{
			eLastFrameState = eState;
			eState = State::ATTACKING;
			Attack(res);
		}
	}
	else
	{
		eLastFrameState = eState;
		eState = State::IDLE;
	}
	mReloadCount--;
}

void MeleeUnit::Attack(GameObject* target)
{
	if (mReloadCount <= 0)
	{
		target->TakeDamage(mDamage);
		mReloadCount = ATTACK_RELOAD_TIME;
	}
}

void MeleeUnit::TakeDamage(int DMG)
{

	DMG = DMG - mArmor;
	if (mDistribution(mGenerator) % 100 <= mBlockChance)
	{
		return;
	}
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

void MeleeUnit::RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor)
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

void MeleeUnit::StartGenerator()
{
	std::random_device rd;
	mGenerator.seed(rd());
}

