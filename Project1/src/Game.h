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
#include "Constants.h"

class Game
{
public:
	Game();
	void RunLoop();
	bool Initialize();
	void Shutdown();
	inline const std::vector<GameObject*>& GetGameObjectVector() { return mObjects; }
	GameObject* RangedAttackDetection(GameObject* gameObject, int range);
	GameObject* CollisionDetection(GameObject* gameObject);
	SDL_Texture* getTexture(int id);
	void KillObject(GameObject* target);
	void CreateKnight(bool isPlayer, bool isAdvancing);
	void CreateSpearKnight(bool isPlayer, bool isAdvancing);
	void CreateAxeKnight(bool isPlayer, bool isAdvancing);
	void CreateArcher(bool isPlayer, bool isAdvancing);
	void ClearAIQueue();
	void PlayerUpgradeArmor();
	void PlayerUpgradeAttack();
	void PlayerChangeOrder();
	void StartGame();
	void Pause();
	void Continue();
	inline int getPlayerGold() { return mPlayerGold; }
private:
	void Update();
	void Render();
	void ProcessInput();
	void ApplyPlayerUpgrade();
	void LoadData();
	SDL_Texture* getTexture(std::string path, int name);
	std::map<int, SDL_Texture*> mTextureMap;
	SDL_Renderer* mRenderer;
	SDL_Window* mWindow;
	std::vector<GameObject*> mObjects;
	std::vector<GameObject*> mDeadObjects;	//objects will be taken from mObjects into mNonCollidableObjects
	std::vector<GameObject*> mNonCollidableObjects;
	std::queue<GameObject*> mPendingPlayerObjects;
	std::queue<GameObject*> mPendingAIObjects;
	
	int mTimeSeconds = 0;
	AI* mAI;
	UI* mUI;
	bool mIsUpdatingObjects;
	bool mIsRunning;
	bool mIsMenuActive;
	int mTicksCount;

	int mPlayerArmorUpgradeCount = 0;
	int mPlayerAttackUpgradeCount = 0;

	int mClearFloorTimer = 0;
	int mKills;
	int mDeaths;
	int mPlayerGold;

	Background* BG;
};