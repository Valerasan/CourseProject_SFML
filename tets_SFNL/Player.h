#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player :
    public Entity
{
private:
    //variabels
    sf::Clock attackTimer;
    sf::Int32 attackTimerMax;

public:
    Player(float x, float y, sf::Texture& textureSheet);
    virtual ~Player();

    const bool& getAttakTimer();
    //func
    virtual void update(const float& dt);
};


#endif;

