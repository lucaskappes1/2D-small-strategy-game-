#include "Castle.h"
#include "Arrow.h"
#include "../Game.h"

Castle::Castle(SDL_Renderer* renderer, int x, int y, Game* game, bool isPlayer) :
	Building(renderer, x, y, game, isPlayer)
{
	mCollisionR = { mPosition.getIntX() - 50, mPosition.getIntY(), 100, 100};
	mDestR = { mPosition.getIntX() - 50, mPosition.getIntY(), 100, 100 };
	MAX_HP = 1500;
	mHP = MAX_HP;
	mDamage = 50;
	mArmor = 20;
	LoadAnimation();
	mRange = 300;
	ATTACK_RELOAD_TIME = 50;
}

void Castle::Draw()
{
	SDL_RenderCopy(mRenderer, mTexture, NULL, &mDestR);
	RenderHPBar(mPosition.getIntX(), mPosition.getIntY() - 5, 28, 3, mPercentHPBar, { 0, 255, 0, 255 }, { 255, 0, 0, 255 });
}

void Castle::Attack(GameObject* target)
{
	mGame->AddProjectile(new Arrow(mPosition, target, mRenderer, mGame, mDamage));
	mReloadCount = ATTACK_RELOAD_TIME;
}

void Castle::OnDeathAction()
{
	mGame->GameOver(this);
}

void Castle::LoadAnimation()
{
	mTexture = mGame->getTexture(CASTLE);
}
