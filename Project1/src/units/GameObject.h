#pragma once
#include "SDL.h"

class GameObject
{
public:
	GameObject() {}
	~GameObject() {}
	virtual const int getGoldCost() const { return 0; }
	virtual void Draw() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Attack(GameObject* target) = 0;
	virtual void TakeDamage(int DMG) = 0;
	inline const int& getAttack() const { return mDamage; }
	inline const int& getArmor() const { return mArmor; }
	inline const int& getX() const { return mX; }
	inline const int& getY() const { return mY; }
	inline const bool& getIsPlayer() const { return mIsPlayer; }
	inline const SDL_Rect& getCollisionRect() const { return mCollisionR; }
	virtual void setArmor(int Armor) { mArmor = Armor; }
	virtual void setAttack(int Damage) { mDamage = Damage; }
	enum State { ATTACKING, WALKING, IDLE, DEATH } eState;
	void DisableCollision() { mCollisionR = { 5000, 5000, 0, 0 }; }
protected:
	int mX;
	int mY;
	int mHP;
	bool mIsPlayer;
	SDL_Rect mCollisionR;
	SDL_Rect mDestR;
	SDL_Renderer* mRenderer;
	SDL_Texture* mTexture;
	class Game* mGame;
	int mReloadCount;
	SDL_Rect mSrcR;
	int mArmor;
	int mDamage;
};

