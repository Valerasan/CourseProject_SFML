#ifndef PLAYERGUI_H
#define PLAYERGUI_H

#include "Player.h"
#include "AnimationComponent.h"

class PlayerGUI
{
private:
	class Heart
	{
	public:
		float timer;
		bool death;
		sf::Sprite sprite;
		AnimationComponent* animation;

		Heart()
		{
			this->animation = nullptr;
			death = false;
		}

		virtual ~Heart()
		{
			delete this->animation;
		}

		void update(const float& dt)
		{

			if (!death)
			{
				this->timer = 0.f;
				this->animation->setOneFrame("HEART", 0, 0);
			}
			else if(death)
			{
				this->timer += dt;
				if(this->timer >= 0.75)
					this->animation->setOneFrame("HEART", 4, 4);
				else
					this->animation->play("HEART", dt);
				
			}
				
		}

		void render(sf::RenderTarget& target)
		{
			target.draw(this->sprite);
		}

	};
	Player* player;
	sf::Texture textureSheet;
	Heart* heart;
	std::string pointsStr;
	sf::Font* font;
	sf::Text text;

	unsigned int score;

	void initText();
	void initAniamaion();

public:
	PlayerGUI(Player* player, sf::Texture& textureSheet, sf::Font* font );
	virtual ~PlayerGUI();

	unsigned int getScore();
	void addScore(const int socre);
	void lessHp();
	void addHp();
	void update(const float& dt);
	void render(sf::RenderTarget& target);

};

#endif;