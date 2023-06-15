#include "Arrow.h"
#include "../Game.h"

Arrow::Arrow(const Vector2& position, GameObject* target, SDL_Renderer* renderer, Game* game, int damage) : 
	Projectile(position, target->getPositionVec(), renderer, game),
	mDamage(damage),
	mTarget(target)
{
	if (mDestination.getY() < mPosition.getY())
	{
		mDestination.setY(mPosition.getY() + 3.0f);
	}
	mVelocity = { 600.0f, 0.0f };
	mAcceleration = { 0.0f, 900.0f };
	mCollisionR = { -100, -100, 0, 0 };
	mDestR = { mPosition.getIntX(), mPosition.getIntY(), 2, 30 };
	CalculateVelocity(0.0f);
	LoadAnimation();
}

void Arrow::Update(float deltaTime)
{
	mPosition += mVelocity * deltaTime;
	mVelocity += mAcceleration * deltaTime;
	mDestR.x = mPosition.getIntX();
	mDestR.y = mPosition.getIntY();
	if (mPosition.getIntY() >= mDestination.getIntY())
	{
		mTarget->TakeDamage(mDamage);
		mGame->KillObject(this);
	}
}

void Arrow::Draw()
{
	Vector2 adjustedVector(mVelocity.getX(), -mVelocity.getY());
	float angle = std::atan2(adjustedVector.getY(), adjustedVector.getX()) * 180 / M_PI;
	angle = 90 - angle;
	if (angle < 0)
		angle += 360;
	mDestR.x = mPosition.getIntX();
	mDestR.y = mPosition.getIntY();
	SDL_RenderCopyEx(mRenderer, mTexture, nullptr, &mDestR, angle, nullptr, SDL_FLIP_NONE);
}

void Arrow::LoadAnimation()
{
	mTexture = mGame->getTexture(ARROW);
}
