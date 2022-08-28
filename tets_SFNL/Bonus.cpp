#include "stdafx.h"
#include "Bonus.h"

Bonus::Bonus(float x, float y, sf::Texture& textureSheet)
{
	this->spawnTime.restart();
	this->spawnTimeMax = 300;
	dead = false;

	this->setPosition(x, y);
	this->createHitbpxComponent(this->sprite, 17.f, 63.f, 17.f, 17.f);
	this->creatMovementComponent(100.f, 30.f, 5.f);
	this->createAnimationComponent(textureSheet);
	this->animationComponent->addAnimation("IDLE", 0, 0, 0, 0, 0, 50, 81);
}



Bonus::~Bonus()
{
}


void Bonus::update(const float& dt)
{
	this->move(0.f, 1.f, dt);
	this->movementComponent->update(dt);
	this->hitboxComponent->update();
	this->animationComponent->setOneFrame("IDLE", 0, 0);
}
