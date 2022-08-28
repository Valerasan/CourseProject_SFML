#include "stdafx.h"
#include "State.h"

void State::initVariables()
{
	this->quit = false;
	this->paused = false;
	this->gover = false;
	this->keyTime.restart();
	this->keyTimeMax = 250.f;
}

State::State(sf::RenderWindow* window,
	std::stack<State*>* states, sf::String& textInput) :
	window(window), states(states), 
	textInput(textInput)
{
	this->initVariables();
}

State::~State()
{

}

const bool& State::getOver() const
{
	return this->gover;
}

const bool& State::getQuit() const
{
	return this->quit;
}

const bool& State::getKeyTime()
{
	if (this->keyTime.getElapsedTime().asMilliseconds() >= this->keyTimeMax)
	{
		this->keyTime.restart();
		return true;
	}
	return false;
}

void State::endState()
{
	this->quit = true;
}

void State::pauseState()
{
	this->paused = true;
}

void State::unpauseSatet()
{
	this->paused = false;
}



void State::updateMousPos()
{
	this->mousPosScreen = sf::Mouse::getPosition();
	this->mousPosWindow = sf::Mouse::getPosition(*this->window);
	this->mousPosView = this->window->mapPixelToCoords
	(sf::Mouse::getPosition(*this->window));
}
