#include "Knight.h"
#include "../Game.h"

Knight::Knight(SDL_Renderer* renderer, int x, int y, class Game* game, bool isPlayer, bool isAdvancing)
{
	mAdvancing = isAdvancing;
	mIsPlayer = isPlayer;
	mRenderer = renderer;
	mPosition = { (float)x, (float)y };
	mVelocity = isPlayer ? Vector2(60.0f, 0.0f) : Vector2(-60.0f, 0.0f);
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
		eLastFrameState = eState;
		eState = DEATH;
		mGame->KillObject(this);
		return;
	}
	GameObject* res = mGame->CollisionDetection(this);
	if (res == nullptr && mAdvancing)
	{
		mPosition += mVelocity * deltaTime;
		mDestR.x = mPosition.getIntX();
		mCollisionR.x = mPosition.getIntX();
		eLastFrameState = eState;
		eState = WALKING;
	}
	else if (res != nullptr)
	{
		if ((res->getIsPlayer() && !mIsPlayer) || (mIsPlayer && !res->getIsPlayer()))
		{
			eLastFrameState = eState;
			eState = ATTACKING;
			Attack(res);
		}
	}
	else
	{
		eLastFrameState = eState;
		eState = IDLE;
	}
	mReloadCount--;
}

void Knight::Draw()
{
	switch (eState)
	{
	case Knight::ATTACKING:
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
		RenderHPBar(mPosition.getIntX(), mPosition.getIntY() - 5, 28, 3, mPercentHPBar, { 0, 255, 0, 255 }, { 255, 0, 0, 255 });
		break;
	case Knight::WALKING:
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
		RenderHPBar(mPosition.getIntX(), mPosition.getIntY() - 5, 28, 3, mPercentHPBar, { 0, 255, 0, 255 }, { 255, 0, 0, 255 });
		break;
	case Knight::IDLE:
		if (!mIsPlayer)
		{
			SDL_RenderCopyEx(mRenderer, mIdleTexture, &mSrcR, &mDestR, 0, nullptr, SDL_FLIP_HORIZONTAL);
		}
		else
		{
			SDL_RenderCopy(mRenderer, mIdleTexture, &mSrcR, &mDestR);
		}
		RenderHPBar(mPosition.getIntX(), mPosition.getIntY() - 5, 28, 3, mPercentHPBar, { 0, 255, 0, 255 }, { 255, 0, 0, 255 });
		break;
	case Knight::DEATH:
		mSrcR.w = 223;
		mDestR.w = 50;
		if (eState != eLastFrameState)
		{
			mCurrentFrame = 0;
			mFrameCount = 0;
			eLastFrameState = eState;
		}
		if (!mIsPlayer)
		{
			mDestR.x = mPosition.getIntX() - 22;
			SDL_RenderCopyEx(mRenderer, mDeathAnimVec.at(mCurrentFrame), &mSrcR, &mDestR, 0, nullptr, SDL_FLIP_HORIZONTAL);
		}
		else
		{
			mDestR.x = mPosition.getIntX() + 10;
			SDL_RenderCopy(mRenderer, mDeathAnimVec.at(mCurrentFrame), &mSrcR, &mDestR);
		}
		mFrameCount++;
		if (mFrameCount >= 6)
		{
			mFrameCount = 0;
			mCurrentFrame++;
			if (mCurrentFrame > 15)
			{
				mCurrentFrame = 15;
			}
		}
		break;
	}
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
	mWalkingAnimVec.emplace_back(mGame->getTexture(KNIGHT_WALK0));
	mWalkingAnimVec.emplace_back(mGame->getTexture(KNIGHT_WALK1));
	mWalkingAnimVec.emplace_back(mGame->getTexture(KNIGHT_WALK2));
	mWalkingAnimVec.emplace_back(mGame->getTexture(KNIGHT_WALK3));
	mWalkingAnimVec.emplace_back(mGame->getTexture(KNIGHT_WALK4));
	mWalkingAnimVec.emplace_back(mGame->getTexture(KNIGHT_WALK5));
	mWalkingAnimVec.emplace_back(mGame->getTexture(KNIGHT_WALK6));
	mWalkingAnimVec.emplace_back(mGame->getTexture(KNIGHT_WALK7));
	mWalkingAnimVec.emplace_back(mGame->getTexture(KNIGHT_WALK8));
	mWalkingAnimVec.emplace_back(mGame->getTexture(KNIGHT_WALK9));
	mWalkingAnimVec.emplace_back(mGame->getTexture(KNIGHT_WALK10));
	mWalkingAnimVec.emplace_back(mGame->getTexture(KNIGHT_WALK11));
	mWalkingAnimVec.emplace_back(mGame->getTexture(KNIGHT_WALK12));
	mWalkingAnimVec.emplace_back(mGame->getTexture(KNIGHT_WALK13));
	mWalkingAnimVec.emplace_back(mGame->getTexture(KNIGHT_WALK14));

	mAttackingAnimVec.emplace_back(mGame->getTexture(KNIGHT_ATTACK0));
	mAttackingAnimVec.emplace_back(mGame->getTexture(KNIGHT_ATTACK1));
	mAttackingAnimVec.emplace_back(mGame->getTexture(KNIGHT_ATTACK2));
	mAttackingAnimVec.emplace_back(mGame->getTexture(KNIGHT_ATTACK3));
	mAttackingAnimVec.emplace_back(mGame->getTexture(KNIGHT_ATTACK4));
	mAttackingAnimVec.emplace_back(mGame->getTexture(KNIGHT_ATTACK5));
	mAttackingAnimVec.emplace_back(mGame->getTexture(KNIGHT_ATTACK6));
	mAttackingAnimVec.emplace_back(mGame->getTexture(KNIGHT_ATTACK7));
	mAttackingAnimVec.emplace_back(mGame->getTexture(KNIGHT_ATTACK8));
	mAttackingAnimVec.emplace_back(mGame->getTexture(KNIGHT_ATTACK9));
	mAttackingAnimVec.emplace_back(mGame->getTexture(KNIGHT_ATTACK10));
	mAttackingAnimVec.emplace_back(mGame->getTexture(KNIGHT_ATTACK11));
	mAttackingAnimVec.emplace_back(mGame->getTexture(KNIGHT_ATTACK12));
	mAttackingAnimVec.emplace_back(mGame->getTexture(KNIGHT_ATTACK13));
	mAttackingAnimVec.emplace_back(mGame->getTexture(KNIGHT_ATTACK14));
	mAttackingAnimVec.emplace_back(mGame->getTexture(KNIGHT_ATTACK15));
	mAttackingAnimVec.emplace_back(mGame->getTexture(KNIGHT_ATTACK16));
	mAttackingAnimVec.emplace_back(mGame->getTexture(KNIGHT_ATTACK17));

	mDeathAnimVec.emplace_back(mGame->getTexture(KNIGHT_DEATH0));
	mDeathAnimVec.emplace_back(mGame->getTexture(KNIGHT_DEATH1));
	mDeathAnimVec.emplace_back(mGame->getTexture(KNIGHT_DEATH2));
	mDeathAnimVec.emplace_back(mGame->getTexture(KNIGHT_DEATH3));
	mDeathAnimVec.emplace_back(mGame->getTexture(KNIGHT_DEATH4));
	mDeathAnimVec.emplace_back(mGame->getTexture(KNIGHT_DEATH5));
	mDeathAnimVec.emplace_back(mGame->getTexture(KNIGHT_DEATH6));
	mDeathAnimVec.emplace_back(mGame->getTexture(KNIGHT_DEATH7));
	mDeathAnimVec.emplace_back(mGame->getTexture(KNIGHT_DEATH8));
	mDeathAnimVec.emplace_back(mGame->getTexture(KNIGHT_DEATH9));
	mDeathAnimVec.emplace_back(mGame->getTexture(KNIGHT_DEATH10));
	mDeathAnimVec.emplace_back(mGame->getTexture(KNIGHT_DEATH11));
	mDeathAnimVec.emplace_back(mGame->getTexture(KNIGHT_DEATH12));
	mDeathAnimVec.emplace_back(mGame->getTexture(KNIGHT_DEATH13));
	mDeathAnimVec.emplace_back(mGame->getTexture(KNIGHT_DEATH14));
	mDeathAnimVec.emplace_back(mGame->getTexture(KNIGHT_DEATH15));

	mIdleTexture = mGame->getTexture(KNIGHT_IDLE);
}
