#pragma once
#include "Enemy.h"

class HeavyPlane :
    public Enemy
{
private:
    sf::Clock attackTimer;
    sf::Int32 attackTimerMax;

    std::map<std::string, sf::Texture>& textures;
    std::vector<Bullet*>& enemyBullets;

    sf::SoundBuffer buffer;
    sf::Sound fireSound;
    
    const unsigned int type = 2;

public:


    HeavyPlane(float x, float y, std::map<std::string, sf::Texture>& texture_sheet,
        std::vector<Bullet*>& enemyBullets);
    virtual ~HeavyPlane();

    unsigned int getType();
    void fire();
    bool fireTimer();
    void update(const float& dt);
    void render(sf::RenderTarget& target, const bool show_hitbox);
};

