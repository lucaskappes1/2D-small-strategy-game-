#include "Game.h"
#include <iostream>
#include <thread>
#include <chrono>

Game::Game()
{
	mIsRunning = false;
	mIsUpdatingObjects = false;
	mTicksCount = 0;
	mKills = 0;
	mDeaths = 0;
	mPlayerGold = 100;
}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_Log("Failure: ", SDL_GetError());
		return false;
	}
	mWindow = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	if (mWindow == nullptr)
	{
		SDL_Log("Failure: ", SDL_GetError());
		return false;
	}
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	if (mRenderer == nullptr)
	{
		SDL_Log("Failure: ", SDL_GetError());
		return false;
	}
	if (!IMG_Init(IMG_INIT_PNG))
	{
		SDL_Log("Failure: ", SDL_GetError());
		return false;
	}
	if (TTF_Init() == -1)
	{
		SDL_Log("Failure: ", SDL_GetError());
		return false;
	}
	LoadData();
	BG = new Background(getTexture("assets/Background.png", BACKGROUND_TEXTURE), mRenderer, WIDTH, HEIGHT);
	mUI = new UI(this, mRenderer);
	mUI->Initialize();
	mIsMenuActive = true;
	mAI = new AIhard(this);
	mIsRunning = true;
	return true;
}

void Game::Shutdown()
{
	delete BG;
	for (auto& i : mObjects)
	{
		delete i;
	}
	for (auto& i : mDeadObjects)
	{
		delete i;
	}
	while (mPendingAIObjects.size() > 0)
	{
		mPendingAIObjects.pop();
	}
	while (mPendingPlayerObjects.size() > 0)
	{
		mPendingAIObjects.pop();
	}
	mTextureMap.clear();
	std::cout << "kills: " << mKills << " deaths: " << mDeaths << "gold: " << mPlayerGold << std::endl;
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	std::this_thread::sleep_for(std::chrono::seconds(10));
	exit(EXIT_SUCCESS);
}

GameObject* Game::RangedAttackDetection(GameObject* gameObject, int range)
{
	int index = -1;
	for (auto& i : mObjects)
	{
		index++;
		if (i == gameObject)
		{
			break;
		}
	}
	if (gameObject->getIsPlayer())
	{
		for (int i = index + 1; i < mObjects.size(); i++)
		{
			if (!mObjects.at(i)->getIsPlayer() && mObjects.at(i)->eState != GameObject::DEATH)
			{
				if(mObjects.at(i)->getX() - gameObject->getX() < range)
				{
					return mObjects.at(i);
				}
				else
				{
					return nullptr;
				}
			}
		}
	}
	else
	{
		for (int i = index - 1; i < mObjects.size(); i--)
		{
			if (mObjects.at(i)->getIsPlayer() && mObjects.at(i)->eState != GameObject::DEATH)
			{
				if (gameObject->getX() - mObjects.at(i)->getX() < range)
				{
					return mObjects.at(i);
				}
			}
		}
	}
	return nullptr;
}

GameObject* Game::CollisionDetection(GameObject* gameObject)
{
	int index = -1;
	for (auto& i : mObjects)
	{
		index++;
		if (i == gameObject)
		{
			break;
		}
	}
	try
	{
		if (gameObject->getIsPlayer() && SDL_HasIntersection(&gameObject->getCollisionRect(), &mObjects.at(index + 1)->getCollisionRect()))
		{
			return mObjects.at(index + 1);
		}
		else if (!gameObject->getIsPlayer() && SDL_HasIntersection(&gameObject->getCollisionRect(), &mObjects.at(index - 1)->getCollisionRect()))
		{
			return mObjects.at(index - 1); 
		}
	}
	catch (const std::out_of_range& e)
	{
		Shutdown();
	}
	return nullptr;
}

SDL_Texture* Game::getTexture(int id)
{
	auto temp = mTextureMap.find(id);
	if (temp == mTextureMap.end())
	{
		return nullptr;
	}
	return temp->second;
}

void Game::KillObject(GameObject* target)
{
	if (target->getIsPlayer())
	{
		mDeaths++;
	}
	else
	{
		mPlayerGold += target->getGoldCost() * mAI->getGoldMultiplier();
		mKills++;
		mUI->UpdateGoldText();
	}
	mDeadObjects.emplace_back(target);
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		Update();
		Render();
		ProcessInput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		case SDL_MOUSEBUTTONUP:
			if(event.button.button == SDL_BUTTON_LEFT)
			{
				mUI->OnMouseClickEvent();
			}
		}
	}
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
}

