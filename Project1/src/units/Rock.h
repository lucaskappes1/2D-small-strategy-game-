#pragma once
#include "Projectile.h"

class Rock : public Projectile
{
public:
	Rock(const Vector2& position, const Vector2& destination, SDL_Renderer* renderer, class Game* game, bool isPlayer, int upgradeLevel);
    Rock(const Vector2& position, const Vector2& destination, SDL_Renderer* renderer, class Game* game, bool isPlayer, float offset);
    void Update(float deltaTime);
    void Draw();
    void LoadAnimation();
    virtual void Attack(GameObject* target) {}
    virtual void TakeDamage(int DMG) {}

private:
};

