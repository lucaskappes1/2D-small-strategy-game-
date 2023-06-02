#include "Archer.h"
#include "../Game.h"

Archer::Archer(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, Game* game, bool isPlayer)
{
	mRenderer = renderer;
	mTexture = texture;
	mX = x;
	mY = y;
	mDestR = { x, y, 32, 32 };
	mSrcR = { 20, 50, 88, 78 };
	mGame = game;
	mIsPlayer = isPlayer;
	mHP = MAX_HP;
	mReloadCount = 0;
	mPercentHPBar = 1.0f;
	mArmor = 0;
	mDamage = 20;
}

void Archer::Update(float deltaTime)
{
	if (mHP <= 0)
	{
		mGame->RemoveObject(this);
	}
	GameObject* res = mGame->CollisionDetection(this);
	if (res == nullptr)
	{
		if (mIsPlayer)
		{
			mX = mX + 1;
			mDestR.x = mX;
		}
		else
		{
			mX = mX - 1;
			mDestR.x = mX;
		}
	}
	res = mGame->RangedAttackDetection(this, 210);
	if (res != nullptr)
	{
		Attack(res);
	}
	mReloadCount--;
}

void Archer::Draw()
{
	SDL_RenderCopy(mRenderer, mTexture, &mSrcR, &mDestR);
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