void Game::ApplyPlayerUpgrade()
{
	mPendingPlayerObjects.back()->setAttack(mPendingPlayerObjects.back()->getAttack() + mPlayerAttackUpgradeCount);
	mPendingPlayerObjects.back()->setArmor(mPendingPlayerObjects.back()->getArmor() + mPlayerArmorUpgradeCount);
}

void Game::LoadData()
{
	getTexture("assets/ArcherSkeleton/Walk/walk.png", ARCHER_WALK);
	getTexture("assets/ArcherSkeleton/Attack/attack.png", ARCHER_ATTACK);
	getTexture("assets/ArcherSkeleton/Idle/Separate sp/idle (1).png", ARCHER_IDLE);
	getTexture("assets/ArcherSkeleton/Dead/dead.png", ARCHER_DEATH);

	getTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_00.png", GREEK_WALK0);
	getTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_01.png", GREEK_WALK1);
	getTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_02.png", GREEK_WALK2);
	getTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_03.png", GREEK_WALK3);
	getTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_04.png", GREEK_WALK4);
	getTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_05.png", GREEK_WALK5);
	getTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_06.png", GREEK_WALK6);
	getTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_07.png", GREEK_WALK7);
	getTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_08.png", GREEK_WALK8);
	getTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_09.png", GREEK_WALK9);
	getTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_10.png", GREEK_WALK10);
	getTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_11.png", GREEK_WALK11);
	getTexture("assets/GreekSoldier/Attack/GreekBasic_Attack_0.png", GREEK_ATTACK0);
	getTexture("assets/GreekSoldier/Attack/GreekBasic_Attack_1.png", GREEK_ATTACK1);
	getTexture("assets/GreekSoldier/Attack/GreekBasic_Attack_2.png", GREEK_ATTACK2);
	getTexture("assets/GreekSoldier/Attack/GreekBasic_Attack_3.png", GREEK_ATTACK3);
	getTexture("assets/GreekSoldier/Attack/GreekBasic_Attack_4.png", GREEK_ATTACK4);
	getTexture("assets/GreekSoldier/Attack/GreekBasic_Attack_5.png", GREEK_ATTACK5);
	getTexture("assets/GreekSoldier/Attack/GreekBasic_Attack_6.png", GREEK_ATTACK6);
	getTexture("assets/GreekSoldier/Attack/GreekBasic_Attack_7.png", GREEK_ATTACK7);
	getTexture("assets/GreekSoldier/Idle/GreekBasic_Idle_00.png", GREEK_IDLE);
	getTexture("assets/GreekSoldier/Die/GreekBasic_Die_00.png", GREEK_DEATH0);
	getTexture("assets/GreekSoldier/Die/GreekBasic_Die_01.png", GREEK_DEATH1);
	getTexture("assets/GreekSoldier/Die/GreekBasic_Die_02.png", GREEK_DEATH2);
	getTexture("assets/GreekSoldier/Die/GreekBasic_Die_03.png", GREEK_DEATH3);
	getTexture("assets/GreekSoldier/Die/GreekBasic_Die_04.png", GREEK_DEATH4);
	getTexture("assets/GreekSoldier/Die/GreekBasic_Die_05.png", GREEK_DEATH5);
	getTexture("assets/GreekSoldier/Die/GreekBasic_Die_06.png", GREEK_DEATH6);
	getTexture("assets/GreekSoldier/Die/GreekBasic_Die_07.png", GREEK_DEATH7);
	getTexture("assets/GreekSoldier/Die/GreekBasic_Die_08.png", GREEK_DEATH8);
	getTexture("assets/GreekSoldier/Die/GreekBasic_Die_09.png", GREEK_DEATH9);
	getTexture("assets/GreekSoldier/Die/GreekBasic_Die_10.png", GREEK_DEATH10);
	getTexture("assets/GreekSoldier/Die/GreekBasic_Die_11.png", GREEK_DEATH11);


	getTexture("assets/Knight/Walk/Tuscan_Walk_20000.png", KNIGHT_WALK0);
	getTexture("assets/Knight/Walk/Tuscan_Walk_20001.png", KNIGHT_WALK1);
	getTexture("assets/Knight/Walk/Tuscan_Walk_20002.png", KNIGHT_WALK2);
	getTexture("assets/Knight/Walk/Tuscan_Walk_20003.png", KNIGHT_WALK3);
	getTexture("assets/Knight/Walk/Tuscan_Walk_20004.png", KNIGHT_WALK4);
	getTexture("assets/Knight/Walk/Tuscan_Walk_20005.png", KNIGHT_WALK5);
	getTexture("assets/Knight/Walk/Tuscan_Walk_20006.png", KNIGHT_WALK6);
	getTexture("assets/Knight/Walk/Tuscan_Walk_20007.png", KNIGHT_WALK7);
	getTexture("assets/Knight/Walk/Tuscan_Walk_20008.png", KNIGHT_WALK8);
	getTexture("assets/Knight/Walk/Tuscan_Walk_20009.png", KNIGHT_WALK9);
	getTexture("assets/Knight/Walk/Tuscan_Walk_20010.png", KNIGHT_WALK10);
	getTexture("assets/Knight/Walk/Tuscan_Walk_20011.png", KNIGHT_WALK11);
	getTexture("assets/Knight/Walk/Tuscan_Walk_20012.png", KNIGHT_WALK12);
	getTexture("assets/Knight/Walk/Tuscan_Walk_20013.png", KNIGHT_WALK13);
	getTexture("assets/Knight/Walk/Tuscan_Walk_20014.png", KNIGHT_WALK14);
	getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20000.png", KNIGHT_ATTACK0);
	getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20001.png", KNIGHT_ATTACK1);
	getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20002.png", KNIGHT_ATTACK2);
	getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20003.png", KNIGHT_ATTACK3);
	getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20004.png", KNIGHT_ATTACK4);
	getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20005.png", KNIGHT_ATTACK5);
	getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20006.png", KNIGHT_ATTACK6);
	getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20007.png", KNIGHT_ATTACK7);
	getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20008.png", KNIGHT_ATTACK8);
	getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20009.png", KNIGHT_ATTACK9);
	getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20010.png", KNIGHT_ATTACK10);
	getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20011.png", KNIGHT_ATTACK11);
	getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20012.png", KNIGHT_ATTACK12);
	getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20013.png", KNIGHT_ATTACK13);
	getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20014.png", KNIGHT_ATTACK14);
	getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20015.png", KNIGHT_ATTACK15);
	getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20016.png", KNIGHT_ATTACK16);
	getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20017.png", KNIGHT_ATTACK17);
	getTexture("assets/Knight/Idle/Tuscan_Idle_20000.png", KNIGHT_IDLE);
	getTexture("assets/Knight/Death/Tuscan_Death_20000.png", KNIGHT_DEATH0);
	getTexture("assets/Knight/Death/Tuscan_Death_20001.png", KNIGHT_DEATH1);
	getTexture("assets/Knight/Death/Tuscan_Death_20002.png", KNIGHT_DEATH2);
	getTexture("assets/Knight/Death/Tuscan_Death_20003.png", KNIGHT_DEATH3);
	getTexture("assets/Knight/Death/Tuscan_Death_20004.png", KNIGHT_DEATH4);
	getTexture("assets/Knight/Death/Tuscan_Death_20005.png", KNIGHT_DEATH5);
	getTexture("assets/Knight/Death/Tuscan_Death_20006.png", KNIGHT_DEATH6);
	getTexture("assets/Knight/Death/Tuscan_Death_20007.png", KNIGHT_DEATH7);
	getTexture("assets/Knight/Death/Tuscan_Death_20008.png", KNIGHT_DEATH8);
	getTexture("assets/Knight/Death/Tuscan_Death_20009.png", KNIGHT_DEATH9);
	getTexture("assets/Knight/Death/Tuscan_Death_20010.png", KNIGHT_DEATH10);
	getTexture("assets/Knight/Death/Tuscan_Death_20011.png", KNIGHT_DEATH11);
	getTexture("assets/Knight/Death/Tuscan_Death_20012.png", KNIGHT_DEATH12);
	getTexture("assets/Knight/Death/Tuscan_Death_20013.png", KNIGHT_DEATH13);
	getTexture("assets/Knight/Death/Tuscan_Death_20014.png", KNIGHT_DEATH14);
	getTexture("assets/Knight/Death/Tuscan_Death_20015.png", KNIGHT_DEATH15);

	getTexture("assets/bSpearman/_walk/bSpearman_Walk_Right_strip10.png", SPEARMAN_WALK);
	getTexture("assets/bSpearman/_attack/bSpearman_Attack01_Right_strip8.png", SPEARKMAN_ATTACK);
	getTexture("assets/bSpearman/bSpearman_Idle_strip8.png", SPEARMAN_IDLE);
	getTexture("assets/bSpearman/_death/bSpearman_Die_Right_strip8.png", SPEARMAN_DEATH);

	getTexture("assets/Knight/Idle/Tuscan_Idle_10000.png", KNIGHT_BUTTON);
	getTexture("assets/bSpearman/Button.png", SPEARMAN_BUTTON);
	getTexture("assets/GreekSoldier/Idle/GreekBasic_Idle_00.png", GREEK_BUTTON);
	getTexture("assets/ArcherSkeleton/Idle/Separate sp/idle (1).png", ARCHER_BUTTON);
	getTexture("assets/ArmorUpgrade.png", ARMOR_UPGRADE_BUTTON);
	getTexture("assets/AttackUpgrade.png", ATTACK_UPGRADE_BUTTON);
	getTexture("assets/Mouse.png", MOUSE_BUTTON);
	getTexture("assets/ChangeOrder.png", CHANGE_ORDER_BUTTON);
}

