#ifndef MAINMENYSTATE_H
#define MAINMENYSTATE_H

#include "GameState.h"
#include "Button.h"
#include "Statistics.h"

class MainMenuState :
    public State
{

private:
        //variable 
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;
    sf::Music music;
    std::map<std::string, Button*> buttons;
    Statistics* statist;
    //func
    void initBackground();
    void initFonts();
    void initButtons();
    void initStatistic();
    void initMusic();

public:
    MainMenuState(sf::RenderWindow* window, std::stack<State*>* states, sf::String& textInput);
    virtual ~MainMenuState();

    //func
    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);

    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);
};

#endif

