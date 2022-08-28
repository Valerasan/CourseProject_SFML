#ifndef STATE_H
#define STATE_H

#include "Player.h"

class State
{
protected:

	std::map<std::string, sf::Texture> textures;

	std::map<std::string, sf::SoundBuffer> buffer;
	std::map<std::string, sf::Sound> sounds;
	std::map<std::string, sf::Music> musics;

	std::stack<State*>* states;
	sf::RenderWindow* window;

	sf::String& textInput;


	bool quit;
	bool paused;
	bool gover;
	bool statistic;

	sf::Clock keyTime;
	sf::Int32 keyTimeMax;

	sf::Vector2i mousPosScreen;
	sf::Vector2i mousPosWindow;
	sf::Vector2f mousPosView;

	//fucntions
	void initVariables();

public:
	State(sf::RenderWindow* window, std::stack<State*>* states, sf::String& textInput);
	virtual ~State();

	const bool& getOver() const;
	const bool& getQuit() const;
	const bool& getKeyTime();

	virtual void endState();
	void pauseState();
	void unpauseSatet();

	virtual void updateMousPos();
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float & dt) = 0;
	virtual void render(sf::RenderTarget * target = NULL) = 0;
};


#endif
