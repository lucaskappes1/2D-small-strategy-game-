#include "UI.h"
#include "../Game.h"
#include "../Player.h"


UI::UI(Game* game, SDL_Renderer* renderer, Player* Player) : mPlayer(Player), mStoneButtonClicked(false)
{
	mGame = game;
	mRenderer = renderer;
	mMouse = new Mouse(mGame->getTexture(MOUSE_BUTTON), mRenderer);
}

UI::~UI()
{
	delete mKnightButton;
	delete mSpearKnightButton;
	delete mAxeKnightButton;
	delete mAcherButton;
	delete mMouse;
	delete mUpgradeArmorButton;
	delete mUpgradeAttackButton;
	delete mStartGameButton;
	delete mPauseButton;
	delete mContinueButton;
	delete mChangeOrderButton;
	delete mUpgradeRockButton;
}

void UI::Initialize()
{
	mFont = TTF_OpenFont("assets/stocky.ttf", 24);
	mStartGameButton = new Button(mRenderer, mMouse, 400, 400, mFont, "Start");
	mPauseButton = new Button(mRenderer, mMouse, 500, 100, mFont, "Pause");
	mContinueButton = new Button(mRenderer, mMouse, 500, 100, mFont, "Continue");
	mStartGameButton->Show();
	mKnightButton = new Button(mGame->getTexture(KNIGHT_BUTTON), mRenderer, mMouse, 50, 50, {130, 50, 106, 186}, mFont);
	mSpearKnightButton = new Button(mGame->getTexture(SPEARMAN_BUTTON), mRenderer, mMouse, 100, 50, {0, 0, 172, 177}, mFont);
	mAxeKnightButton = new Button(mGame->getTexture(GREEK_BUTTON), mRenderer, mMouse, 150, 50, {0, 0, 362, 586}, mFont);
	mAcherButton = new Button(mGame->getTexture(ARCHER_BUTTON), mRenderer, mMouse, 200, 50, {0, 0, 303, 525}, mFont);
	mHeavyInfantryButton = new Button(mGame->getTexture(HEAVY_INFANTRY_BUTTON), mRenderer, mMouse, 250, 50, { 0, 0, 65, 63 }, mFont);
	mRockButton = new Button(mGame->getTexture(ROCK), mRenderer, mMouse, 300, 50, { 0, 0, 64, 64 }, mFont);
	mUpgradeArmorButton = new Button(mGame->getTexture(ARMOR_UPGRADE_BUTTON), mRenderer, mMouse, 50, 100, { 0, 0, 64, 64 }, mFont);
	mUpgradeAttackButton = new Button(mGame->getTexture(ATTACK_UPGRADE_BUTTON), mRenderer, mMouse, 100, 100, { 0, 0, 64, 64 }, mFont);
	mUpgradeRockButton = new Button(mGame->getTexture(ROCK_UPGRADE_BUTTON), mRenderer, mMouse, 150, 100, { 0, 0, 128, 128 }, mFont);
	mChangeOrderButton = new Button(mGame->getTexture(CHANGE_ORDER_BUTTON), mRenderer, mMouse, 200, 100, { 0, 0, 64, 64 }, mFont);
	HideGameplayButtons();
	mContinueButton->Hide();
	mPauseButton->Hide();
	mKnightButton->addTooltip("Cost: 35 gold\nStrong all around infantry");
	mSpearKnightButton->addTooltip("Cost: 80 gold\nStronger than Knight, but slower");
	mAxeKnightButton->addTooltip("Cost: 60 gold\nVery weak, but does a lot of damage");
	mAcherButton->addTooltip("Cost: 55 gold\nVery weak, but attacks from distance");
	mHeavyInfantryButton->addTooltip("Cost 380 gold. Very Strong");
	mUpgradeArmorButton->addTooltip("Cost: 500 gold\nIncrease armor of next units by 1");
	mUpgradeAttackButton->addTooltip("Cost: 500 gold\nIncrease attack of next units by 1");
	mChangeOrderButton->addTooltip("Click to Change Order between advance or stand still");
	mRockButton->addTooltip("Cost: 150 gold. Throw a Rock which does splash damage on next mouse click");
	mUpgradeRockButton->addTooltip("Cost 2000 gold. Adds 2 Rocks when throwing");
	mGold = "Gold: 100";
	mTextSurface = TTF_RenderText_Solid(mFont, mGold.c_str(), mTextColor);
	mTextTexture = SDL_CreateTextureFromSurface(mRenderer, mTextSurface);
}

