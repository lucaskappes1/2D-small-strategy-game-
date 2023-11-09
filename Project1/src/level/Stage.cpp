#include "Stage.h"
#include "../Game.h"
#include "../units/Archer.h"
#include "../units/AxeKnight.h"
#include "../units/Castle.h"
#include "../units/HeavyInfantry.h"
#include "../units/Knight.h"
#include "../units/SpearKnight.h"
#include "../units/Tower1.h"
#include "../units/Tower2.h"
#include "../Constants.h"
#include "../AI.h"

Stage::Stage(Game* game, SDL_Renderer* renderer, AI* ai) : mAI (ai),
mGame(game), 
mRenderer(renderer)
{
}

void Stage::LoadStage1(std::vector<class GameObject*>& mObjects)
{
	if (mObjects.size() > 0)
	{
		for (auto i : mObjects)
		{
			delete i;
		}
		mObjects.clear();
	}
	mObjects.emplace_back(new Castle(mRenderer, PLAYER_CASTLE_POSITION, HEIGHT - 175, mGame, 1));
	mObjects.emplace_back(new Castle(mRenderer, AI_CASTLE_POSITION, HEIGHT - 175, mGame, 0));
}

void Stage::LoadStage2(std::vector<class GameObject*>& mObjects)
{
	if (mObjects.size() > 0)
	{
		for (auto i : mObjects)
		{
			delete i;
		}
		mObjects.clear();
	}
	mObjects.emplace_back(new Castle(mRenderer, PLAYER_CASTLE_POSITION, HEIGHT - 175, mGame, 1));
	mObjects.emplace_back(new Castle(mRenderer, AI_CASTLE_POSITION, HEIGHT - 175, mGame, 0));
	mAI->CreateTower1();
	mAI->CreateTower1();
}

void Stage::LoadStage3(std::vector<class GameObject*>& mObjects)
{
	if (mObjects.size() > 0)
	{
		for (auto i : mObjects)
		{
			delete i;
		}
		mObjects.clear();
	}
	mObjects.emplace_back(new Castle(mRenderer, PLAYER_CASTLE_POSITION, HEIGHT - 175, mGame, 1));
	mObjects.emplace_back(new Castle(mRenderer, AI_CASTLE_POSITION, HEIGHT - 175, mGame, 0));
	mAI->CreateTower2();
	mAI->CreateTower1();
	mAI->CreateTower1();
}

void Stage::LoadStage4(std::vector<class GameObject*>& mObjects)
{
	if (mObjects.size() > 0)
	{
		for (auto i : mObjects)
		{
			delete i;
		}
		mObjects.clear();
	}
	mObjects.emplace_back(new Castle(mRenderer, PLAYER_CASTLE_POSITION, HEIGHT - 175, mGame, 1));
	mObjects.emplace_back(new Castle(mRenderer, AI_CASTLE_POSITION, HEIGHT - 175, mGame, 0));
	mAI->CreateTower2();
	mAI->CreateTower2();
	mAI->CreateTower2();
}
