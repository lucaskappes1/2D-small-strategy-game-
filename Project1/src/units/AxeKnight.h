#pragma once
#include "GameObject.h"
#include <vector>

class AxeKnight :  public GameObject
{
public:
	AxeKnight(SDL_Renderer* renderer, int x, int y, class Game* game, bool isPlayer, bool isAdvancing);
	void Update(float deltaTime);
	void Draw();
	void Attack(GameObject* target);
	virtual void TakeDamage(int DMG);
	inline static const int getStaticGoldCost() { return mGoldCost; }
	inline const int getGoldCost() const override { return mGoldCost; }
	
private:
	enum State eLastFrameState;
	std::vector<SDL_Texture*> mWalkingAnimVec;
	std::vector<SDL_Texture*> mAttackingAnimVec;
	std::vector<SDL_Texture*> mDeathAnimVec;
	SDL_Texture* mIdleTexture;
	void RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor);
	float mPercentHPBar;
	const int MAX_HP = 160;
	const int ATTACK_RELOAD_TIME = 55;
	const static int mGoldCost = 60;
	int mCurrentFrame;
	void LoadAnimation();
	int mFrameCount;
};