#include "stdafx.h"
#include "Map.h"

Map::Map()
{
	if (!map_texture.loadFromFile("Resource/Images/Sprits/map.png"))
		throw("ERROR::MAP::COULD NOT LOAD MAP TEXTURE");

	map_sprite[0].setTexture(map_texture);
	map_sprite[0].setPosition(0, -map_sprite[0].getGlobalBounds().height + 600);

	map_sprite[1].setTexture(map_texture);
	map_sprite[1].setPosition(0, -map_sprite[1].getGlobalBounds().height - map_sprite[0].getGlobalBounds().height);

}

Map::~Map()
{
}

void Map::update(const float& dt)
{
	if (map_sprite[0].getPosition().y > 0.0f && map_sprite[0].getPosition().y < 1.0f)
		map_sprite[1].setPosition(0.0f, map_sprite[0].getPosition().y - map_sprite[0].getGlobalBounds().height);
	if (map_sprite[1].getPosition().y > 0.0f && map_sprite[1].getPosition().y < 1.0f)
		map_sprite[0].setPosition(0.0f, map_sprite[1].getPosition().y - map_sprite[1].getGlobalBounds().height);

	map_sprite[0].move(0, map_speed * dt);
	map_sprite[1].move(0, map_speed * dt);

}

void Map::render(sf::RenderTarget& target)
{
	target.draw(map_sprite[0]);
	target.draw(map_sprite[1]);

}
