#include "Game.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "Player.h"
#include "units/Projectile.h"
#include "TextureManager.h"
#include "units/Arrow.h"
#include "units/Catapult.h"
#include "units/Rock.h"

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
	BG = new Background(TextureManager::getTexture(BACKGROUND_TEXTURE), mRenderer, WIDTH, HEIGHT);
	mPlayer = new Player(this);
	mAI = new AIhard(this);
	mStage = new Stage(this, mRenderer, mAI);
	mUI = new UI(this, mRenderer, mPlayer, mStage);
	mPlayer->setUiPointer(mUI);
	mUI->Initialize();
	mIsMenuActive = true;
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
	delete mStage;
	TextureManager::ClearTextureMap();
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
	target->OnDeathAction();
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
	TextureManager::LoadAllTextures(mRenderer);
	Archer::LoadAnimation();
	Arrow::LoadAnimation();
	AxeKnight::LoadAnimation();
	Castle::LoadAnimation();
	Catapult::LoadAnimation();
	HeavyInfantry::LoadAnimation();
	Knight::LoadAnimation();
	Rock::LoadAnimation();
	SpearKnight::LoadAnimation();
	Tower1::LoadAnimation();
	Tower2::LoadAnimation();
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
	mIsMenuActive = false;
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

void Game::GameOver(Castle* castle)
{
	if (castle->getIsPlayer())
	{
		Shutdown();
	}
	else
	{
		mUI->VictoryScreen();
	}
	mAI->Deactivate();
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
