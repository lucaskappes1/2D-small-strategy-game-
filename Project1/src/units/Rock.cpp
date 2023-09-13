#include "Rock.h"
#include "../Game.h"

Rock::Rock(const Vector2& position, const Vector2& destination, SDL_Renderer* renderer, Game* game, int upgradeLevel) :
	Projectile(position, destination, renderer, game)
{
	mVelocity = { 180.0f, 0.0f };
	mAcceleration = { 0.0f, 50.0f };
	mDestR = { mPosition.getIntX(), mPosition.getIntY(), 12, 12 };
	if (upgradeLevel == 1)
	{
		mGame->AddProjectile(new Rock(position, destination, mRenderer, mGame, -60.0f));
		mGame->AddProjectile(new Rock(position, destination, mRenderer, mGame, 60.0f));
	}
	if (upgradeLevel == 2)
	{
		mGame->AddProjectile(new Rock(position, destination, mRenderer, mGame, -60.0f));
		mGame->AddProjectile(new Rock(position, destination, mRenderer, mGame, 60.0f));
		mGame->AddProjectile(new Rock(position, destination, mRenderer, mGame, -120.0f));
		mGame->AddProjectile(new Rock(position, destination, mRenderer, mGame, 120.0f));
	}
	LoadAnimation();
	CalculateVelocity(0.0f);
}

Rock::Rock(const Vector2& position, const Vector2& destination, SDL_Renderer* renderer, Game* game, float offset, float velocityOffset) : 
	Projectile(position, destination, renderer, game)
{
	mVelocity = { 180.0f + velocityOffset, 0.0f };
	mAcceleration = { 0.0f, 50.0f };
	mPosition = position;
	mDestR = { mPosition.getIntX(), mPosition.getIntY(), 12, 12 };
	LoadAnimation();
	CalculateVelocity(offset);
}

void Rock::Update(float deltaTime)
{
	mVelocity += mAcceleration * deltaTime;
	mPosition += mVelocity * deltaTime;
	mDestR.x = mPosition.getIntX();
	mDestR.y = mPosition.getIntY();
	if (mPosition.getIntY() >= mDestination.getIntY())
	{
		mGame->SplashDamage(150, mPosition.getIntX(), 100);
		mGame->KillObject(this);
	}
}

void Rock::Draw()
{
	SDL_RenderCopy(mRenderer, mTexture, NULL, &mDestR);
}

void Rock::LoadAnimation()
{
	mTexture = mGame->getTexture(ROCK);
}