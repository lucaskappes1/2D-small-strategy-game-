#pragma once
#include "GameObject.h"
#include <vector>

class Knight :  public GameObject
{
public:
	Knight(SDL_Renderer* renderer, int x, int y, class Game* game, bool isPlayer);
	void Update(float deltaTime);
	void Draw();
	void Attack(GameObject* target);
	virtual void TakeDamage(int DMG);
	inline static const int getStaticGoldCost() { return mGoldCost; }
	inline const int getGoldCost() const override { return mGoldCost; }
	void static StaticLoadAnimation(); //this will load the animation into texture map
private:
	enum State{ATTACKING, WALKING} eState;
	enum State eLastFrameState;
	float mPercentHPBar;
	void RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor);
	const int MAX_HP = 120;
	const int ATTACK_RELOAD_TIME = 20;
	const static int mGoldCost = 35;
	int mFrameCount;
	int mCurrentFrame;
	std::vector<SDL_Texture*> mWalkingAnimVec;
	std::vector<SDL_Texture*> mAttackingAnimVec;
	void LoadAnimation();
};
