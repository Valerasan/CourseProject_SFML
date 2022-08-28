#pragma once

#include "Button.h"
class GameOver
{

private:
	sf::Font& font;
	sf::Text text;
	sf::Text gameOverText;
	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, Button*> buttons;

	sf::String& textInput;
	sf::Text inputText;

public:
	GameOver(sf::RenderWindow& window, sf::Font& font, sf::String& textInput);
	virtual ~GameOver();

	//func
	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key, float y, const std::string text);
	void update(const sf::Vector2f& mousPosition);
	void render(sf::RenderTarget& target);

};

