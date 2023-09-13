#include "Game.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "Player.h"
#include "units/Projectile.h"

Game::Game()
{
	mIsRunning = false;
	mIsUpdatingObjects = false;
	mTicksCount = 0;
	mKills = 0;
	mDeaths = 0;
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
	mPlayer = new Player(this);
	mUI = new UI(this, mRenderer, mPlayer);
	mPlayer->setUiPointer(mUI);
	mUI->Initialize();
	mIsMenuActive = true;
	mAI = new AIhard(this);
	mIsRunning = true;
	
	return true;
}

void Game::Shutdown()
{
	delete BG;
	mObjects.clear();
	mDeadObjects.clear();
	mNonCollidableObjects.clear();
	mPendingProjectiles.clear();
	while (mPendingAIObjects.size() > 0)
	{
		mPendingAIObjects.pop();
	}
	while (mPendingPlayerObjects.size() > 0)
	{
		mPendingAIObjects.pop();
	}
	delete mPlayer;
	mTextureMap.clear();
	std::cout << "kills: " << mKills << " deaths: " << mDeaths << std::endl;
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
	float d = INFINITY;
	GameObject* result = nullptr;
	for (auto& i : mObjects)
	{
		if (i != gameObject && (i->getIsPlayer() != gameObject->getIsPlayer()) && !dynamic_cast<Projectile*>(i))
		{
			float temp = Vector2::CalculateDistance(i->getPositionVec(), gameObject->getPositionVec());
			if (temp < d)
			{
				d = temp;
				result = i;
			}
		}
	}
	if (d < range)
	{
		return result;
	}
	return nullptr;
}

GameObject* Game::CollisionDetection(GameObject* gameObject)
{
	int x = gameObject->getVelocityVec().getIntX() > 0 ? 2 : -2;
	int y = gameObject->getVelocityVec().getIntY() > 0 ? 2 : -2;
	SDL_Rect rectangle = gameObject->getCollisionRect();
	rectangle.x += x;
	rectangle.y += y;
	for (auto& i : mObjects)
	{
		if (i != gameObject && SDL_HasIntersection(&rectangle, &i->getCollisionRect()))
		{
			return i;
		}
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
	if (target->getIsPlayer() && !dynamic_cast<Projectile*>(target))
	{
		mDeaths++;
	}
	else if (!target->getIsPlayer() && !dynamic_cast<Projectile*>(target))
	{
		mPlayer->IncreaseGold(target->getGoldCost() * mAI->getGoldMultiplier());
		mKills++;
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

void Game::LoadData()
{
	getTexture("assets/castle.png", CASTLE);
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

	getTexture("assets/HeavyInfantry/HeavyInfantry.png", HEAVY_INFANTRY);
	getTexture("assets/HeavyInfantry/HeavyInfantryButton.png", HEAVY_INFANTRY_BUTTON);

	getTexture("assets/Knight/Idle/Tuscan_Idle_10000.png", KNIGHT_BUTTON);
	getTexture("assets/bSpearman/Button.png", SPEARMAN_BUTTON);
	getTexture("assets/GreekSoldier/Idle/GreekBasic_Idle_00.png", GREEK_BUTTON);
	getTexture("assets/ArcherSkeleton/Idle/Separate sp/idle (1).png", ARCHER_BUTTON);
	getTexture("assets/ArmorUpgrade.png", ARMOR_UPGRADE_BUTTON);
	getTexture("assets/AttackUpgrade.png", ATTACK_UPGRADE_BUTTON);
	getTexture("assets/Mouse.png", MOUSE_BUTTON);
	getTexture("assets/ChangeOrder.png", CHANGE_ORDER_BUTTON);
	getTexture("assets/Rock.png", ROCK);
	getTexture("assets/RockUpgrade.png", ROCK_UPGRADE_BUTTON);

	getTexture("assets/Arrow.png", ARROW);

	getTexture("assets/tower_2.png", TOWER2);
	getTexture("assets/tower.png", TOWER1);
	
}

void Game::CreateUnit(GameObject* unit)
{
	if (unit->getIsPlayer())
	{
		mPendingPlayerObjects.emplace(unit);
	}
	else
	{
		mPendingAIObjects.emplace(unit);	
	}
}

void Game::ClearAIQueue()
{
	while (mPendingAIObjects.size() > 0)
	{
		mPendingAIObjects.pop();
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
	mObjects.emplace_back(new Castle(mRenderer, WIDTH - 974, HEIGHT - 175, this, 1));
	mObjects.emplace_back(new Castle(mRenderer, WIDTH - 50, HEIGHT - 175, this, 0));
	mObjects.at(1)->setArmor(120);
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
			float m = (float)d / Radious;
			m = 1 - m;
			i->TakeDamage(Damage * m);
		}
	}
}

void Game::AddProjectile(GameObject* projectile)
{
	mPendingProjectiles.emplace_back(projectile);
}

void Game::IncreasePlayerBuildingCount()
{
	mPlayerBuildingCount++;
}

void Game::IncreaseAIBuildingCount()
{
	mAIBuildingCount++;
}

void Game::DecreasePlayerBuildingCount()
{
	mPlayerBuildingCount--;
}

void Game::DecreaseAIBuildingCount()
{
	mAIBuildingCount--;
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
				if (dynamic_cast<Projectile*>(i) || dynamic_cast<Building*>(i))
				{
					auto iter = std::find(mObjects.begin(), mObjects.end(), i);
					std::iter_swap(iter, mObjects.end() - 1);
					mObjects.pop_back();
				}
				else
				{
					auto iter = std::find(mObjects.begin(), mObjects.end(), i);
					std::iter_swap(iter, mObjects.end() - 1);
					mObjects.pop_back();
					mNonCollidableObjects.emplace_back(i);
				}
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
					int d = i->getX() - getPlayerCreateUnitPosition();
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
				aux->setOrder(mPlayer->getIsPlayerAdvancing());
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
					int d = i->getX() - getAICreateUnitPosition();
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
		if (mPendingProjectiles.size() > 0)
		{
			for (auto& i : mPendingProjectiles)
			{
				mObjects.emplace_back(i);
			}
			mPendingProjectiles.clear();
		}
	}
	if (SDL_GetTicks() - mTimeSeconds > 6000)
	{
		mTimeSeconds = SDL_GetTicks();
		mAI->ChangeState();
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
