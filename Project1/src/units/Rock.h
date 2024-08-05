#pragma once
#include "Projectile.h"

class Rock : public Projectile
{
public:
	Rock(const Vector2& position, const Vector2& destination, SDL_Renderer* renderer, class Game* game, int upgradeLevel);
    Rock(const Vector2& position, const Vector2& destination, SDL_Renderer* renderer, class Game* game, float offset, float velocityOffset);
    void Update(float deltaTime);
    void Draw();
    static void LoadAnimation();
    virtual void Attack(GameObject* target) {}
    virtual void TakeDamage(int DMG) {}
private:
    static SDL_Texture* mTexture;
};

