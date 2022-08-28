#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Bullet.h"

class Enemy :
	public Entity
{
public:
	bool dead;

	Enemy();
	virtual ~Enemy();

	virtual unsigned int getType() = 0;
	virtual void fire() = 0;
	virtual bool fireTimer() = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target, const bool show_hitbox = false) = 0;
	
};

#endif 