void Game::CreateKnight(bool isPlayer, bool isAdvancing)
{
	if (isPlayer)
	{
		if (mPlayerGold >= Knight::getStaticGoldCost())
		{
			mPlayerGold -= Knight::getStaticGoldCost();
			mPendingPlayerObjects.emplace(new Knight(mRenderer, PLAYER_CREATE_UNIT_POSITION, HEIGHT - 110, this, 1, isAdvancing));
			ApplyPlayerUpgrade();
			mUI->UpdateGoldText();
		}
	}
	else
	{
		mPendingAIObjects.emplace(new Knight(mRenderer, AI_CREATE_UNIT_POSITION, HEIGHT - 110, this, 0, isAdvancing));
	}
}

void Game::CreateSpearKnight(bool isPlayer, bool isAdvancing)
{
	
	if (isPlayer)
	{
		if (mPlayerGold >= SpearKnight::getStaticGoldCost())
		{
			mPlayerGold -= SpearKnight::getStaticGoldCost();
			mPendingPlayerObjects.emplace(new SpearKnight(mRenderer, PLAYER_CREATE_UNIT_POSITION, HEIGHT - 110, this, 1, isAdvancing));
			ApplyPlayerUpgrade();
			mUI->UpdateGoldText();
		}
	}
	else
	{
		mPendingAIObjects.emplace(new SpearKnight(mRenderer, AI_CREATE_UNIT_POSITION, HEIGHT - 110, this, 0, isAdvancing));
	}
}

