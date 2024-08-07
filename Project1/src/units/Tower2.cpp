#include "Tower2.h"
#include "Arrow.h"
#include "../Game.h"
#include "../TextureManager.h"

SDL_Texture* Tower2::mTexture = nullptr;

Tower2::Tower2(SDL_Renderer* renderer, int x, int y, Game* game, bool isPlayer) :
	Building(renderer, x, y, game, isPlayer)
{
	mCollisionR = { mPosition.getIntX() - 10, mPosition.getIntY(), 35, 100 };
	mDestR = { mPosition.getIntX() - 10, mPosition.getIntY(), 35, 100 };
	MAX_HP = 1100;
	mHP = MAX_HP;
	mDamage = 50;
	LoadAnimation();
	mArmor = 18;
	mRange = 280;
	mProjectileNumber = 1;
	ATTACK_RELOAD_TIME = 110;
}

void Tower2::Draw()
{
	SDL_RenderCopy(mRenderer, mTexture, NULL, &mDestR);
	RenderHPBar(mPosition.getIntX(), mPosition.getIntY() - 5, 28, 3, mPercentHPBar, { 0, 255, 0, 255 }, { 255, 0, 0, 255 });
}

void Tower2::Attack(GameObject* target)
{
	mGame->AddProjectile(new Arrow(mPosition, target, mRenderer, mGame, mDamage));
	mReloadCount = ATTACK_RELOAD_TIME;
}

void Tower2::LoadAnimation()
{
	mTexture = TextureManager::getTexture(TOWER2);
}