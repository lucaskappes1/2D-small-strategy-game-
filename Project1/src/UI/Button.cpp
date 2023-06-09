#include "Button.h"

Button::Button(SDL_Texture* tex, SDL_Renderer* renderer, Mouse* mouse, int xpos, int ypos, SDL_Rect srcR, TTF_Font* Font)
{
	mTexture = tex;
	mRenderer = renderer;
	mMouse = mouse;
	mDestR = { xpos, ypos, 50, 50 };
	mSrcR = srcR;
	mIsSelected = false;
	mFont = Font;
	eState = SHOWING;
}

Button::Button(SDL_Renderer* renderer, Mouse* mouse, int xpos, int ypos, TTF_Font* Font, const char* Text)
{
	mRenderer = renderer;
	mMouse = mouse;
	mDestR = { xpos, ypos, 200, 50 };
	mIsSelected = false;
	mFont = Font;
	mTextSurface = TTF_RenderText_Solid(mFont, Text, mTextColor);
	mTexture = SDL_CreateTextureFromSurface(mRenderer, mTextSurface);
	SDL_FreeSurface(mTextSurface);
	int x, y;
	SDL_QueryTexture(mTexture, nullptr, nullptr, &x, &y);
	mSrcR = { 0, 0, x, y };
	eState = SHOWING;
}

Button::~Button()
{
	delete mTooltip;
}

void Button::Update()
{
	if (SDL_HasIntersection(&mDestR, &mMouse->getCollisionRect()) && eState == SHOWING)
	{
		mIsSelected = true;
		//display text
	}
	else
	{
		mIsSelected = false;
	}
}

void Button::Draw()
{
	if (eState == SHOWING)
	{
		SDL_RenderCopy(mRenderer, mTexture, &mSrcR, &mDestR);
		if (mIsSelected)
		{
			SDL_RenderCopy(mRenderer, mTextTexture, NULL, &mTextRect);
		}
	}
}

void Button::addTooltip(const char* Tooltip)
{
	mTooltip = new std::string(Tooltip);
	mTextSurface = TTF_RenderText_Solid(mFont, mTooltip->c_str(), mTextColor);
	mTextTexture = SDL_CreateTextureFromSurface(mRenderer, mTextSurface);
	mTextRect = { 50, 150, 500, 20 };
}

void Button::Show()
{
	eState = SHOWING;
}

void Button::Hide()
{
	eState = HIDDEN;
}
