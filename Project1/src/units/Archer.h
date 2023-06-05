#pragma once
#include "GameObject.h"
#include <vector>

class Archer :
    public GameObject
{
public:
	Archer(SDL_Renderer* renderer, int x, int y, class Game* game, bool isPlayer);
	void Update(float deltaTime);
	void Draw();
	void Attack(GameObject* target);
	virtual void TakeDamage(int DMG);
	inline const static int getStaticGoldCost() { return mGoldCost; }
	inline const int getGoldCost() const override { return mGoldCost; }
private:
	enum State{ATTACKING, WALKING} eState;
	enum State eLastFrameState;;
	void RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor);
	float mPercentHPBar;
	const int MAX_HP = 80;
	const int ATTACK_RELOAD_TIME = 40;
	const static int mGoldCost = 55;
	void LoadAnimation();
	SDL_Texture* mAttackTexture;
	int mFrameCount;
};

