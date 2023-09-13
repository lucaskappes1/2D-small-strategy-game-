#include "Tower2.h"
#include "Arrow.h"
#include "../Game.h"

Tower2::Tower2(SDL_Renderer* renderer, int x, int y, Game* game, bool isPlayer) :
	Building(renderer, x, y, game, isPlayer)
{
	mCollisionR = { mPosition.getIntX() - 10, mPosition.getIntY(), 35, 100 };
	mDestR = { mPosition.getIntX() - 10, mPosition.getIntY(), 35, 100 };
	MAX_HP = 1100;
	mHP = MAX_HP;
	mDamage = 50;
	LoadAnimation();
}

void Tower2::Draw()
{
	SDL_RenderCopy(mRenderer, mTexture, NULL, &mDestR);
	RenderHPBar(mPosition.getIntX(), mPosition.getIntY() - 5, 28, 3, mPercentHPBar, { 0, 255, 0, 255 }, { 255, 0, 0, 255 });
}

void Tower2::Attack(GameObject* target)
{
	if (mReloadCount <= 0)
	{
		mGame->AddProjectile(new Arrow(mPosition, target, mRenderer, mGame, mDamage));
		mReloadCount = ATTACK_RELOAD_TIME;
	}
}

void Tower2::LoadAnimation()
{
	mTexture = mGame->getTexture(TOWER2);
}