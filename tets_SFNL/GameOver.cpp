#include "stdafx.h"
#include "GameOver.h"


GameOver::GameOver(sf::RenderWindow& window, sf::Font& font, sf::String& textInput)
	: font(font), textInput(textInput)
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

	//init text
	this->text.setFont(font);
	this->text.setFillColor(sf::Color(255, 255, 255, 200));
	this->text.setCharacterSize(60);
	this->text.setString("GAME OVER");
	this->text.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 20.f
	);


	this->gameOverText.setFont(font);
	this->gameOverText.setFillColor(sf::Color(255, 255, 255, 200));
	this->gameOverText.setCharacterSize(36);
	this->gameOverText.setString("Enter your name");
	this->gameOverText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 105.f
	);

	this->inputText.setFont(font);
	this->inputText.setFillColor(sf::Color(255, 255, 255, 200));
	this->inputText.setCharacterSize(60);
	this->inputText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 300.f
	);

}

GameOver::~GameOver()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

const bool GameOver::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPresssed();
}

void GameOver::addButton(const std::string key, float y, const std::string text)
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

void GameOver::update(const sf::Vector2f& mousPosition)
{
	this->inputText.setString(textInput);
	for (auto& it : this->buttons)
	{
		it.second->update(mousPosition);
	}
}

void GameOver::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);

	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

	target.draw(gameOverText);
	target.draw(text);
	target.draw(inputText);

}
