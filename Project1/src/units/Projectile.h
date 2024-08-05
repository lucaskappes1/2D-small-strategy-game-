#pragma once
#include "GameObject.h"
#include "SDL.h"

class Projectile : public GameObject
{
public:
    Projectile(const Vector2& position, const Vector2& destination, SDL_Renderer* renderer, class Game* game);
    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;
    virtual void Attack(GameObject* target) {}
    virtual void TakeDamage(int DMG) {}
    virtual void OnDeathAction() {}
protected:
    Vector2 mAcceleration;
    Vector2 mDestination;
    void CalculateVelocity(float offset);
    SDL_Renderer* mRenderer;
    SDL_Rect mDestR;
    class Game* mGame;
};

