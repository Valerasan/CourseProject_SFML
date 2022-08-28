#include "stdafx.h"
#include "PlayerGUI.h"


void PlayerGUI::initText()
{
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(30);
	this->text.setPosition(20, 20);
}

void PlayerGUI::initAniamaion()
{
	heart = new Heart[this->player->getHp()];
	for (int i = 0; i < this->player->getHp(); i++)
	{
		heart[i].animation = new AnimationComponent(heart[i].sprite, textureSheet);
		heart[i].animation->addAnimation("HEART", 2, 0, 0, 3, 0, 50, 50);
		heart[i].sprite.setPosition(50.f + (50.f * i), 500.f);
	}

}

PlayerGUI::PlayerGUI(Player* player, sf::Texture& textureSheet, sf::Font* font)
	: player(player), textureSheet(textureSheet), font(font)
{
	score = 0;
	this->initText();
	this->initAniamaion();
}

PlayerGUI::~PlayerGUI()
{
	delete[] this->heart;
}

unsigned int PlayerGUI::getScore()
{
	return score;
}

void PlayerGUI::addScore(const int socre)
{
	score += socre;
}

void PlayerGUI::lessHp()
{
	heart[this->player->getHp() - 1].death = true;
	this->player->loseHP();
}



void PlayerGUI::addHp()
{
	heart[this->player->getHp()].death = false;
	this->player->gainHP();
}

void PlayerGUI::update(const float& dt)
{
	pointsStr = "Score: " + std::to_string(score);
	this->text.setString(pointsStr);
	for (int i = 0; i < this->player->getMaxHP(); i++)
	{
		heart[i].update(dt);
	}
	
}

void PlayerGUI::render(sf::RenderTarget& target)
{
	target.draw(this->text);
	for (int i = 0; i < this->player->getMaxHP(); i++)
	{
		heart[i].render(target);
	}
}
