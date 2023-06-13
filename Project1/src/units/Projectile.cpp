#include "Projectile.h"
#include "../Game.h"

Projectile::Projectile(const Vector2& position, const Vector2& destination, SDL_Renderer* renderer, class Game* game, bool isPlayer) :
	mDestination(destination),
	mRenderer(renderer),
	mGame(game)
{
}

void Projectile::CalculateVelocity(float offset)
{
	mDestination.setX(mDestination.getX() + offset);
	int dx = mDestination.getIntX() - mPosition.getIntX();
	float distanceX = dx * (dx >= 0 ? 1.0f : -1.0f);
	float time = distanceX / mVelocity.getX();
	float Voy = (mDestination.getIntY() - mPosition.getIntY() - (mAcceleration.getY() * time * time / 2)) / time;
	mVelocity = { mVelocity.getX() * (dx >= 0 ? 1.0f : -1.0f), Voy};
}