void Game::CreateAxeKnight(bool isPlayer, bool isAdvancing)
{
	if (isPlayer)
	{
		if (mPlayerGold >= AxeKnight::getStaticGoldCost())
		{
			mPlayerGold -= AxeKnight::getStaticGoldCost();
			mPendingPlayerObjects.emplace(new AxeKnight(mRenderer, PLAYER_CREATE_UNIT_POSITION, HEIGHT - 110, this, 1, isAdvancing));
			ApplyPlayerUpgrade();
			mUI->UpdateGoldText();
		}
	}
	else
	{
		mPendingAIObjects.emplace(new AxeKnight(mRenderer, AI_CREATE_UNIT_POSITION, HEIGHT - 110, this, 0, isAdvancing));
	}
}

void Game::CreateArcher(bool isPlayer, bool isAdvancing)
{
	if (isPlayer)
	{
		if (mPlayerGold >= Archer::getStaticGoldCost())
		{
			mPlayerGold -= Archer::getStaticGoldCost();
			mPendingPlayerObjects.emplace(new Archer(mRenderer, PLAYER_CREATE_UNIT_POSITION, HEIGHT - 110, this, 1, isAdvancing));
			ApplyPlayerUpgrade();
			mUI->UpdateGoldText();
		}
	}
	else
	{
		mPendingAIObjects.emplace(new Archer(mRenderer, AI_CREATE_UNIT_POSITION, HEIGHT - 110, this, 0, isAdvancing));
	}
}

void Game::ClearAIQueue()
{
	while (mPendingAIObjects.size() > 0)
	{
		mPendingAIObjects.pop();
	}
}

void Game::PlayerUpgradeArmor()
{
	if (mPlayerGold >= 500)
	{
		mPlayerArmorUpgradeCount++;
		mPlayerGold -= 500;
		mUI->UpdateGoldText();
	}
}

void Game::PlayerUpgradeAttack()
{
	if (mPlayerGold >= 500)
	{
		mPlayerAttackUpgradeCount++;
		mPlayerGold -= 500;
		mUI->UpdateGoldText();
	}
}

