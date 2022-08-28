#pragma once
#include "Entity.h"



class Bullet :
    public Entity
{
private:

    float dir_x;
    float dir_y;

public:

    bool dead;
    Bullet(float x, float y, float dir_x, float dir_y, float max_vlosity, sf::Texture& textureSheet);
    virtual ~Bullet();

    virtual void update(const float& dt);
};

