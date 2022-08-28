#include "stdafx.h"
#include "SpawnSystem.h"

SpawnSystem::SpawnSystem(std::vector<Enemy*>& activeEnemies,
	std::map<std::string, sf::Texture>& textures,
	std::vector<Bullet*>& enemyBullets, int maxEnemy,
	std::vector <Bonus*>& hpup)
	: textures(textures), activeEnemies(activeEnemies), 
	enemyBullets(enemyBullets), maxEnemy(maxEnemy),
	hpup(hpup)
{
	enemyCount = 0;
	this->spawnEnemyTimer.restart();
	this->spawnEnemyTimerMax = 2000;

	this->spawnBonusTimer.restart();
	this->spawnBonusTimerMax = 10000;
}

SpawnSystem::~SpawnSystem()
{
}



const bool SpawnSystem::spawnTimerRestart(sf::Clock& spawnTimer, sf::Int32& spawnsTimerMax, int RandNum)
{
	if (spawnTimer.getElapsedTime().asMilliseconds() >= (spawnsTimerMax - rand() % RandNum))
	{
		spawnTimer.restart();
		return true;
	}
	return false;
}

void SpawnSystem::createRandom()
{
	if (enemyCount < maxEnemy && spawnTimerRestart(spawnEnemyTimer, spawnEnemyTimerMax, 600))
	{
		int ran = rand() % 100;
		if (ran <= 100 && ran >= 50)
			createEnemy(1, 100 + rand() % 700, -100.f);
		if (ran < 50 && ran >= 25)
			createEnemy(2, 100 + rand() % 700, -100.f);
		if (ran < 25 && ran >= 0)
			createEnemy(3, 100 + rand() % 700, -100.f);
	}

}

void SpawnSystem::createRandomBonus()
{
	if (spawnTimerRestart(spawnBonusTimer, spawnBonusTimerMax, 1000))
	{
		this->hpup.emplace_back(new Bonus(100 + rand() % 700,-20, this->textures["HP_UP"]));
	}
}

void SpawnSystem::createEnemy(const short type, const float xPos, const float yPos)
{
	switch (type)
	{
	case EnemyTypes::PLANE:
		this->activeEnemies.emplace_back(new Plane(xPos, yPos, this->textures, enemyBullets));
		enemyCount++;
		break;
	case EnemyTypes::HEAVY_PALNE:
		this->activeEnemies.emplace_back(new HeavyPlane(xPos, yPos, this->textures, enemyBullets));
		enemyCount++;
		break;
	case EnemyTypes::MINI_PLANE:
		this->activeEnemies.emplace_back(new MiniPlane(xPos, yPos, this->textures, enemyBullets));
		enemyCount++;
		break;
	default:
		std::cout << "ERROR::ENEMYSYSTEM::CREATEENEMY::TYPE DOES NOT EXIST" << "\n";
		break;
	}
}

void SpawnSystem::removeEntity(const int index)
{
	enemyCount--;
	delete this->activeEnemies[index];
	this->activeEnemies.erase(this->activeEnemies.begin() + index);
}


void SpawnSystem::removeEntity(std::vector<Enemy*>& activeEnemies)
{
	enemyCount--;
	activeEnemies.erase(remove_if(activeEnemies.begin(), activeEnemies.end(), [](const Enemy* i_enemy)
		{ return 1 == i_enemy->dead; }), activeEnemies.end());
}

void SpawnSystem::removeEntity(std::vector<Bonus*>& bonus)
{
	
	bonus.erase(remove_if(bonus.begin(), bonus.end(), [](const Bonus* i_bonus)
		{ return 1 == i_bonus->dead; }), bonus.end());
}

void SpawnSystem::removeEntity(std::vector<Bullet*>& bullets)
{
	bullets.erase(remove_if(bullets.begin(), bullets.end(), [](const Bullet* i_bullet)
		{ return 1 == i_bullet->dead; }), bullets.end());
}
