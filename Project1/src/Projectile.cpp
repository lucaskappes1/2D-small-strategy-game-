#include "Projectile.h"
#include "Game.h"
#include "Constants.h"

Projectile::Projectile(const Vector2& position, const Vector2& velocity, const Vector2& acceleration,
	SDL_Renderer* renderer, class Game* game) :
	mPosition(position),
	mVelocity(velocity),
	mAcceleration(acceleration),
	mRenderer(renderer),
	mGame(game)
{
	mDestR = { mPosition.getIntX(), mPosition.getIntY(), 32, 32 };
	LoadAnimation();
}

void Projectile::Update(float deltaTime)
{
	mVelocity += mAcceleration * deltaTime;
	mPosition += mVelocity * deltaTime;
	mDestR.x = mPosition.getIntX();
	mDestR.y = mPosition.getIntY();
}

void Projectile::Draw()
{
	SDL_RenderCopy(mRenderer, mTexture, NULL, &mDestR);
}

void Projectile::LoadAnimation()
{
	mTexture = mGame->getTexture(ROCK);
}
