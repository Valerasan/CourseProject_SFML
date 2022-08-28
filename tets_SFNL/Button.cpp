#include "stdafx.h"
#include "Button.h"



Button::Button(float x, float y, float width, float hight, sf::Font* font,
	std::string text, unsigned characterSize,sf::Color textIdleColor, 
	sf::Color textHoverColor, sf::Color textActiveColor,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->butonState = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, hight));
	this->shape.setFillColor(idleColor);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(textIdleColor);
	this->text.setCharacterSize(characterSize);
	this->text.setPosition
(
		this->shape.getPosition().x +( this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width  /2.f,
		this->shape.getPosition().y +  this->text.getGlobalBounds().height / 2.f
	);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->textIdleColor = textIdleColor;
	this->textHoverColor = textHoverColor;
	this->textActiveColor = textActiveColor;

}

Button::~Button()
{

}

const bool Button::isPresssed() const
{
	if (this->butonState == BTN_ACTIV)
		return true;
	return false;
}

void Button::update(const sf::Vector2f& mousPosition)
{
	//update the boolean for hover
	 this->butonState = BTN_IDLE; 
	
	 //hover
	if (this->shape.getGlobalBounds().contains(mousPosition))
	{
		this->butonState = BTN_HOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))//activ
		{
			this->butonState = BTN_ACTIV;
		}
	}

	switch (this->butonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		break;
	case BTN_ACTIV:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		break;
	}
}

void Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}
