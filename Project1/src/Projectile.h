#pragma once
#include "Vector2.h"
#include "SDL.h"

class Projectile
{
public:
    Projectile(const Vector2& position, const Vector2& velocity, const Vector2& acceleration,
        SDL_Renderer* renderer, class Game* game);
    void Update(float deltaTime);
    void Draw();
    void LoadAnimation();
private:
    Vector2 mPosition;
    Vector2 mVelocity;
    Vector2 mAcceleration;
    SDL_Renderer* mRenderer;
    SDL_Texture* mTexture;
    SDL_Rect mDestR;
    class Game* mGame;
};

