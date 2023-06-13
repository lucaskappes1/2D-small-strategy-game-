#pragma once
#include "GameObject.h"
#include "SDL.h"

class Projectile : public GameObject
{
public:
    Projectile(const Vector2& position, const Vector2& destination, SDL_Renderer* renderer, class Game* game);
    void Update(float deltaTime) override;
    void Draw();
    void LoadAnimation();
    virtual void Attack(GameObject* target) {}
    virtual void TakeDamage(int DMG) {}
private:
    Vector2 mAcceleration;
    Vector2 mDestination;
    void CalculateVelocity();
    SDL_Renderer* mRenderer;
    SDL_Texture* mTexture;
    SDL_Rect mDestR;
    class Game* mGame;
};

