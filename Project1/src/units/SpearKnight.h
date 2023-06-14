#pragma once
#include "GameObject.h"

class SpearKnight : public GameObject
{
public:
	SpearKnight(SDL_Renderer* renderer, int x, int y, class Game* game, bool isPlayer, bool isAdvancing);
	void Update(float deltaTime);
	void Draw();
	void Attack(GameObject* target);
	virtual void TakeDamage(int DMG);
	inline static const int getStaticGoldCost() { return mGoldCost; }
	inline const int getGoldCost() const override { return mGoldCost; }
private:
	SDL_Texture* mTextureAttack;
	SDL_Texture* mIdleTexture;
	SDL_Texture* mDeathTexture;
	enum State eLastFrameState;
	void RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor);
	const int MAX_HP = 200;
	const int ATTACK_RELOAD_TIME = 45;
	float mPercentHPBar;
	const static int mGoldCost = 80;
	void LoadAnimation();
	int mFrameCount;
	bool mStateChanged;
};