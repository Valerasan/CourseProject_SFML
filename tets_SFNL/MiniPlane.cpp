#include "stdafx.h"
#include "MiniPlane.h"

MiniPlane::MiniPlane(float x, float y, std::map<std::string, sf::Texture>& texture_sheet,
	std::vector<Bullet*>& enemyBullets) :
	textures(texture_sheet), enemyBullets(enemyBullets)
{
	buffer.loadFromFile("Resource/Music/rocket-launcher.wav");
	this->fireSound.setBuffer(buffer);
	this->fireSound.setVolume(20);

	this->creatMovementComponent(400.f, 40.f, 4.f);
	this->createHitbpxComponent(this->sprite, -5.f, -25.f, 73, 40);
	this->createAnimationComponent(this->textures["ENEMY_MINI_PLANE"]);
	this->createAttributeComponent(1);
	this->setRotation(180.f);
	this->setPosition(x, y);



	this->animationComponent->addAnimation("IDLE", 0, 0, 0, 0, 0, 83, 66);
}

MiniPlane::~MiniPlane()
{
}

unsigned int MiniPlane::getType()
{
	return type;
}

void MiniPlane::fire(){}

bool MiniPlane::fireTimer()
{
	return false;
}

void MiniPlane::update(const float& dt)
{
	this->move(0.f, 1.f, dt);
	this->movementComponent->update(dt);
	this->animationComponent->setOneFrame("IDLE", 0, 0);

	this->hitboxComponent->update();
}

void MiniPlane::render(sf::RenderTarget& target, const bool show_hitbox)
{
	target.draw(this->sprite);

	if (show_hitbox)
		this->hitboxComponent->render(target);
}
