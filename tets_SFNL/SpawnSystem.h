#ifndef SPAWNSYSTEM_H
#define SPAWNSYSTEM_H

#include "Plane.h"
#include "HeavyPlane.h"
#include "MiniPlane.h"
#include "Bonus.h"


enum EnemyTypes { PLANE = 1, HEAVY_PALNE, MINI_PLANE };

class SpawnSystem
{
private:
	std::map<std::string, sf::Texture>& textures;
	std::vector<Enemy*>& activeEnemies;
	std::vector <Bonus*>& hpup;
	std::vector<Bullet*>& enemyBullets;

	sf::Clock spawnEnemyTimer;
	sf::Int32 spawnEnemyTimerMax;

	sf::Clock spawnBonusTimer;
	sf::Int32 spawnBonusTimerMax;
	
	int enemyCount;
	int maxEnemy;

public:
	SpawnSystem(std::vector<Enemy*>& activeEnemies,
		std::map<std::string, sf::Texture>& textures, 
		std::vector<Bullet*>& enemyBullets,int maxEnemy,
		std::vector <Bonus*>& hpup);
	virtual ~SpawnSystem();

	//Functions
	const bool spawnTimerRestart(sf::Clock& spawnTimer, sf::Int32& spawnsTimerMax, int RandNum);
	void createRandom();
	void createRandomBonus();
	void createEnemy(const short type, const float xPos, const float yPos);

	void removeEntity(const int index);
	void removeEntity(std::vector<Enemy*>& activeEnemies);
	void removeEntity(std::vector <Bonus*>& hpup);
	void removeEntity(std::vector<Bullet*>& bullets);
};

#endif