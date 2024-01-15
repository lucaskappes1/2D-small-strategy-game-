#include "UI.h"
#include "../Game.h"
#include "../Player.h"
#include "../level/Stage.h"


UI::UI(Game* game, SDL_Renderer* renderer, Player* Player, Stage* stage) : mPlayer(Player), mStoneButtonClicked(false), mStage(stage)
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
	delete mTower1Button;
	delete mTower2Button;
	delete mStage;
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
	mTower1Button = new Button(mGame->getTexture(TOWER1), mRenderer, mMouse, 350, 50, { 0, 0, 239, 486 }, mFont);
	mTower2Button = new Button(mGame->getTexture(TOWER2), mRenderer, mMouse, 400, 50, { 0, 0, 251, 481 }, mFont);
	mStage1Button = new Button(mRenderer, mMouse, 300, 300, mFont, "Stage 1");
	mStage2Button = new Button(mRenderer, mMouse, 300, 400, mFont, "Stage 2");
	mStage3Button = new Button(mRenderer, mMouse, 300, 500, mFont, "Stage 3");
	mStage4Button = new Button(mRenderer, mMouse, 300, 600, mFont, "Stage 4");
	mSpecialUpgradeButton = new Button(mRenderer, mMouse, 600, 300, mFont, "Special Up");
	mArcherBonusButton = new Button(mRenderer, mMouse, 300, 300, mFont, "Archer Bonus");
	mMeleeBonusButton = new Button(mRenderer, mMouse, 300, 400, mFont, "Melee Bonus");
	mTowerBonusButton = new Button(mRenderer, mMouse, 300, 500, mFont, "Tower Bonus");
	HideSpecialUpgradeScreen();
	HideGameplayButtons();
	HideIntermissionButtons();
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
	mTower1Button->addTooltip("Cost: 500 gold. Build a weak tower");
	mTower2Button->addTooltip("Cost: 850 gold. Build a strong tower");
	mGold = "Gold: 100";
	mTextSurface = TTF_RenderText_Solid(mFont, mGold.c_str(), mTextColor);
	mTextTexture = SDL_CreateTextureFromSurface(mRenderer, mTextSurface);

	mButtonMap.emplace(mStartGameButton, [this]()
		{
			ShowIntermissionButtons();
	mStartGameButton->Hide();
		});

	mButtonMap.emplace(mPauseButton, [this]()
		{
			mGame->Pause();
	HideGameplayButtons();
	mContinueButton->Show();
	mPauseButton->Hide();
		});

	mButtonMap.emplace(mContinueButton, [this]()
		{
			mGame->Continue();
	ShowGameplayButtons();
	mPauseButton->Show();
	mContinueButton->Hide();
		});

	mButtonMap.emplace(mKnightButton, [this]()
		{
			mPlayer->CreateKnight();
		});

	mButtonMap.emplace(mSpearKnightButton, [this]()
		{
			mPlayer->CreateSpearKnight();
		});

	mButtonMap.emplace(mAxeKnightButton, [this]()
		{
			mPlayer->CreateAxeKnight();
		});

	mButtonMap.emplace(mAcherButton, [this]()
		{
			mPlayer->CreateArcher();
		});

	mButtonMap.emplace(mHeavyInfantryButton, [this]()
		{
			mPlayer->CreateHeavyInfantry();
		});

	mButtonMap.emplace(mRockButton, [this]()
		{
			mStoneButtonClicked = true;
		});

	mButtonMap.emplace(mUpgradeArmorButton, [this]()
		{
			mPlayer->UpgradeArmor();
		});

	mButtonMap.emplace(mUpgradeAttackButton, [this]()
		{
			mPlayer->UpgradeAttack();
		});

	mButtonMap.emplace(mUpgradeRockButton, [this]()
		{
			mPlayer->UpgradeRock();
		});

	mButtonMap.emplace(mChangeOrderButton, [this]()
		{
			mPlayer->ChangeOrder();
		});

	mButtonMap.emplace(mTower1Button, [this]()
		{
			mPlayer->CreateTower1();
		});

	mButtonMap.emplace(mTower2Button, [this]()
		{
			mPlayer->CreateTower2();
		});

	mButtonMap.emplace(mStage1Button, [this]()
		{
			HideIntermissionButtons();
			ShowGameplayButtons();
			mPauseButton->Show();
			mStage->LoadStage1(mGame->GetModifiableGameObjectVector());
			mGame->StartGame();
		});

	mButtonMap.emplace(mStage2Button, [this]()
		{
			HideIntermissionButtons();
			ShowGameplayButtons();
			mPauseButton->Show();
			mStage->LoadStage2(mGame->GetModifiableGameObjectVector());
			mGame->StartGame();
		});

	mButtonMap.emplace(mStage3Button, [this]()
		{
			HideIntermissionButtons();
			ShowGameplayButtons();
			mPauseButton->Show();
			mStage->LoadStage3(mGame->GetModifiableGameObjectVector());
			mGame->StartGame();
		});

	mButtonMap.emplace(mStage4Button, [this]()
		{
			HideIntermissionButtons();
			ShowGameplayButtons();
			mPauseButton->Show();
			mStage->LoadStage4(mGame->GetModifiableGameObjectVector());
			mGame->StartGame();
		});

	mButtonMap.emplace(mSpecialUpgradeButton, [this]()
		{
			HideIntermissionButtons();
			ShowSpecialUpgradeScreen();
		});

	mButtonMap.emplace(mArcherBonusButton, [this]()
		{
			mPlayer->BuyArcherUpgrade();
			HideSpecialUpgradeScreen();
			ShowIntermissionButtons();
		});

	mButtonMap.emplace(mMeleeBonusButton, [this]()
		{
			mPlayer->BuyShieldUpgrade();
			HideSpecialUpgradeScreen();
			ShowIntermissionButtons();
		});
	mButtonMap.emplace(mTowerBonusButton, [this]()
		{
			mPlayer->BuyTowerUpgrade();
			HideSpecialUpgradeScreen();
			ShowIntermissionButtons();
		});
}

