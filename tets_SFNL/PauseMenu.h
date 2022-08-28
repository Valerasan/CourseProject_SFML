#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "Button.h"


class PauseMenu
{
private:

	sf::Font& font;
	sf::Text menuText;
	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, Button*> buttons;


	//func
	void initBackground(sf::RenderWindow& window);
	void initText();
	


public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();

	

	//func
	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key,  float y, const std::string text);
	void update(const sf::Vector2f& mousPosition);
	void render(sf::RenderTarget& target);

};

#endif

