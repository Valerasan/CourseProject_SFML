#pragma once
#include "Enemy.h"
class MiniPlane :
    public Enemy
{
private:


    std::map<std::string, sf::Texture>& textures;
    std::vector<Bullet*>& enemyBullets;

    sf::SoundBuffer buffer;
    sf::Sound fireSound;

    const unsigned int type = 3;

public:


    MiniPlane(float x, float y, std::map<std::string, sf::Texture>& texture_sheet,
        std::vector<Bullet*>& enemyBullets);
    virtual ~MiniPlane();

    unsigned int getType();
    void fire();
    bool fireTimer();
    void update(const float& dt);
    void render(sf::RenderTarget& target, const bool show_hitbox);
};

