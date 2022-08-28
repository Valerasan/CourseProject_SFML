#include "stdafx.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& sprite,
	float offset_x, float offset_y, 
	float witdh, float hight) :
	sprite(sprite), offset_x(offset_x), offset_y(offset_y)
{
	this->hitbox.setPosition(this->sprite.getPosition().x + offset_x,
		this->sprite.getPosition().y + offset_y);
	this->hitbox.setSize(sf::Vector2f(witdh, hight));
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(1.f);
	this->hitbox.setOutlineColor(sf::Color::Green);


}

HitboxComponent::~HitboxComponent()
{

}

void HitboxComponent::setRotation(const float angle)
{
	this->hitbox.setRotation(angle);
}

const sf::Vector2f& HitboxComponent::getPosition() const
{
	return this->hitbox.getPosition();
}

const sf::FloatRect HitboxComponent::getGlobalBounds() const
{
	return this->hitbox.getGlobalBounds();
}

bool HitboxComponent::ckeckIntersect(const sf::FloatRect& frect)
{
	return this->hitbox.getGlobalBounds().intersects(frect);
}

void HitboxComponent::update()
{
	this->hitbox.setPosition(this->sprite.getPosition().x + this->offset_x,
		this->sprite.getPosition().y + this->offset_y);
}

void HitboxComponent::render(sf::RenderTarget& taregt)
{
	taregt.draw(this->hitbox);
}
