#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables()
{
	this->hitboxComponent = NULL;
	this->movementComponent = NULL;
	this->animationComponent = NULL;
	this->attributeComponent = NULL;
	offset_x = 0;
	offset_y = 0;
}

Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->hitboxComponent;
	delete this->movementComponent;
	delete this->animationComponent;
	delete this->attributeComponent;
}
//Component func
void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entity::createHitbpxComponent(sf::Sprite& sprite,
	float offset_x, float offset_y,
	float witdh, float hight)
{
	this->hitboxComponent = new HitboxComponent(sprite, 
		offset_x, offset_y,
		witdh, hight);
}

void Entity::creatMovementComponent(const float maxVelocity,
	const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite,maxVelocity, 
		acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture& textureSheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, textureSheet);
}

void Entity::createAttributeComponent(int HP)
{
	this->attributeComponent = new AttributeComponent(HP);
}

void Entity::loseHP()
{
	this->attributeComponent->loseHP();
}

void Entity::gainHP()
{
	this->attributeComponent->gainHP();
}

const int Entity::getHp() const
{
	return this->attributeComponent->hp;
}

const int Entity::getMaxHP() const
{
	return this->attributeComponent->hpMax;
}

const sf::Vector2f& Entity::getPosition() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getPosition();

	return this->sprite.getPosition();
}

const sf::FloatRect Entity::getSize() const
{
	return this->sprite.getGlobalBounds();
}


const sf::FloatRect Entity::getGlobalBounds() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getGlobalBounds();

	return this->sprite.getGlobalBounds();
}

void Entity::setPosition(const float x, const float y)
{
		this->sprite.setPosition(x, y);
}

void Entity::setRotation(const float angle)
{
	this->sprite.setRotation(angle);
	this->hitboxComponent->setRotation(angle);
}


void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	if (this->movementComponent)
	{
		this->movementComponent->move(dir_x, dir_y, dt); // Set velosity
	}
}


void Entity::render(sf::RenderTarget& target, const bool show_hitbox)
{
	target.draw(this->sprite);

	if (show_hitbox)
		this->hitboxComponent->render(target);
}

