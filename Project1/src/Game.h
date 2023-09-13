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
#include "units/HeavyInfantry.h"
#include "Constants.h"
#include "units/Tower1.h"
#include "units/Tower2.h"

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
	SDL_Renderer* getRenderer() { return mRenderer; }
	void KillObject(GameObject* target);
	void CreateUnit(GameObject* unit);
	void ClearAIQueue();
	void PlayerChangeOrder();
	void StartGame();
	void Pause();
	void Continue();
	void SplashDamage(int Damage, int x, int Radious);
	void AddProjectile(GameObject* projectile);
private:
	void Update();
	void Render();
	void ProcessInput();
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
	std::vector<GameObject*> mPendingProjectiles;

	class Player* mPlayer;

	int mTimeSeconds = 0;
	AI* mAI;
	UI* mUI;
	bool mIsUpdatingObjects;
	bool mIsRunning;
	bool mIsMenuActive;
	int mTicksCount;

	int mClearFloorTimer = 0;
	int mKills;
	int mDeaths;

	Background* BG;
};