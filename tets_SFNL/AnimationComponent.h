#ifndef ANIMATIONVOMPONENT_H
#define ANIMATIONVOMPONENT_H


class AnimationComponent
{
private:
	class Animation
	{
	public:
		//variables 
		sf::Sprite& sprite;
		sf::Texture& textureSheet;
		float speed;
		float animationTimer;
		float timer;
		int width;
		int hight;
		sf::IntRect startRect;
		sf::IntRect currenRect;
		sf::IntRect endRect;

		Animation(sf::Sprite& sprite,sf::Texture& textureSheet,
			float animation_timer, int start_frame_x, int start_frame_y,
			int frames_x, int frames_y, int width, int hight)
			:sprite(sprite), textureSheet(textureSheet), speed(speed),
			 width(width), hight(hight), animationTimer(animation_timer)
		{
			this->timer = 0.f;
			this->startRect = sf::IntRect(start_frame_x * width, start_frame_y * hight, width, hight);
			this->currenRect = this->startRect;
			this->endRect = sf::IntRect(frames_x * width, frames_y * hight, width, hight);
			
			this->sprite.setTexture(this->textureSheet, true);
			this->sprite.setTextureRect(this->startRect);

		}

		void play(const float& dt)
		{
			this->timer += 10.f * dt;
			if (this->timer >= this->animationTimer)
			{
				//reset timer
				this->timer = 0.f;

				if (this->currenRect != this->endRect)
				{
					this->currenRect.left += this->width;

				}
				else
				{
					this->currenRect.left = this->startRect.left;
				}

				this->sprite.setTextureRect(this->currenRect);
			}
		}

		void resert()
		{
			this->timer = 0.f;
			this->currenRect = this->startRect;
			
		}

		void setOneFrame(const int frameNum_x, const int frameNum_y)
		{
			this->sprite.setTextureRect(sf::IntRect(frameNum_x * width, frameNum_y * hight, width, hight));
		}
	};


	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	std::map<std::string, Animation*> animations;


public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet);
	virtual ~AnimationComponent();


	//func
	void addAnimation(const std::string key,
		float animation_timer, int start_frame_x, int start_frame_y,
		int frames_x, int frames_y, int width, int hight);



	void play(const std::string key, const float& dt);
	void setOneFrame(const std::string key, const int frameNum_x, const int frameNum_y);
};

#endif