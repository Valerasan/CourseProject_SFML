#ifndef MAP_H
#define MAP_H

class Map
{

private:
	sf::Sprite map_sprite[2];
	sf::Texture map_texture;
	float map_speed = 50;
	
public:
	Map();
	virtual ~Map();
	void update(const float& dt);
	void render(sf::RenderTarget& target);
	
};

#endif

