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
	mWindow = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
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
	BG = new Background(getTexture("assets/Background.png", "Background"), mRenderer);
	
	mObjects.emplace_back(new Castle(mRenderer, getTexture("assets/Castle.png", "Castle"), 50, 425, this, 1));
	mObjects.emplace_back(new Castle(mRenderer, getTexture("assets/Castle.png", "Castle"), 750, 425, this, 0));
	mObjects.at(1)->setArmor(50);
	mObjects.at(1)->setAttack(7);
	mUI = new UI(this, mRenderer);
	mUI->Initialize();
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
			if (!mObjects.at(i)->getIsPlayer())
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
			if (mObjects.at(i)->getIsPlayer())
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

void Game::RemoveObject(GameObject* target)
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

void Game::CreateKnight(bool isPlayer)
{
	if (isPlayer)
	{
		if (mPlayerGold >= Knight::getStaticGoldCost())
		{
			mPlayerGold -= Knight::getStaticGoldCost();
			mPendingPlayerObjects.emplace(new Knight(mRenderer, getTexture("assets/Knight.png", "Knight"), PLAYER_CREATE_UNIT_POSITION, 490, this, 1));
			ApplyPlayerUpgrade();
			mUI->UpdateGoldText();
		}
	}
	else
	{
		mPendingAIObjects.emplace(new Knight(mRenderer, getTexture("assets/Knight.png", "Knight"), AI_CREATE_UNIT_POSITION, 490, this, 0));
	}
}

void Game::CreateSpearKnight(bool isPlayer)
{
	
	if (isPlayer)
	{
		if (mPlayerGold >= SpearKnight::getStaticGoldCost())
		{
			mPlayerGold -= SpearKnight::getStaticGoldCost();
			mPendingPlayerObjects.emplace(new SpearKnight(mRenderer, getTexture("assets/SpearKnight.png", "SpearKnight"), PLAYER_CREATE_UNIT_POSITION, 490, this, 1));
			ApplyPlayerUpgrade();
			mUI->UpdateGoldText();
		}
	}
	else
	{
		mPendingAIObjects.emplace(new SpearKnight(mRenderer, getTexture("assets/SpearKnight.png", "SpearKnight"), AI_CREATE_UNIT_POSITION, 490, this, 0));
	}
}

void Game::CreateAxeKnight(bool isPlayer)
{
	if (isPlayer)
	{
		if (mPlayerGold >= AxeKnight::getStaticGoldCost())
		{
			mPlayerGold -= AxeKnight::getStaticGoldCost();
			mPendingPlayerObjects.emplace(new AxeKnight(mRenderer, getTexture("assets/AxeKnight.png", "AxeKnight"), PLAYER_CREATE_UNIT_POSITION, 490, this, 1));
			ApplyPlayerUpgrade();
			mUI->UpdateGoldText();
		}
	}
	else
	{
		mPendingAIObjects.emplace(new AxeKnight(mRenderer, getTexture("assets/AxeKnight.png", "AxeKnight"), AI_CREATE_UNIT_POSITION, 490, this, 0));
	}
}

void Game::CreateArcher(bool isPlayer)
{
	if (isPlayer)
	{
		if (mPlayerGold >= Archer::getStaticGoldCost())
		{
			mPlayerGold -= Archer::getStaticGoldCost();
			mPendingPlayerObjects.emplace(new Archer(mRenderer, getTexture("assets/Archer.png", "Archer"), PLAYER_CREATE_UNIT_POSITION, 490, this, 1));
			ApplyPlayerUpgrade();
			mUI->UpdateGoldText();
		}
	}
	else
	{
		mPendingAIObjects.emplace(new Archer(mRenderer, getTexture("assets/Archer.png", "Archer"), AI_CREATE_UNIT_POSITION, 490, this, 0));
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

SDL_Texture* Game::getTexture(std::string path, std::string name)
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
	bool ChangedVector = false;
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
			delete i;
		}
		mDeadObjects.clear();
		ChangedVector = true;
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
			mPendingPlayerObjects.pop();
			mObjects.emplace_back(aux);
			ChangedVector = true;
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
			ChangedVector = true;
		}
	}
	if (SDL_GetTicks() - mTimeSeconds > 6000)
	{
		mTimeSeconds = SDL_GetTicks();
		mAI->Act();
	}
	if (ChangedVector)
	{
		std::sort(mObjects.begin(), mObjects.end(), [](const GameObject* a, const GameObject* b) {
			return a->getX() < b->getX();
			});
	}
}

void Game::Render()
{
	SDL_RenderClear(mRenderer);
	BG->Draw();
	for (auto& i : mObjects)
	{
		i->Draw();
	}
	mUI->Draw();
	SDL_RenderPresent(mRenderer);
}
