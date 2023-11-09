#include "Building.h"
#include "../Game.h"

Building::Building(SDL_Renderer* renderer, int x, int y, Game* game, bool isPlayer)
{
	mGame = game;
	mIsPlayer = isPlayer;
	mRenderer = renderer;
	mPosition = { (float)x, (float)y };
	mPercentHPBar = 1;
}

void Building::Update(float deltaTime)
{
	if (mHP <= 0)
	{
		if (getIsPlayer())
		{
			mGame->DecreasePlayerBuildingCount();
		}
		else
		{
			mGame->DecreaseAIBuildingCount();
		}
		mGame->KillObject(this);
	}
	if (mReloadCount < 0)
	{
		GameObject* res = mGame->RangedAttackDetection(this, mRange);
		if (res != nullptr)
		{
			Attack(res);
			mProjectileCount++;
			if (mProjectileCount < mProjectileNumber)
			{
				mReloadCount = 6;
			}
			else
			{
				mProjectileCount = 0;
			}
		}
	}
	mReloadCount--;
}

void Building::TakeDamage(int DMG)
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

void Building::RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor)
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
