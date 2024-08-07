#pragma once
#include "Projectile.h"
class Arrow :
    public Projectile
{
public:
    Arrow(const Vector2& position, GameObject* target, SDL_Renderer* renderer, class Game* game, int damage);
    void Update(float deltaTime);
    void Draw();
    static void LoadAnimation();
private:
    int mDamage;
    GameObject* mTarget;
    static SDL_Texture* mTexture;
};

