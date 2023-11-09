#pragma once
#include <vector>

class Stage
{
public:
	Stage(class Game* game, struct SDL_Renderer* renderer, class AI* ai);
	void LoadStage1(std::vector<class GameObject*>& mObjects);
	void LoadStage2(std::vector<class GameObject*>& mObjects);
	void LoadStage3(std::vector<class GameObject*>& mObjects);
	void LoadStage4(std::vector<class GameObject*>& mObjects);
private:
	class Game* mGame;
	class AI* mAI;
	struct SDL_Renderer* mRenderer;
};

