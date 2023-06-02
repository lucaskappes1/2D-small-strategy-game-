#pragma once
#include "Button.h"
#include <string>

class UI
{
public:
	UI(class Game* game, SDL_Renderer* renderer);
	~UI();
	void Initialize();
	void Update();
	void Draw();
	void OnMouseClickEvent();
	void UpdateGoldText();
private:
	Game* mGame;
	SDL_Renderer* mRenderer;
	SDL_Surface* mTextSurface;
	SDL_Texture* mTextTexture;
	Mouse* mMouse;
	Button* mKnightButton;
	Button* mSpearKnightButton;
	Button* mAxeKnightButton;
	Button* mAcherButton;
	Button* mUpgradeArmorButton;
	Button* mUpgradeAttackButton;
	std::string mGold;
	TTF_Font* mFont;
	SDL_Color mTextColor = { 255, 0, 0 };
	SDL_Rect mTextRect = { 10, 10, 100, 30 };
};

