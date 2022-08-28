#include "stdafx.h"
#include "MainMenyState.h"

//init fucn
void MainMenuState::initBackground()
{
	this->background.setSize(sf::Vector2f(
		static_cast<float>(this->window->getSize().x), 
		static_cast<float>(this->window->getSize().y)));

	if (!this->backgroundTexture.loadFromFile("Resource/Images/Backgrounds/menu_bg.jpg"))
	{
		throw("ERROR::MAINMENUSSTATE::COULD NOT LOAD TEXTUR");
	}
	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("fonts/STENCIL.TTF"))
	{
		throw("ERROR::MAINMENUSSTATE::COULD NOT LOAD FONT");
	}
}

void MainMenuState::initButtons()
{
		this->buttons["GAME_STATE_BTN"] = new Button(400, 500, 150, 50,
			&this->font, "New Game", 25,
			sf::Color(255, 255, 255, 200), sf::Color(255, 255, 250, 250), sf::Color(255, 255, 255, 50),
			sf::Color(70,70,70, 200), sf::Color(150, 150, 150, 250),sf::Color(20, 20, 20, 50));

		this->buttons["EXIT_STATE_BTN"] = new Button(600, 500, 150, 50,
			&this->font, "Quit", 25,
			sf::Color(255, 255, 255, 200), sf::Color(255, 255, 250, 250), sf::Color(255, 255, 255, 50),
			sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50));

		this->buttons["STATIC_BTN"] = new Button(200, 500, 150, 50,
			&this->font, "Statistic", 25,
			sf::Color(255, 255, 255, 200), sf::Color(255, 255, 250, 250), sf::Color(255, 255, 255, 50),
			sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50));
}

void MainMenuState::initStatistic()
{
	this->statistic = false;
	this->statist = new Statistics(*this->window, this->font);
}

void MainMenuState::initMusic()
{
	if (!this->music.openFromFile("Resource/Music/10-ending.ogg"))
		throw("ERROR::MAINMENUSSTATE::COULD NOT LOAD MUSIC");

	this->music.setVolume(40.f);
	this->music.setLoop(true);
	this->music.play();
}

MainMenuState::MainMenuState(sf::RenderWindow* window, 
	std::stack<State*>* states, sf::String& textInput)
	: State(window, states, textInput)
{
	this->initBackground();
	this->initFonts();
	this->initButtons();
	this->initStatistic();
	this->initMusic();
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	
}

void MainMenuState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) 
		&& this->getKeyTime()
		&& !this->statistic)
		this->endState();
}

void MainMenuState::updateButtons()
{
	//update all buttons and handls
	for (auto &it : this->buttons)
		it.second->update(this->mousPosView);

	//Quit the game
	if (this->buttons["EXIT_STATE_BTN"]->isPresssed())
		this->endState();

	//New Game
	if (this->buttons["GAME_STATE_BTN"]->isPresssed())
	{
		this->music.stop();
		this->states->push(new GameState(this->window, this->states, this->textInput));
	}

	//Statistic
	if (this->buttons["STATIC_BTN"]->isPresssed())
	{
		this->statist->staticRead();
		this->statistic = true;
	}

}

void MainMenuState::update(const float& dt)
{
	
	this->updateInput(dt);
	
	
	if (!this->statistic)
	{
		this->updateMousPos();
		this->updateButtons();
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			this->statistic = false;	
	}


}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
	this->renderButtons(*target);

	if (this->statistic) // Pause menu
	{
		this->statist->render(*target);
	}
}