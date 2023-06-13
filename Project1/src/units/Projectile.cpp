#include "Projectile.h"
#include "../Game.h"

Projectile::Projectile(const Vector2& position, const Vector2& destination, SDL_Renderer* renderer, class Game* game) :
	mDestination(destination),
	mRenderer(renderer),
	mGame(game)
{
	mAcceleration = { 0.0f, 30.0f };
	mCollisionR = { 0, 0, 0, 0 };
	mPosition = position;
	mDestR = { mPosition.getIntX(), mPosition.getIntY(), 16, 16 };
	LoadAnimation();
	CalculateVelocity();
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

void Projectile::CalculateVelocity()
{
	Vector2 dtemp = mDestination - mPosition;
	int d = abs(dtemp.getIntX());
	float time = (float) d / 300.0f;
	float temp = (pow(time, 2) * 30.0f) / 2.0f;
	float Voy = (-temp - 58) / time;
	mVelocity = { 300, Voy };
}
