#pragma once
#include "Mouse.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>

class Button
{
public:
	Button(SDL_Texture* tex, SDL_Renderer* renderer, Mouse* mouse, int xpos, int ypos, SDL_Rect srcR, TTF_Font* Font);	//Texture Button constructor
	Button(SDL_Renderer* renderer, Mouse* mouse, int xpos, int ypos, TTF_Font* Font, const char* Text);	//Text Button constructor
	~Button();
	void Update();
	void Draw();
	const bool& IsSelected() const { return mIsSelected; }
	void addTooltip(const char* Tooltip);
	void Show();
	void Hide();
private:
	enum State{SHOWING, HIDDEN} eState;
	std::string* mTooltip;
	SDL_Surface* mTextSurface;
	SDL_Texture* mTextTexture;
	SDL_Texture* mTexture;
	SDL_Color mTextColor = { 255, 0, 0 };
	SDL_Renderer* mRenderer;
	SDL_Rect mDestR;
	SDL_Rect mSrcR;
	Mouse* mMouse;
	TTF_Font* mFont;
	SDL_Rect mTextRect;
	bool mIsSelected;
};