#include "Rock.h"
#include "../Game.h"

Rock::Rock(const Vector2& position, const Vector2& destination, SDL_Renderer* renderer, Game* game, bool isPlayer, int upgradeLevel) : 
	Projectile(position, destination, renderer, game, isPlayer)
{
	mVelocity = { 180.0f, 0.0f };
	mAcceleration = { 0.0f, 50.0f };
	mCollisionR = { -1000000, -100, 0, 0 };
	mPosition = position;
	mDestR = { mPosition.getIntX(), mPosition.getIntY(), 12, 12 };
	mIsPlayer = isPlayer;
	if (upgradeLevel == 1)
	{
		mGame->ThrowRock(new Rock(position, destination, mRenderer, mGame, isPlayer, -60.0f));
		mGame->ThrowRock(new Rock(position, destination, mRenderer, mGame, isPlayer, 60.0f));
	}
	if (upgradeLevel == 2)
	{
		mGame->ThrowRock(new Rock(position, destination, mRenderer, mGame, isPlayer, -60.0f));
		mGame->ThrowRock(new Rock(position, destination, mRenderer, mGame, isPlayer, 60.0f));
		mGame->ThrowRock(new Rock(position, destination, mRenderer, mGame, isPlayer, -120.0f));
		mGame->ThrowRock(new Rock(position, destination, mRenderer, mGame, isPlayer, 120.0f));
	}
	LoadAnimation();
	CalculateVelocity(0.0f);
}

Rock::Rock(const Vector2& position, const Vector2& destination, SDL_Renderer* renderer, Game* game, bool isPlayer, float offset) : 
	Projectile(position, destination, renderer, game, isPlayer)
{
	mVelocity = { 180.0f, 0.0f };
	mAcceleration = { 0.0f, 50.0f };
	mCollisionR = { -10000, -100, 0, 0 };
	mPosition = position;
	mDestR = { mPosition.getIntX(), mPosition.getIntY(), 12, 12 };
	mIsPlayer = isPlayer;

	LoadAnimation();
	CalculateVelocity(offset);
}

void Rock::Update(float deltaTime)
{
	mVelocity += mAcceleration * deltaTime;
	mPosition += mVelocity * deltaTime;
	mDestR.x = mPosition.getIntX();
	mDestR.y = mPosition.getIntY();
	if (mPosition.getIntX() >= mDestination.getIntX() && mIsPlayer)
	{
		mGame->SplashDamage(150, mPosition.getIntX(), 100);
		mGame->KillObject(this);
	}
	else if (mPosition.getIntX() <= mDestination.getIntX() && !mIsPlayer)
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