void Game::PlayerChangeOrder()
{
	for (auto& i : mObjects)
	{
		if (i->getIsPlayer())
		{
			i->ChangeOrder();
		}
	}
}

void Game::StartGame()
{
	mObjects.emplace_back(new Castle(mRenderer, getTexture("assets/Castle.png", CASTLE), WIDTH - 974, HEIGHT - 175, this, 1));
	mObjects.emplace_back(new Castle(mRenderer, getTexture("assets/Castle.png", CASTLE), WIDTH - 50, HEIGHT - 175, this, 0));
	mObjects.at(1)->setArmor(50);
	mIsMenuActive = false;
	mUI->StartGame();
	mAI->Activate();
}

void Game::Pause()
{
	mIsMenuActive = true;
	mAI->Deactivate();
}

void Game::Continue()
{
	mIsMenuActive = false;
	mAI->Activate();
}

void Game::SplashDamage(int Damage, int x, int Radious)
{
	for (auto& i : mObjects)
	{
		int d = x - i->getX();
		d = abs(d);
		if (d < Radious)
		{
			float m = (float)x / Radious;
			m = 1 - m;
			i->TakeDamage(Damage * m);
		}
	}
}

SDL_Texture* Game::getTexture(std::string path, int name)
{
	auto temp = mTextureMap.find(name);
	if (temp == mTextureMap.end())
	{
		SDL_Surface* surf = IMG_Load(path.c_str());
		SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		mTextureMap.emplace(name, tex);
		return tex;
	}
	return temp->second;	//temp é um iterator. Assim, temp->second retorna o value da posição do iterator no mapa
}

void Game::Update()
{
	if (mIsMenuActive)
	{
		mUI->Update();
	}
	else
	{
		// Compute delta time
		// Wait until 16ms has elapsed since last frame
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

		float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
		if (deltaTime > 0.05f)
		{
			deltaTime = 0.05f;
		}
		mTicksCount = SDL_GetTicks();

		mUI->Update();
		mIsUpdatingObjects = true;
		for (auto& i : mObjects)
		{
			i->Update(deltaTime);
		}
		mIsUpdatingObjects = false;
		if (mDeadObjects.size() > 0)
		{
			for (auto& i : mDeadObjects)
			{
				auto iter = std::find(mObjects.begin(), mObjects.end(), i);
				std::iter_swap(iter, mObjects.end() - 1);
				mObjects.pop_back();
				mNonCollidableObjects.emplace_back(i);
			}
			mDeadObjects.clear();
		}
		if (SDL_GetTicks() - mClearFloorTimer > 30000)
		{
			mClearFloorTimer = SDL_GetTicks();
			mNonCollidableObjects.clear();
		}
		if (mPendingPlayerObjects.size() > 0)
		{
			bool temp = true;
			for (auto& i : mObjects)
			{
				if (i->getIsPlayer())
				{
					int d = i->getX() - PLAYER_CREATE_UNIT_POSITION;
					if (d <= 32 && d >= 0)
					{
						temp = false;
						break;
					}
				}
			}
			if (temp)
			{
				GameObject* aux = mPendingPlayerObjects.front();
				aux->setOrder(mUI->getIsPlayerAdvancing());
				mPendingPlayerObjects.pop();
				mObjects.emplace_back(aux);
			}
		}
		if (mPendingAIObjects.size() > 0)
		{
			bool temp = true;
			for (auto& i : mObjects)
			{
				if (!i->getIsPlayer())
				{
					int d = i->getX() - AI_CREATE_UNIT_POSITION;
					if (d <= 0 && d >= -32)
					{
						temp = false;
						break;
					}
				}
			}
			if (temp)
			{
				GameObject* aux = mPendingAIObjects.front();
				mPendingAIObjects.pop();
				mObjects.emplace_back(aux);
			}
		}
	}
	std::sort(mObjects.begin(), mObjects.end(), [](const GameObject* a, const GameObject* b) {
		return a->getCollisionRect().x < b->getCollisionRect().x;
		});
	if (SDL_GetTicks() - mTimeSeconds > 4000)
	{
		mTimeSeconds = SDL_GetTicks();
		mAI->Act();
	}
}

void Game::Render()
{
	SDL_RenderClear(mRenderer);
	BG->Draw();
	for (auto& i : mNonCollidableObjects)
	{
		i->Draw();
	}
	for (auto& i : mObjects)
	{
		i->Draw();
	}
	mUI->Draw();
	SDL_RenderPresent(mRenderer);
}
