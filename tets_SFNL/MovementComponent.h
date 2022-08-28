#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H


class MovementComponent
{
private:
	sf::Sprite& sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Vector2f velocity;

public:
	MovementComponent(sf::Sprite& sprite,float maxVelocity,
		float acceleration, float deceleration);
	virtual ~MovementComponent();

	//accessors
	const sf::Vector2f& getVelocity() const;

	//func
	const bool idle() const;
	void move(const float x, const float y, const float& dt);

	void update(const float& dt);
};


#endif;

