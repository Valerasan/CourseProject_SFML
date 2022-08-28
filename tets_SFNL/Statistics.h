#ifndef STATISTICS_H
#define STATISTICS_H


#include "Button.h"

class Statistics
{

	sf::Font& font;
	sf::Text text;
	sf::Text textStat;
	sf::RectangleShape background;
	sf::RectangleShape container;
	std::string pointsStr;
	std::map<std::string, Button*> buttons;

public:
	Statistics(sf::RenderWindow& window, sf::Font& font);
	virtual ~Statistics();


	//func
	void staticRead();
	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key, float y, const std::string text);
	void render(sf::RenderTarget& target);

};

#endif 

