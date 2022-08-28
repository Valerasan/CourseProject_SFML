#ifndef BONUS_H
#define BONUS_H

#include "Entity.h"
class Bonus :
    public Entity
{
private:
    //variabels
    sf::Clock spawnTime;
    sf::Int32 spawnTimeMax;


public:
    bool dead;

    Bonus(float x, float y, sf::Texture& textureSheet);
    virtual ~Bonus();

    //func
    virtual void update(const float& dt);
};

#endif




