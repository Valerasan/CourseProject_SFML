#include "stdafx.h"
#include "Game.h"

void Game::initVarables()
{
	this->window = NULL;
	this->fullscreen = false;

	this->dt = 0.f;
}

void Game::initWindow()
{
	if (!icon.loadFromFile("Resource/Images/Backgrounds/icon.png"))
		throw("ERROR::GAME.CPP::COULD NOT LOAD ICON");

	std::ifstream ifs("Config/window.ini");
	//this->videoMods = sf::VideoMode::getFullscreenModes();

	std::string title = "None";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();

	bool fulscreen_l = false;

	unsigned framerate_limit = 120;
	bool vertical_sync = false;
	unsigned anitialasing_level = 0;


	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> fulscreen_l;
		ifs >> framerate_limit;
		ifs >> vertical_sync;
		ifs >> anitialasing_level;
	}

	ifs.close();

	this->fullscreen = fulscreen_l;
	this->window_settings.antialiasingLevel = anitialasing_level;
	if(this->fullscreen)
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, window_settings);
	else
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, window_settings);
	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync);
	this->window->setIcon(225, 225,icon.getPixelsPtr());
}

void Game::initStates()
{
	this->states.push(new MainMenuState(this->window, &this->states, this->playerInput));
}

Game::Game()
{
	this->initWindow();
	this->initStates();
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

void Game::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();


		if (this->sfEvent.type == sf::Event::TextEntered 
			&& states.top()->getOver() && playerInput.getSize() <=8)
		{
			if (this->sfEvent.text.unicode != 8 && this->sfEvent.text.unicode != 2386)
			{
				playerInput += this->sfEvent.text.unicode;
				playerText.setString(playerInput);
			}
			else if (this->sfEvent.text.unicode == 8)
			{
				playerInput.erase(playerInput.getSize() - 1, 1);
				playerText.setString(playerInput);
			}

		}
	}
}

void Game::update()
{
	this->updateSFMLEvents();
	
	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	else//App end
	{
		this->window->close();
	}

}

void Game::render()
{
	this->window->clear();
	
	//render items
	if (!this->states.empty())
	{
		this->states.top()->render(this->window);
	}
		
	
	this->window->draw(playerText);
	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}
