#include "AxeKnight.h"
#include "../Game.h"

AxeKnight::AxeKnight(SDL_Renderer* renderer, int x, int y, Game* game, bool isPlayer)
{
	mRenderer = renderer;
	mDestR = { x, y, 32, 32 };
	mCollisionR = { x, y, 32, 32 };
	//mSrcR = { 170, 0, 1026, 597 };
	mX = x;
	mY = y;
	mGame = game;
	mIsPlayer = isPlayer;
	mHP = MAX_HP;
	mReloadCount = 0;
	mPercentHPBar = 1.0f;
	mArmor = 0;
	mDamage = 80;
	mCurrentFrame = 0;
	mFrameCount = 0;
	eState = WALKING;
	LoadAnimations();
}

void AxeKnight::Update(float deltaTime)
{
	if (mHP <= 0)
	{
		mGame->RemoveObject(this);
	}
	GameObject* res = mGame->CollisionDetection(this);
	if (res == nullptr)
	{
		if (mIsPlayer)
		{
			mX = mX + 1;
		}
		else
		{
			mX = mX - 1;
		}
		mDestR.x = mX;
		mCollisionR.x = mX;
		eLastFrameState = eState;
		eState = WALKING;
	}
	else
	{
		if ((res->getIsPlayer() && !mIsPlayer) || (mIsPlayer && !res->getIsPlayer()))
		{
			eLastFrameState = eState;
			eState = ATTACKING;
			Attack(res);
		}
	}
	mReloadCount--;
}

void AxeKnight::Draw()
{
	if (eState == ATTACKING)
	{
		mDestR.w = 77;
		if (eState != eLastFrameState)
		{
			mFrameCount = 0;
			mCurrentFrame = 0;
		}
		if (!mIsPlayer)
		{
			mDestR.x = mX - 25;
			SDL_RenderCopyEx(mRenderer, mAttackingAnimVec.at(mCurrentFrame), NULL, &mDestR, 0, nullptr, SDL_FLIP_HORIZONTAL);
		}
		else
		{
			mDestR.x = mX - 15;
			SDL_RenderCopy(mRenderer, mAttackingAnimVec.at(mCurrentFrame), NULL, &mDestR);
		}
		mFrameCount++;
		if (mFrameCount >= 5)
		{
			mFrameCount = 0;
			mCurrentFrame++;
			if (mCurrentFrame > 7)
			{
				mCurrentFrame = 0;
			}
		}
	}
	if (eState == WALKING)
	{
		mDestR.w = 32;
		if (eState != eLastFrameState)
		{
			mFrameCount = 0;
			mCurrentFrame = 0;
		}
		if (!mIsPlayer)
		{
			SDL_RenderCopyEx(mRenderer, mWalkingAnimVec.at(mCurrentFrame), NULL, &mDestR, 0, nullptr, SDL_FLIP_HORIZONTAL);
		}
		else
		{
			SDL_RenderCopy(mRenderer, mWalkingAnimVec.at(mCurrentFrame), NULL, &mDestR);
		}
		mFrameCount++;
		if (mFrameCount >= 5)
		{
			mFrameCount = 0;
			mCurrentFrame++;
			if (mCurrentFrame > 11)
			{
				mCurrentFrame = 0;
			}
		}
	}
	float temp = mHP / MAX_HP;
	RenderHPBar(mX, mY - 5, 28, 3, mPercentHPBar, { 0, 255, 0, 255 }, { 255, 0, 0, 255 });
}

void AxeKnight::Attack(GameObject* target)
{
	if (mReloadCount <= 0)
	{
		target->TakeDamage(mDamage);
		mReloadCount = ATTACK_RELOAD_TIME;
	}
}

void AxeKnight::TakeDamage(int DMG)
{
	DMG = DMG - mArmor;
	if (DMG <= 0)
	{
		mHP -= 1;
	}
	else
	{
		mHP -= DMG;
	}
	mPercentHPBar = (float)mHP / (float)MAX_HP;
}

void AxeKnight::LoadAnimations()
{
	mWalkingAnimVec.emplace_back(mGame->getTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_00.png", "GreekWalk0"));
	mWalkingAnimVec.emplace_back(mGame->getTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_01.png", "GreekWalk1"));
	mWalkingAnimVec.emplace_back(mGame->getTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_02.png", "GreekWalk2"));
	mWalkingAnimVec.emplace_back(mGame->getTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_03.png", "GreekWalk3"));
	mWalkingAnimVec.emplace_back(mGame->getTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_04.png", "GreekWalk4"));
	mWalkingAnimVec.emplace_back(mGame->getTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_05.png", "GreekWalk5"));
	mWalkingAnimVec.emplace_back(mGame->getTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_06.png", "GreekWalk6"));
	mWalkingAnimVec.emplace_back(mGame->getTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_07.png", "GreekWalk7"));
	mWalkingAnimVec.emplace_back(mGame->getTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_08.png", "GreekWalk8"));
	mWalkingAnimVec.emplace_back(mGame->getTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_09.png", "GreekWalk9"));
	mWalkingAnimVec.emplace_back(mGame->getTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_10.png", "GreekWalk10"));
	mWalkingAnimVec.emplace_back(mGame->getTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_11.png", "GreekWalk11"));

	mAttackingAnimVec.emplace_back(mGame->getTexture("assets/GreekSoldier/Attack/GreekBasic_Attack_0.png", "GreekAttack0"));
	mAttackingAnimVec.emplace_back(mGame->getTexture("assets/GreekSoldier/Attack/GreekBasic_Attack_1.png", "GreekAttack1"));
	mAttackingAnimVec.emplace_back(mGame->getTexture("assets/GreekSoldier/Attack/GreekBasic_Attack_2.png", "GreekAttack2"));
	mAttackingAnimVec.emplace_back(mGame->getTexture("assets/GreekSoldier/Attack/GreekBasic_Attack_3.png", "GreekAttack3"));
	mAttackingAnimVec.emplace_back(mGame->getTexture("assets/GreekSoldier/Attack/GreekBasic_Attack_4.png", "GreekAttack4"));
	mAttackingAnimVec.emplace_back(mGame->getTexture("assets/GreekSoldier/Attack/GreekBasic_Attack_5.png", "GreekAttack5"));
	mAttackingAnimVec.emplace_back(mGame->getTexture("assets/GreekSoldier/Attack/GreekBasic_Attack_6.png", "GreekAttack6"));
	mAttackingAnimVec.emplace_back(mGame->getTexture("assets/GreekSoldier/Attack/GreekBasic_Attack_7.png", "GreekAttack7"));
}

void AxeKnight::RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor)
{
	Percent = Percent > 1.f ? 1.f : Percent < 0.f ? 0.f : Percent;
	SDL_Color old;
	SDL_GetRenderDrawColor(mRenderer, &old.r, &old.g, &old.g, &old.a);
	SDL_Rect bgrect = { x, y, w, h };
	SDL_SetRenderDrawColor(mRenderer, BGColor.r, BGColor.g, BGColor.b, BGColor.a);
	SDL_RenderFillRect(mRenderer, &bgrect);
	SDL_SetRenderDrawColor(mRenderer, FGColor.r, FGColor.g, FGColor.b, FGColor.a);
	int pw = (int)((float)w * Percent);
	int px = x + (w - pw);
	SDL_Rect fgrect = { px, y, pw, h };
	SDL_RenderFillRect(mRenderer, &fgrect);
	SDL_SetRenderDrawColor(mRenderer, old.r, old.g, old.b, old.a);
}
