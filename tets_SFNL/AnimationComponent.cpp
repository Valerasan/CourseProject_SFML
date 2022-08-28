#include "stdafx.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet)
	:sprite(sprite), textureSheet(textureSheet)
{

}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : this->animations)
	{
		delete i.second;
	}
}

void AnimationComponent::addAnimation(const std::string key,
	float animation_timer, int start_frame_x, int start_frame_y,
	int frames_x, int frames_y, int width, int hight)
{
	this->animations[key] = new Animation(this->sprite, this->textureSheet,
		animation_timer, start_frame_x, start_frame_y,
		frames_x, frames_y, width, hight);
}


void AnimationComponent::play(const std::string key, const float& dt)
{

	this->animations[key]->play(dt);
}

void AnimationComponent::setOneFrame(const std::string key, const int frameNum_x, const int frameNum_y)
{
	this->animations[key]->setOneFrame(frameNum_x, frameNum_y);
}