void UI::Update()
{
	mKnightButton->Update();
	mSpearKnightButton->Update();
	mAxeKnightButton->Update();
	mAcherButton->Update();
	mHeavyInfantryButton->Update();
	mUpgradeArmorButton->Update();
	mUpgradeAttackButton->Update();
	mStartGameButton->Update();
	mPauseButton->Update();
	mContinueButton->Update();
	mChangeOrderButton->Update();
	mRockButton->Update();
	mUpgradeRockButton->Update();
	mMouse->Update();
}

void UI::Draw()
{
	mKnightButton->Draw();
	mSpearKnightButton->Draw();
	mAxeKnightButton->Draw();
	mAcherButton->Draw();
	mHeavyInfantryButton->Draw();
	mUpgradeArmorButton->Draw();
	mUpgradeAttackButton->Draw();
	mStartGameButton->Draw();
	mPauseButton->Draw();
	mContinueButton->Draw();
	mChangeOrderButton->Draw();
	mRockButton->Draw();
	mUpgradeRockButton->Draw();
	SDL_RenderCopy(mRenderer, mTextTexture, NULL, &mTextRect);
	mMouse->Draw();
}

void UI::OnMouseClickEvent()
{
	if (mStoneButtonClicked)
	{
		mPlayer->LaunchRock(mMouse->getCollisionRect().x);
		mStoneButtonClicked = false;
	}
	else if (mKnightButton->IsSelected())
	{
		mPlayer->CreateKnight();
	}
	else if (mSpearKnightButton->IsSelected())
	{
		mPlayer->CreateSpearKnight();
	}
	else if (mAxeKnightButton->IsSelected())
	{
		mPlayer->CreateAxeKnight();
	}
	else if (mAcherButton->IsSelected())
	{
		mPlayer->CreateArcher();
	}
	else if (mHeavyInfantryButton->IsSelected())
	{
		mPlayer->CreateHeavyInfantry();
	}
	else if (mUpgradeArmorButton->IsSelected())
	{
		mPlayer->UpgradeArmor();
	}
	else if (mUpgradeAttackButton->IsSelected())
	{
		mPlayer->UpgradeAttack();
	}
	else if (mStartGameButton->IsSelected())
	{
		mGame->StartGame();
		mStartGameButton->Hide();
	}
	else if (mPauseButton->IsSelected())
	{
		mGame->Pause();
		HideGameplayButtons();
		mContinueButton->Show();
		mPauseButton->Hide();
	}
	else if (mContinueButton->IsSelected())
	{
		mGame->Continue();
		ShowGameplayButtons();
		mPauseButton->Show();
		mContinueButton->Hide();
	}
	else if (mChangeOrderButton->IsSelected())
	{
		mPlayer->ChangeOrder();
	}
	else if (mRockButton->IsSelected())
	{
		mStoneButtonClicked = true;
	}
	else if (mUpgradeRockButton->IsSelected())
	{
		mPlayer->UpgradeRock();
	}
}

void UI::UpdateGoldText()
{
	mGold = "Gold: " + std::to_string(mPlayer->getGold());
	SDL_FreeSurface(mTextSurface);
	SDL_DestroyTexture(mTextTexture);
	mTextSurface = TTF_RenderText_Solid(mFont, mGold.c_str(), mTextColor);
	mTextTexture = SDL_CreateTextureFromSurface(mRenderer, mTextSurface);
}

void UI::StartGame()
{
	ShowGameplayButtons();
	mPauseButton->Show();
}

void UI::HideGameplayButtons()
{
	mKnightButton->Hide();
	mSpearKnightButton->Hide();
	mAxeKnightButton->Hide();
	mAcherButton->Hide();
	mHeavyInfantryButton->Hide();
	mUpgradeArmorButton->Hide();
	mUpgradeAttackButton->Hide();
	mChangeOrderButton->Hide();
	mRockButton->Hide();
	mUpgradeRockButton->Hide();
}

void UI::ShowGameplayButtons()
{
	mKnightButton->Show();
	mSpearKnightButton->Show();
	mAxeKnightButton->Show();
	mAcherButton->Show();
	mHeavyInfantryButton->Show();
	mUpgradeArmorButton->Show();
	mUpgradeAttackButton->Show();
	mChangeOrderButton->Show();
	mRockButton->Show();
	mUpgradeRockButton->Show();
}
