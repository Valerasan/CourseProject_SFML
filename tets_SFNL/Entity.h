#ifndef ENTITY_H
#define ENTITY_H


#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "AttributeComponent.h"

class Entity
{
private:
	void initVariables();



protected:
	
	sf::Sprite sprite;
	float offset_x;
	float offset_y;

	HitboxComponent* hitboxComponent;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	AttributeComponent* attributeComponent;


public:
	Entity();
	virtual ~Entity();

	//Component func
	void setTexture(sf::Texture& texture);
	void createHitbpxComponent(sf::Sprite& sprite,
		float offset_x, float offset_y,
		float witdh, float hight);
	void creatMovementComponent(const float maxVelocity,
		const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& textureSheet);
	void createAttributeComponent(int HP);

	//Func 
	virtual void loseHP();
	virtual void gainHP();
	virtual const int getHp() const;
	virtual const int getMaxHP() const;
	virtual const sf::Vector2f& getPosition() const;
	virtual const sf::FloatRect getSize() const;
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual void setPosition(const float x, const float y);
	virtual void setRotation(const float angle);
	virtual void move(const float x, const float y, const float& d);


	virtual void update(const float& dt) = 0;;
	virtual void render(sf::RenderTarget& target, const bool show_hitbox = false);

};


#endif 




