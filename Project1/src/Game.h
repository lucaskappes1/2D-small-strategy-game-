#pragma once
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include "AI.h"
#include "Background.h"
#include "units/Castle.h"
#include "units/Knight.h"
#include "units/SpearKnight.h"
#include "UI/UI.h"
#include "units/AxeKnight.h"
#include "units/Archer.h"

class Game
{
public:
	Game();
	void RunLoop();
	bool Initialize();
	void Shutdown();
	const std::vector<GameObject*>& GetGameObjectVector() { return mObjects; }
	GameObject* RangedAttackDetection(GameObject* gameObject, int range);
	GameObject* CollisionDetection(GameObject* gameObject);
	SDL_Texture* getTexture(std::string path, std::string name);
	void RemoveObject(GameObject* target);
	void CreateKnight(bool isPlayer);
	void CreateSpearKnight(bool isPlayer);
	void CreateAxeKnight(bool isPlayer);
	void CreateArcher(bool isPlayer);
	void ClearAIQueue();
	void PlayerUpgradeArmor();
	void PlayerUpgradeAttack();
	inline int getPlayerGold() { return mPlayerGold; }
private:
	void Update();
	void Render();
	void ProcessInput();
	void ApplyPlayerUpgrade();
	
	std::map<std::string, SDL_Texture*> mTextureMap;
	SDL_Renderer* mRenderer;
	SDL_Window* mWindow;
	std::vector<GameObject*> mObjects;
	std::vector<GameObject*> mDeadObjects;
	std::queue<GameObject*> mPendingPlayerObjects;
	std::queue<GameObject*> mPendingAIObjects;
	
	int mTimeSeconds = 0;
	AI* mAI;
	UI* mUI;
	bool mIsUpdatingObjects;
	bool mIsRunning;
	int mTicksCount;

	int mPlayerArmorUpgradeCount = 0;
	int mPlayerAttackUpgradeCount = 0;

	const int WIDTH = 1024;
	const int HEIGHT = 768;
	const int PLAYER_CREATE_UNIT_POSITION = WIDTH - 934;
	const int AI_CREATE_UNIT_POSITION = WIDTH - 130;
	int mKills;
	int mDeaths;
	int mPlayerGold;

	Background* BG;
};