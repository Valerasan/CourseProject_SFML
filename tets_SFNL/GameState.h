#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "GameOver.h"
#include "PlayerGUI.h"
#include "Bullet.h"
#include "Plane.h"
#include "SpawnSystem.h"
#include "Bonus.h"
#include "Map.h"


class GameState :
    public State
{
private:

    sf::Font font;

    PauseMenu* pmenu;
    GameOver* gameOver;
    Player* player;
    PlayerGUI* GUI;

    Map* map;

    SpawnSystem* spawnSystem;
    std::vector <Bonus*> hpup;
    std::vector<Enemy*> activeEnemies;
    std::vector<Bullet*> bullets;
    std::vector<Bullet*> enemyBullets;
    
    bool gameOversound;

    //func
    void initFonts();
    void initAudio();
    void initTexturs();
    void initPauseMenu();
    void initGameOver();
    void initEntities();

public:

    
    GameState(sf::RenderWindow* window,
        std::stack<State*>* states, sf::String& textInput);
    virtual ~GameState();


//Fucn
    void updateInput(const float& dt);
    void updatePlayerInput(const float& dt);
    void updatePmButtons();
    void updateGameOverButtons();
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);


};


#endif

