#include "stdafx.h"
#include "Statistics.h"


Statistics::Statistics(sf::RenderWindow& window, sf::Font& font)
	: font(font)
{
	this->background.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x),
		static_cast<float>(window.getSize().y)));
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	this->container.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x) - 40.f,
		static_cast<float>(window.getSize().y) - 40.f));
	this->container.setFillColor(sf::Color(20, 20, 20, 220));
	this->container.setPosition(
		static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x / 2.f,
		static_cast<float>(window.getSize().y) / 2.f - this->container.getSize().y / 2.f);

	//init text
	this->text.setFont(font);
	this->text.setFillColor(sf::Color(255, 255, 255, 200));
	this->text.setCharacterSize(60);
	this->text.setString("STATISTIC");
	this->text.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f,
		this->container.getPosition().y);

	this->staticRead();
	
	this->textStat.setFont(font);
	this->textStat.setFillColor(sf::Color(255, 255, 255, 200));
	this->textStat.setCharacterSize(20);
	this->textStat.setPosition(
		this->container.getPosition().x + 20.f,
		this->container.getPosition().y + 80.f);



}

Statistics::~Statistics()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void Statistics::staticRead()
{
	pointsStr = "";

	std::ifstream ifs("text.txt");
	if (ifs.is_open())
	{
		std::string str = "";
		std::string str_two = "";

		while (getline(ifs, str))
		{
			pointsStr += (str + "\n");
		}

	}
	ifs.close();
	this->textStat.setString(pointsStr);
}

const bool Statistics::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPresssed();
}

void Statistics::addButton(const std::string key, float y, const std::string text)
{
	float width = 250.f;
	float hight = 50.f;
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;


	this->buttons[key] = new Button(
		x, y, width, hight,
		&this->font, text, 25,
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 250, 250), sf::Color(255, 255, 255, 50),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50));
}


void Statistics::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);

	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

	target.draw(textStat);
	target.draw(text);
}
