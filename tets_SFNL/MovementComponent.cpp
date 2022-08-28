#include "stdafx.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, 
	float maxVelocity, float acceleration, float deceleration)
	: sprite(sprite), maxVelocity(maxVelocity),
	acceleration(acceleration), deceleration(deceleration)
{

}

MovementComponent::~MovementComponent()
{

}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}


const bool MovementComponent::idle() const
{
	if (this->velocity.x == 0.f && this->velocity.y == 0.f)
		return true;
	return false;
}

//func
void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{

	//acceleration
	this->velocity.x += this->acceleration * dir_x;

	this->velocity.y += this->acceleration * dir_y;

}

void MovementComponent::update(const float& dt)
{
	//deceleration
	if (this->velocity.x > 0.f)
	{
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;

		this->velocity.x -= deceleration;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
	}
	else if (this->velocity.x < 0.f)
	{

		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;

		this->velocity.x += deceleration;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}

	if (this->velocity.y > 0.f)
	{
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;

		this->velocity.y -= deceleration;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;
	}
	else if (this->velocity.y < 0.f)
	{

		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;

		this->velocity.y += deceleration;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}
	

	//final move
	this->sprite.move(this->velocity * dt);
}
