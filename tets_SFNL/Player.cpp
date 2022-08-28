#include "stdafx.h"
#include "Player.h"


Player::Player(float x, float y,sf::Texture& textureSheet)
{
	this->attackTimer.restart();
	this->attackTimerMax = 260;

	this->setPosition(x, y);
	this->createHitbpxComponent(this->sprite,5.f,20.f, 90.f, 65);
	this->creatMovementComponent(650.f, 30.f, 5.f);
	this->createAnimationComponent(textureSheet);
	this->createAttributeComponent(5);
	this->animationComponent->addAnimation("IDLE_LEFT", 0, 1, 0, 2, 0, 100, 85);
}

Player::~Player()
{

}

const bool& Player::getAttakTimer()
{
	if (this->attackTimer.getElapsedTime().asMilliseconds() >= this->attackTimerMax)
	{
		this->attackTimer.restart();
		return true;
	}
	return false;
}


//func
void Player::update(const float& dt)
{
	this->movementComponent->update(dt);
	if (this->sprite.getPosition().x < -20)
		this->sprite.setPosition(-20, this->sprite.getPosition().y);
	if (this->sprite.getPosition().x + this->sprite.getGlobalBounds().width > 820)
		this->sprite.setPosition(820 - this->sprite.getGlobalBounds().width, this->sprite.getPosition().y);

	if (this->sprite.getPosition().y < -10)
		this->sprite.setPosition(this->sprite.getPosition().x, -10);
	if (this->sprite.getPosition().y + this->sprite.getGlobalBounds().height > 610)
		this->sprite.setPosition(this->sprite.getPosition().x, 610 - this->sprite.getGlobalBounds().height);

	//this->animationComponent->play("IDLE_LEFT", dt);
	if(this->movementComponent->getVelocity().x > 0.f)
		this->animationComponent->setOneFrame("IDLE_LEFT", 1,0);
	else if(this->movementComponent->getVelocity().x < 0.f)
		this->animationComponent->setOneFrame("IDLE_LEFT", 2, 0);
	else
		this->animationComponent->setOneFrame("IDLE_LEFT", 0, 0);

	this->hitboxComponent->update();


}
