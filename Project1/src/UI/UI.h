#pragma once
#include "Button.h"
#include <string>
#include <unordered_map>
#include <functional>

class UI
{
public:
	UI(class Game* game, SDL_Renderer* renderer, class Player* Player, class Stage* stage);
	~UI();
	void Initialize();
	void Update();
	void Draw();
	void OnMouseClickEvent();
	void UpdateGoldText();
	void VictoryScreen();
private:
	void HideGameplayButtons();
	void ShowGameplayButtons();
	void ShowIntermissionButtons();
	void HideIntermissionButtons();
	void ShowSpecialUpgradeScreen();
	void HideSpecialUpgradeScreen();

	
	bool mStoneButtonClicked;
	class Player* mPlayer;
	class Stage* mStage;
	Game* mGame;
	SDL_Renderer* mRenderer;
	SDL_Surface* mTextSurface;
	SDL_Texture* mTextTexture;
	Mouse* mMouse;
	Button* mKnightButton;
	Button* mSpearKnightButton;
	Button* mAxeKnightButton;
	Button* mAcherButton;
	Button* mHeavyInfantryButton;
	Button* mUpgradeArmorButton;
	Button* mUpgradeAttackButton;
	Button* mUpgradeRockButton;
	Button* mStartGameButton;
	Button* mPauseButton;
	Button* mContinueButton;
	Button* mChangeOrderButton;
	Button* mRockButton;
	Button* mTower1Button;
	Button* mTower2Button;
	Button* mStage1Button;
	Button* mStage2Button;
	Button* mStage3Button;
	Button* mStage4Button;
	Button* mSpecialUpgradeButton;
	Button* mArcherBonusButton;
	Button* mMeleeBonusButton;
	Button* mTowerBonusButton;

	std::unordered_map<Button*, std::function<void()>> mButtonMap;
	std::string mGold;
	TTF_Font* mFont;
	SDL_Color mTextColor = { 255, 0, 0 };
	SDL_Rect mTextRect = { 10, 10, 100, 30 };
};

