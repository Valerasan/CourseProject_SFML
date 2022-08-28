#include "stdafx.h"
#include "PauseMenu.h"

void PauseMenu::initBackground(sf::RenderWindow& window)
{
	this->background.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x),
		static_cast<float>(window.getSize().y)));
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	this->container.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x) / 4.f,
		static_cast<float>(window.getSize().y)));
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(
		static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x / 2.f,
		0.f);
}

void PauseMenu::initText()
{
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(60);
	this->menuText.setString("PAUSED");
	this->menuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 20.f
	);

}

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
	: font(font)
{
	this->initBackground(window);
	this->initText();

}

PauseMenu::~PauseMenu()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

const bool PauseMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPresssed();
}

void PauseMenu::addButton(const std::string key, float y, const std::string text)
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

void PauseMenu::update(const sf::Vector2f& mousPosition)
{
	for (auto &it : this->buttons)
	{
		it.second->update(mousPosition);
	}
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);

	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

	target.draw(menuText);
}
