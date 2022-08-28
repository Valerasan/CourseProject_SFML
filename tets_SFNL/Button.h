#ifndef BUTTON_H
#define BUTTON_H


enum button_states{ BTN_IDLE = 0, BTN_HOVER, BTN_ACTIV};

class Button
{

private:
	short unsigned butonState;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textActiveColor;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;
	 


public:
	Button(float x, float y, float width, float hight, sf::Font* font,
		std::string text, unsigned characterSize, sf::Color textIdleColor,
		sf::Color textHoverColor, sf::Color textActiveColor,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	virtual ~Button();

	const bool isPresssed() const;

	//func
	void update(const sf::Vector2f& mousPosition);
	void render(sf::RenderTarget& target);
};

#endif
