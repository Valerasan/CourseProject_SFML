#pragma once
#include "Enemy.h"


class Plane :
    public Enemy
{

private:
    sf::Clock attackTimer;
    sf::Int32 attackTimerMax;

    std::map<std::string, sf::Texture>& textures;
    std::vector<Bullet*>& enemyBullets;

    sf::SoundBuffer buffer;
    sf::Sound fireSound;

    unsigned int type = 1;

public:


    Plane(float x, float y, std::map<std::string, sf::Texture>& texture_sheet,
        std::vector<Bullet*>& enemyBullets);
    virtual ~Plane();
    
    unsigned int getType();
    void fire();
    bool fireTimer();
    void update(const float& dt);
    void render(sf::RenderTarget& target,const bool show_hitbox);

};