void UI::Update()
{
	for (const auto& pair : mButtonMap)
	{
		pair.first->Update();
	}
	mMouse->Update();
}

void UI::Draw()
{
	for (const auto& pair : mButtonMap)
	{
		pair.first->Draw();
	}
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
	for (const auto& pair : mButtonMap)
	{
		if (pair.first->IsSelected())
		{
			pair.second();				//Important to remember that () means the lambda function is called. Without () the function is not called
			break;
		}
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

void UI::VictoryScreen()
{
	mStage->ClearStage(mGame->GetModifiableGameObjectVector());
	HideGameplayButtons();
	ShowIntermissionButtons();
}

void UI::HideGameplayButtons()
{
	mKnightButton->Hide();
	mSpearKnightButton->Hide();
	mAxeKnightButton->Hide();
	mAcherButton->Hide();
	mHeavyInfantryButton->Hide();
	mChangeOrderButton->Hide();
	mRockButton->Hide();
	mTower1Button->Hide();
	mTower2Button->Hide();
	mUpgradeArmorButton->Hide();
	mUpgradeAttackButton->Hide();
}

void UI::ShowGameplayButtons()
{
	mKnightButton->Show();
	mSpearKnightButton->Show();
	mAxeKnightButton->Show();
	mAcherButton->Show();
	mHeavyInfantryButton->Show();
	mChangeOrderButton->Show();
	mRockButton->Show();
	mTower1Button->Show();
	mTower2Button->Show();
	mUpgradeArmorButton->Show();
	mUpgradeAttackButton->Show();
}

void UI::ShowIntermissionButtons()
{
	mStage1Button->Show();
	mStage2Button->Show();
	mStage3Button->Show();
	mStage4Button->Show();
	mUpgradeRockButton->Show();
	mSpecialUpgradeButton->Show();
}

void UI::HideIntermissionButtons()
{
	mStage1Button->Hide();
	mStage2Button->Hide();
	mStage3Button->Hide();
	mStage4Button->Hide();
	mUpgradeRockButton->Hide();
	mSpecialUpgradeButton->Hide();
}

void UI::ShowSpecialUpgradeScreen()
{
	mArcherBonusButton->Show();
	mMeleeBonusButton->Show();
	mTowerBonusButton->Show();
}

void UI::HideSpecialUpgradeScreen()
{
	mArcherBonusButton->Hide();
	mMeleeBonusButton->Hide();
	mTowerBonusButton->Hide();
}
