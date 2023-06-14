#pragma once
#include "GameObject.h"

class Castle :  public GameObject
{
public:
	Castle(SDL_Renderer* renderer, SDL_Texture* tex, int x, int y, class Game* game, bool isPlayer);
	void Update(float deltaTime);
	void Draw();
	void Attack(GameObject* target);
	virtual void TakeDamage(int DMG);
private:
	const int MAX_HP = 1000;
	const int ATTACK_RELOAD_TIME = 8;
	const int mArmor = 20;
	void RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor);
	float mPercentHPBar;
};