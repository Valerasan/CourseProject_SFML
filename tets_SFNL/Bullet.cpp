#include "stdafx.h"
#include "Bullet.h"



Bullet::Bullet(float x, float y, float dir_x,float dir_y, 
	float max_vlosity, sf::Texture& textureSheet) :
	dir_x(dir_x), dir_y(dir_y)
{
	
	this->creatMovementComponent(max_vlosity, 700.f,0.f);
	this->createHitbpxComponent(this->sprite, 2.f, 3.f, 9.f, 15);
	this->createAnimationComponent(textureSheet);
	this->setPosition(x, y);
	this->sprite.setScale(0.5f, 0.5f);
	this->dead = false;
	this->animationComponent->addAnimation("FIRE", 0, 0, 0, 0, 0, 24, 40);
}

Bullet::~Bullet()
{
}

void Bullet::update(const float& dt)
{
	this->movementComponent->update(dt);
	this->move(dir_x, dir_y, dt);
	this->animationComponent->setOneFrame("FIRE", 0, 0);
	this->hitboxComponent->update();
}
