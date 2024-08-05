#include "TextureManager.h"
#include <SDL_image.h>

std::map<int, SDL_Texture*> TextureManager::mTextureMap;

void TextureManager::LoadAllTextures(SDL_Renderer* renderer)
{
	LoadSingleTexture("assets/castle.png", CASTLE, renderer);
	LoadSingleTexture("assets/ArcherSkeleton/Walk/walk.png", ARCHER_WALK, renderer);
	LoadSingleTexture("assets/ArcherSkeleton/Attack/attack.png", ARCHER_ATTACK, renderer);
	LoadSingleTexture("assets/ArcherSkeleton/Idle/Separate sp/idle (1).png", ARCHER_IDLE, renderer);
	LoadSingleTexture("assets/ArcherSkeleton/Dead/dead.png", ARCHER_DEATH, renderer);
	LoadSingleTexture("assets/Background.png", BACKGROUND_TEXTURE, renderer);
	LoadSingleTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_00.png", GREEK_WALK0, renderer);
	LoadSingleTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_01.png", GREEK_WALK1, renderer);
	LoadSingleTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_02.png", GREEK_WALK2, renderer);
	LoadSingleTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_03.png", GREEK_WALK3, renderer);
	LoadSingleTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_04.png", GREEK_WALK4, renderer);
	LoadSingleTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_05.png", GREEK_WALK5, renderer);
	LoadSingleTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_06.png", GREEK_WALK6, renderer);
	LoadSingleTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_07.png", GREEK_WALK7, renderer);
	LoadSingleTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_08.png", GREEK_WALK8, renderer);
	LoadSingleTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_09.png", GREEK_WALK9, renderer);
	LoadSingleTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_10.png", GREEK_WALK10, renderer);
	LoadSingleTexture("assets/GreekSoldier/Walk/GreekBasic_Walk_11.png", GREEK_WALK11, renderer);
	LoadSingleTexture("assets/GreekSoldier/Attack/GreekBasic_Attack_0.png", GREEK_ATTACK0, renderer);
	LoadSingleTexture("assets/GreekSoldier/Attack/GreekBasic_Attack_1.png", GREEK_ATTACK1, renderer);
	LoadSingleTexture("assets/GreekSoldier/Attack/GreekBasic_Attack_2.png", GREEK_ATTACK2, renderer);
	LoadSingleTexture("assets/GreekSoldier/Attack/GreekBasic_Attack_3.png", GREEK_ATTACK3, renderer);
	LoadSingleTexture("assets/GreekSoldier/Attack/GreekBasic_Attack_4.png", GREEK_ATTACK4, renderer);
	LoadSingleTexture("assets/GreekSoldier/Attack/GreekBasic_Attack_5.png", GREEK_ATTACK5, renderer);
	LoadSingleTexture("assets/GreekSoldier/Attack/GreekBasic_Attack_6.png", GREEK_ATTACK6, renderer);
	LoadSingleTexture("assets/GreekSoldier/Attack/GreekBasic_Attack_7.png", GREEK_ATTACK7, renderer);
	LoadSingleTexture("assets/GreekSoldier/Idle/GreekBasic_Idle_00.png", GREEK_IDLE, renderer);
	LoadSingleTexture("assets/GreekSoldier/Die/GreekBasic_Die_00.png", GREEK_DEATH0, renderer);
	LoadSingleTexture("assets/GreekSoldier/Die/GreekBasic_Die_01.png", GREEK_DEATH1, renderer);
	LoadSingleTexture("assets/GreekSoldier/Die/GreekBasic_Die_02.png", GREEK_DEATH2, renderer);
	LoadSingleTexture("assets/GreekSoldier/Die/GreekBasic_Die_03.png", GREEK_DEATH3, renderer);
	LoadSingleTexture("assets/GreekSoldier/Die/GreekBasic_Die_04.png", GREEK_DEATH4, renderer);
	LoadSingleTexture("assets/GreekSoldier/Die/GreekBasic_Die_05.png", GREEK_DEATH5, renderer);
	LoadSingleTexture("assets/GreekSoldier/Die/GreekBasic_Die_06.png", GREEK_DEATH6, renderer);
	LoadSingleTexture("assets/GreekSoldier/Die/GreekBasic_Die_07.png", GREEK_DEATH7, renderer);
	LoadSingleTexture("assets/GreekSoldier/Die/GreekBasic_Die_08.png", GREEK_DEATH8, renderer);
	LoadSingleTexture("assets/GreekSoldier/Die/GreekBasic_Die_09.png", GREEK_DEATH9, renderer);
	LoadSingleTexture("assets/GreekSoldier/Die/GreekBasic_Die_10.png", GREEK_DEATH10, renderer);
	LoadSingleTexture("assets/GreekSoldier/Die/GreekBasic_Die_11.png", GREEK_DEATH11, renderer);
	LoadSingleTexture("assets/Knight/Walk/Tuscan_Walk_20000.png", KNIGHT_WALK0, renderer);
	LoadSingleTexture("assets/Knight/Walk/Tuscan_Walk_20001.png", KNIGHT_WALK1, renderer);
	LoadSingleTexture("assets/Knight/Walk/Tuscan_Walk_20002.png", KNIGHT_WALK2, renderer);
	LoadSingleTexture("assets/Knight/Walk/Tuscan_Walk_20003.png", KNIGHT_WALK3, renderer);
	LoadSingleTexture("assets/Knight/Walk/Tuscan_Walk_20004.png", KNIGHT_WALK4, renderer);
	LoadSingleTexture("assets/Knight/Walk/Tuscan_Walk_20005.png", KNIGHT_WALK5, renderer);
	LoadSingleTexture("assets/Knight/Walk/Tuscan_Walk_20006.png", KNIGHT_WALK6, renderer);
	LoadSingleTexture("assets/Knight/Walk/Tuscan_Walk_20007.png", KNIGHT_WALK7, renderer);
	LoadSingleTexture("assets/Knight/Walk/Tuscan_Walk_20008.png", KNIGHT_WALK8, renderer);
	LoadSingleTexture("assets/Knight/Walk/Tuscan_Walk_20009.png", KNIGHT_WALK9, renderer);
	LoadSingleTexture("assets/Knight/Walk/Tuscan_Walk_20010.png", KNIGHT_WALK10, renderer);
	LoadSingleTexture("assets/Knight/Walk/Tuscan_Walk_20011.png", KNIGHT_WALK11, renderer);
	LoadSingleTexture("assets/Knight/Walk/Tuscan_Walk_20012.png", KNIGHT_WALK12, renderer);
	LoadSingleTexture("assets/Knight/Walk/Tuscan_Walk_20013.png", KNIGHT_WALK13, renderer);
	LoadSingleTexture("assets/Knight/Walk/Tuscan_Walk_20014.png", KNIGHT_WALK14, renderer);
	LoadSingleTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20000.png", KNIGHT_ATTACK0, renderer);
	LoadSingleTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20001.png", KNIGHT_ATTACK1, renderer);
	LoadSingleTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20002.png", KNIGHT_ATTACK2, renderer);
	LoadSingleTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20003.png", KNIGHT_ATTACK3, renderer);
	LoadSingleTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20004.png", KNIGHT_ATTACK4, renderer);
	LoadSingleTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20005.png", KNIGHT_ATTACK5, renderer);
	LoadSingleTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20006.png", KNIGHT_ATTACK6, renderer);
	LoadSingleTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20007.png", KNIGHT_ATTACK7, renderer);
	LoadSingleTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20008.png", KNIGHT_ATTACK8, renderer);
	LoadSingleTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20009.png", KNIGHT_ATTACK9, renderer);
	LoadSingleTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20010.png", KNIGHT_ATTACK10, renderer);
	LoadSingleTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20011.png", KNIGHT_ATTACK11, renderer);
	LoadSingleTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20012.png", KNIGHT_ATTACK12, renderer);
	LoadSingleTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20013.png", KNIGHT_ATTACK13, renderer);
	LoadSingleTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20014.png", KNIGHT_ATTACK14, renderer);
	LoadSingleTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20015.png", KNIGHT_ATTACK15, renderer);
	LoadSingleTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20016.png", KNIGHT_ATTACK16, renderer);
	LoadSingleTexture("assets/Knight/Attack_01/Tuscan_Attack_01_20017.png", KNIGHT_ATTACK17, renderer);
	LoadSingleTexture("assets/Knight/Idle/Tuscan_Idle_20000.png", KNIGHT_IDLE, renderer);
	LoadSingleTexture("assets/Knight/Death/Tuscan_Death_20000.png", KNIGHT_DEATH0, renderer);
	LoadSingleTexture("assets/Knight/Death/Tuscan_Death_20001.png", KNIGHT_DEATH1, renderer);
	LoadSingleTexture("assets/Knight/Death/Tuscan_Death_20002.png", KNIGHT_DEATH2, renderer);
	LoadSingleTexture("assets/Knight/Death/Tuscan_Death_20003.png", KNIGHT_DEATH3, renderer);
	LoadSingleTexture("assets/Knight/Death/Tuscan_Death_20004.png", KNIGHT_DEATH4, renderer);
	LoadSingleTexture("assets/Knight/Death/Tuscan_Death_20005.png", KNIGHT_DEATH5, renderer);
	LoadSingleTexture("assets/Knight/Death/Tuscan_Death_20006.png", KNIGHT_DEATH6, renderer);
	LoadSingleTexture("assets/Knight/Death/Tuscan_Death_20007.png", KNIGHT_DEATH7, renderer);
	LoadSingleTexture("assets/Knight/Death/Tuscan_Death_20008.png", KNIGHT_DEATH8, renderer);
	LoadSingleTexture("assets/Knight/Death/Tuscan_Death_20009.png", KNIGHT_DEATH9, renderer);
	LoadSingleTexture("assets/Knight/Death/Tuscan_Death_20010.png", KNIGHT_DEATH10, renderer);
	LoadSingleTexture("assets/Knight/Death/Tuscan_Death_20011.png", KNIGHT_DEATH11, renderer);
	LoadSingleTexture("assets/Knight/Death/Tuscan_Death_20012.png", KNIGHT_DEATH12, renderer);
	LoadSingleTexture("assets/Knight/Death/Tuscan_Death_20013.png", KNIGHT_DEATH13, renderer);
	LoadSingleTexture("assets/Knight/Death/Tuscan_Death_20014.png", KNIGHT_DEATH14, renderer);
	LoadSingleTexture("assets/Knight/Death/Tuscan_Death_20015.png", KNIGHT_DEATH15, renderer);
	LoadSingleTexture("assets/bSpearman/_walk/bSpearman_Walk_Right_strip10.png", SPEARMAN_WALK, renderer);
	LoadSingleTexture("assets/bSpearman/_attack/bSpearman_Attack01_Right_strip8.png", SPEARKMAN_ATTACK, renderer);
	LoadSingleTexture("assets/bSpearman/bSpearman_Idle_strip8.png", SPEARMAN_IDLE, renderer);
	LoadSingleTexture("assets/bSpearman/_death/bSpearman_Die_Right_strip8.png", SPEARMAN_DEATH, renderer);
	LoadSingleTexture("assets/HeavyInfantry/HeavyInfantry.png", HEAVY_INFANTRY, renderer);
	LoadSingleTexture("assets/HeavyInfantry/HeavyInfantryButton.png", HEAVY_INFANTRY_BUTTON, renderer);
	LoadSingleTexture("assets/Knight/Idle/Tuscan_Idle_10000.png", KNIGHT_BUTTON, renderer);
	LoadSingleTexture("assets/bSpearman/Button.png", SPEARMAN_BUTTON, renderer);
	LoadSingleTexture("assets/GreekSoldier/Idle/GreekBasic_Idle_00.png", GREEK_BUTTON, renderer);
	LoadSingleTexture("assets/ArcherSkeleton/Idle/Separate sp/idle (1).png", ARCHER_BUTTON, renderer);
	LoadSingleTexture("assets/ArmorUpgrade.png", ARMOR_UPGRADE_BUTTON, renderer);
	LoadSingleTexture("assets/AttackUpgrade.png", ATTACK_UPGRADE_BUTTON, renderer);
	LoadSingleTexture("assets/Mouse.png", MOUSE_BUTTON, renderer);
	LoadSingleTexture("assets/ChangeOrder.png", CHANGE_ORDER_BUTTON, renderer);
	LoadSingleTexture("assets/Rock.png", ROCK, renderer);
	LoadSingleTexture("assets/RockUpgrade.png", ROCK_UPGRADE_BUTTON, renderer);
	LoadSingleTexture("assets/Arrow.png", ARROW, renderer);
	LoadSingleTexture("assets/tower_2.png", TOWER2, renderer);
	LoadSingleTexture("assets/tower.png", TOWER1, renderer);
	LoadSingleTexture("assets/Catapult.png", CATAPULT, renderer);
}

SDL_Texture* TextureManager::getTexture(int TextureCode)
{
	auto temp = mTextureMap.find(TextureCode);
	if (temp == mTextureMap.end())
	{
		return nullptr;
	}
	return temp->second;
}

void TextureManager::ClearTextureMap()
{
	mTextureMap.clear();
}

void TextureManager::LoadSingleTexture(std::string path, int name, SDL_Renderer* renderer)
{
	SDL_Surface* surf = IMG_Load(path.c_str());
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	mTextureMap.emplace(name, tex);
}
