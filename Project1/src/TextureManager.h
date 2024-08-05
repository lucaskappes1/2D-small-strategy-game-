#pragma once
#include <map>
#include <SDL.h>
#include <string>
#include "constants.h"

class TextureManager
{
public:
	static void LoadAllTextures(SDL_Renderer* renderer);
	static SDL_Texture* getTexture(int TextureCode);
	static void ClearTextureMap();
private:
	static void LoadSingleTexture(std::string path, int name, SDL_Renderer* renderer);
	static std::map<int, SDL_Texture*> mTextureMap;
};

