#include "UI.h"
#include "../Game.h"


UI::UI(Game* game, SDL_Renderer* renderer)
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
}

void UI::Initialize()
{
	mFont = TTF_OpenFont("assets/stocky.ttf", 24);
	mKnightButton = new Button(mGame->getTexture(KNIGHT_BUTTON), mRenderer, mMouse, 50, 50, {130, 50, 106, 186}, mFont);
	mSpearKnightButton = new Button(mGame->getTexture(SPEARMAN_BUTTON), mRenderer, mMouse, 100, 50, {0, 0, 172, 177}, mFont);
	mAxeKnightButton = new Button(mGame->getTexture(GREEK_BUTTON), mRenderer, mMouse, 150, 50, {0, 0, 362, 586}, mFont);
	mAcherButton = new Button(mGame->getTexture(ARCHER_BUTTON), mRenderer, mMouse, 200, 50, {0, 0, 303, 525}, mFont);
	mUpgradeArmorButton = new Button(mGame->getTexture(ARMOR_UPGRADE_BUTTON), mRenderer, mMouse, 50, 100, { 0, 0, 64, 64 }, mFont);
	mUpgradeAttackButton = new Button(mGame->getTexture(ATTACK_UPGRADE_BUTTON), mRenderer, mMouse, 100, 100, { 0, 0, 64, 64 }, mFont);
	mKnightButton->addTooltip("Cost: 35 gold\nStrong all around infantry");
	mSpearKnightButton->addTooltip("Cost: 80 gold\nStronger than Knight, but slower");
	mAxeKnightButton->addTooltip("Cost: 60 gold\nVery weak, but does a lot of damage");
	mAcherButton->addTooltip("Cost: 55 gold\nVery weak, but attacks from distance");
	mUpgradeArmorButton->addTooltip("Cost: 500 gold\nIncrease armor of next units by 1");
	mUpgradeAttackButton->addTooltip("Cost: 500 gold\nIncrease attack of next units by 1");
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
	mUpgradeArmorButton->Update();
	mUpgradeAttackButton->Update();
	mMouse->Update();
}

void UI::Draw()
{
	mKnightButton->Draw();
	mSpearKnightButton->Draw();
	mAxeKnightButton->Draw();
	mAcherButton->Draw();
	mUpgradeArmorButton->Draw();
	mUpgradeAttackButton->Draw();
	SDL_RenderCopy(mRenderer, mTextTexture, NULL, &mTextRect);
	mMouse->Draw();
}

void UI::OnMouseClickEvent()
{
	if (mKnightButton->IsSelected())
	{
		mGame->CreateKnight(true);
	}
	else if (mSpearKnightButton->IsSelected())
	{
		mGame->CreateSpearKnight(true);
	}
	else if (mAxeKnightButton->IsSelected())
	{
		mGame->CreateAxeKnight(true);
	}
	else if (mAcherButton->IsSelected())
	{
		mGame->CreateArcher(true);
	}
	else if (mUpgradeArmorButton->IsSelected())
	{
		mGame->PlayerUpgradeArmor();
	}
	else if (mUpgradeAttackButton->IsSelected())
	{
		mGame->PlayerUpgradeAttack();
	}
}

void UI::UpdateGoldText()
{
	mGold = "Gold: " + std::to_string(mGame->getPlayerGold());
	SDL_FreeSurface(mTextSurface);
	SDL_DestroyTexture(mTextTexture);
	mTextSurface = TTF_RenderText_Solid(mFont, mGold.c_str(), mTextColor);
	mTextTexture = SDL_CreateTextureFromSurface(mRenderer, mTextSurface);
}
