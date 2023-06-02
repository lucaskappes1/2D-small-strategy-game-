#include "Castle.h"
#include "../Game.h"

Castle::Castle(SDL_Renderer* renderer, SDL_Texture* tex, int x, int y, Game* game, bool isPlayer)
{
	mGame = game;
	mIsPlayer = isPlayer;
	mRenderer = renderer;
	mTexture = tex;
	mX = x;
	mY = y;
	mDestR = { mX - 50, mY, 100, 100 };
	mHP = MAX_HP;
	mDamage = 5;
	mPercentHPBar = 1;
}

void Castle::Update(float deltaTime)
{
	if (mHP <= 0)
	{
		mGame->RemoveObject(this);
	}
	GameObject* res = mGame->RangedAttackDetection(this, 210);
	if (res != nullptr)
	{
		Attack(res);
	}
	mReloadCount--;
}

void Castle::Draw()
{
	SDL_RenderCopy(mRenderer, mTexture, NULL, &mDestR);
	RenderHPBar(mX, mY - 5, 28, 3, mPercentHPBar, { 0, 255, 0, 255 }, { 255, 0, 0, 255 });
}

void Castle::Attack(GameObject* target)
{
	if (mReloadCount <= 0)
	{
		target->TakeDamage(mDamage);
		mReloadCount = ATTACK_RELOAD_TIME;
	}
}

void Castle::TakeDamage(int DMG)
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

void Castle::RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor)
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
