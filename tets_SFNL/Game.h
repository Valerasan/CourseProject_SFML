#ifndef GAME_H
#define GAME_H

#include "MainMenyState.h"

class Game
{


private:
	//Variable
	sf::Image icon;
	sf::RenderWindow *window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;
	//std::vector<sf::VideoMode> videoMods;
	sf::ContextSettings window_settings;
	bool fullscreen;
	std::stack<State*> states;

	sf::String playerInput;
	sf::Text playerText;

	//Initialaz
	void initVarables();
	void initWindow();
	void initStates();
	

public:
	//Constru/Destruct
	Game();
	virtual ~Game();


	//update
	void updateDt();
	void updateSFMLEvents();
	void update();

	//render
	void render();

	//core
	void run();

};

#endif

