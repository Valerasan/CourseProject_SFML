#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H



class HitboxComponent
{
private:
	
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	float offset_x;
	float offset_y;

public:
	HitboxComponent(sf::Sprite& sprite,
		float offset_x, float offset_y, 
		float witdh, float hight);
	virtual ~HitboxComponent();

	//accessors
	const sf::FloatRect getGlobalBounds() const;
	const sf::Vector2f& getPosition() const;

	//func
	bool ckeckIntersect(const sf::FloatRect& frect);
	virtual void setRotation(const float angle);
	void update();
	void render(sf::RenderTarget& taregt);
};


#endif

