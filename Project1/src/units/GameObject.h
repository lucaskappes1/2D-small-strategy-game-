#pragma once
#include "SDL.h"
#include "../Vector2.h"

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
	inline const int& getX() const { return mPosition.getIntX(); }
	inline const int& getY() const { return mPosition.getIntY(); }
	inline const Vector2& getPositionVec() const { return mPosition; }
	inline const bool& getIsPlayer() const { return mIsPlayer; }
	inline const SDL_Rect& getCollisionRect() const { return mCollisionR; }
	virtual void setArmor(int Armor) { mArmor = Armor; }
	virtual void setAttack(int Damage) { mDamage = Damage; }
	enum State { ATTACKING, WALKING, IDLE, DEATH } eState;
	void ChangeOrder() { mAdvancing = !mAdvancing; }
	void setOrder(bool isAdvancing) { mAdvancing = isAdvancing; }
protected:
	Vector2 mPosition;
	Vector2 mVelocity;
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
	bool mAdvancing;
};

