#include "Knight.h"
#include "../Game.h"

Knight::Knight(SDL_Renderer* renderer, int x, int y, class Game* game, bool isPlayer)
{
	mIsPlayer = isPlayer;
	mRenderer = renderer;
	mX = x;
	mY = y;
	mDestR = { x, y, 32,  32 };
	mCollisionR = { x, y, 32, 32 };
	mSrcR = { 135, 50, 106, 186 };
	mGame = game;
	mHP = MAX_HP;
	mReloadCount = 0;
	mPercentHPBar = 1.0f;
	mArmor = 6;
	mDamage = 20;
	eState = WALKING;
	mFrameCount = 0;
	mCurrentFrame = 0;
	LoadAnimation();
}

void Knight::Update(float deltaTime)
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
			Attack(res);
			eLastFrameState = eState;
			eState = ATTACKING;
		} 
	}
	mReloadCount--;
}

void Knight::Draw()
{
	if (eState == ATTACKING)
	{
		if (eState != eLastFrameState)
		{
			mCurrentFrame = 0;
			mFrameCount = 0;
		}
		if (!mIsPlayer)
		{
			SDL_RenderCopyEx(mRenderer, mAttackingAnimVec.at(mCurrentFrame), &mSrcR, &mDestR, 0, nullptr, SDL_FLIP_HORIZONTAL);
		}
		else
		{
			SDL_RenderCopy(mRenderer, mAttackingAnimVec.at(mCurrentFrame), &mSrcR, &mDestR);
		}
		mFrameCount++;
		if (mFrameCount >= 6)
		{
			mFrameCount = 0;
			mCurrentFrame++;
			if (mCurrentFrame >= 17)
			{
				mCurrentFrame = 0;
			}
		}
	}
	if (eState == WALKING)
	{
		if (eState != eLastFrameState)
		{
			mCurrentFrame = 0;
			mFrameCount = 0;
		}
		if (!mIsPlayer)
		{
			SDL_RenderCopyEx(mRenderer, mWalkingAnimVec.at(mCurrentFrame), &mSrcR, &mDestR, 0, nullptr, SDL_FLIP_HORIZONTAL);
		}
		else
		{
			SDL_RenderCopy(mRenderer, mWalkingAnimVec.at(mCurrentFrame), &mSrcR, &mDestR);
		}
		mFrameCount++;
		if (mFrameCount >= 6)
		{
			mFrameCount = 0;
			mCurrentFrame++;
			if (mCurrentFrame >= 14)
			{
				mCurrentFrame = 0;
			}
		}
	}
	RenderHPBar(mX, mY - 5, 28, 3, mPercentHPBar, {0, 255, 0, 255}, {255, 0, 0, 255});
}

void Knight::Attack(GameObject* target)
{
	if (mReloadCount <= 0)
	{
		target->TakeDamage(mDamage);
		mReloadCount = ATTACK_RELOAD_TIME;
	}
}

void Knight::TakeDamage(int DMG)
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

void Knight::RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor)
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

void Knight::LoadAnimation()
{
	mWalkingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Walk/Tuscan_Walk_20000.png", "KnightWalk0"));
	mWalkingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Walk/Tuscan_Walk_20001.png", "KnightWalk1"));
	mWalkingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Walk/Tuscan_Walk_20002.png", "KnightWalk2"));
	mWalkingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Walk/Tuscan_Walk_20003.png", "KnightWalk3"));
	mWalkingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Walk/Tuscan_Walk_20004.png", "KnightWalk4"));
	mWalkingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Walk/Tuscan_Walk_20005.png", "KnightWalk5"));
	mWalkingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Walk/Tuscan_Walk_20006.png", "KnightWalk6"));
	mWalkingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Walk/Tuscan_Walk_20007.png", "KnightWalk7"));
	mWalkingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Walk/Tuscan_Walk_20008.png", "KnightWalk8"));
	mWalkingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Walk/Tuscan_Walk_20009.png", "KnightWalk9"));
	mWalkingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Walk/Tuscan_Walk_20010.png", "KnightWalk10"));
	mWalkingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Walk/Tuscan_Walk_20011.png", "KnightWalk11"));
	mWalkingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Walk/Tuscan_Walk_20012.png", "KnightWalk12"));
	mWalkingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Walk/Tuscan_Walk_20013.png", "KnightWalk13"));
	mWalkingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Walk/Tuscan_Walk_20014.png", "KnightWalk14"));

	mAttackingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20000.png", "KnightAttack0"));
	mAttackingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20001.png", "KnightAttack1"));
	mAttackingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20002.png", "KnightAttack2"));
	mAttackingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20003.png", "KnightAttack3"));
	mAttackingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20004.png", "KnightAttack4"));
	mAttackingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20005.png", "KnightAttack5"));
	mAttackingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20006.png", "KnightAttack6"));
	mAttackingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20007.png", "KnightAttack7"));
	mAttackingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20008.png", "KnightAttack8"));
	mAttackingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20009.png", "KnightAttack9"));
	mAttackingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20010.png", "KnightAttack10"));
	mAttackingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20011.png", "KnightAttack11"));
	mAttackingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20012.png", "KnightAttack12"));
	mAttackingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20013.png", "KnightAttack13"));
	mAttackingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20014.png", "KnightAttack14"));
	mAttackingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20015.png", "KnightAttack15"));
	mAttackingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20016.png", "KnightAttack16"));
	mAttackingAnimVec.emplace_back(mGame->getTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20017.png", "KnightAttack17"));
}
