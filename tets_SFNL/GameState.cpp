#include "stdafx.h"
#include "GameState.h"

void GameState::initFonts()
{
	if (!this->font.loadFromFile("fonts/STENCIL.TTF"))
		throw("ERROR::MAINMENUSSTATE::COULD NOT LOAD FONT");
}

void GameState::initAudio()
{

	if (!this->buffer["FIRE"].loadFromFile("Resource/Music/machine-gun.wav"))
		throw("ERROR::GAME_STATE::COULD NOT LOAD FIRE SOUND");
	else
		this->sounds["FIRE"].setBuffer(buffer["FIRE"]);


	if (!this->buffer["BONUS"].loadFromFile("Resource/Music/bonus.wav"))
		throw("ERROR::GAME_STATE::COULD NOT LOAD BONUS SOUND");
	else
		this->sounds["BONUS"].setBuffer(buffer["BONUS"]);


	if (!this->buffer["DAMAGE"].loadFromFile("Resource/Music/damage.wav"))
		throw("ERROR::GAME_STATE::COULD NOT LOAD DAMAGE SOUND");
	else
		this->sounds["DAMAGE"].setBuffer(buffer["DAMAGE"]);


	if (!this->buffer["ED_DEATH"].loadFromFile("Resource/Music/enemy_death.wav"))
		throw("ERROR::GAME_STATE::COULD NOT LOAD ED_DEATH SOUND");
	else
		this->sounds["ED_DEATH"].setBuffer(buffer["ED_DEATH"]);

	if (!this->buffer["GAME_OVER"].loadFromFile("Resource/Music/gameover.wav"))
		throw("ERROR::GAME_STATE::COULD NOT LOAD GAME_OVER SOUND");
	else
		this->sounds["GAME_OVER"].setBuffer(buffer["GAME_OVER"]);

	if (!this->musics["GAME"].openFromFile("Resource/Music/game.ogg"))
		throw("ERROR::GAME_STATE::COULD NOT LOAD GAME MUSIC");

}

void GameState::initTexturs()
{

	if(!this->textures["PLAYER_IDLE"].loadFromFile("Resource/Images/Sprits/plane.png"))
		throw("ERROR::GAME_STATE::COULD NOT LOAD PLAYER IDLE TEXTURE");
	if (!this->textures["ENEMY_PLANE"].loadFromFile("Resource/Images/Sprits/enemy_plane.png"))
		throw("ERROR::GAME_STATE::COULD NOT LOAD FIRE TEXTURE");
	if (!this->textures["ENEMY_HEAVY_PLANE"].loadFromFile("Resource/Images/Sprits/heavy_plane.png"))
		throw("ERROR::GAME_STATE::COULD NOT LOAD ENEMY_HEAVY_PLANE TEXTURE");
	if (!this->textures["ENEMY_MINI_PLANE"].loadFromFile("Resource/Images/Sprits/mini_plane.png"))
		throw("ERROR::GAME_STATE::COULD NOT LOAD ENEMY_MINI_PLANE TEXTURE");
	if (!this->textures["HEART"].loadFromFile("Resource/Images/Sprits/heart1.png"))
		throw("ERROR::GAME_STATE::COULD NOT LOAD HERT GUI TEXTURE");
	if (!this->textures["FIRE"].loadFromFile("Resource/Images/Sprits/fire.png"))
		throw("ERROR::GAME_STATE::COULD NOT LOAD FIRE TEXTURE");
	if (!this->textures["FIRE_EN"].loadFromFile("Resource/Images/Sprits/fire_en.png"))
		throw("ERROR::GAME_STATE::COULD NOT LOAD FIRE TEXTURE");
	if (!this->textures["HP_UP"].loadFromFile("Resource/Images/Sprits/hpup.png"))
		throw("ERROR::GAME_STATE::COULD NOT LOAD FIRE TEXTURE");
}

void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);
	this->pmenu->addButton("QUIT",  200.f, "Quit");
}

void GameState::initGameOver()
{
	this->gameOver = new GameOver(*this->window, this->font, this->textInput);
	this->gameOver->addButton("RESTART", 200.f, "Restart");
	this->gameOver->addButton("QUIT", 400.f, "Quit");
}

void GameState::initEntities()
{
	this->player = new Player(200, 200, this->textures["PLAYER_IDLE"]);
	this->spawnSystem = new SpawnSystem(this->activeEnemies,
		this->textures, this->enemyBullets, 10, hpup);

}

GameState::GameState(sf::RenderWindow* window,
	std::stack<State*>* states, sf::String& textInput)
	: State(window, states, textInput)
{
	gameOversound = false;
	this->initFonts();
	this->initTexturs();
	this->initAudio();
	this->initPauseMenu();
	this->initGameOver();
	this->initEntities();

	this->GUI = new PlayerGUI(this->player,this->textures["HEART"], &this->font);
	this->map = new Map();

	musics["GAME"].setVolume(30);
	musics["GAME"].setLoop(true);
	musics["GAME"].play();
}

GameState::~GameState()
{
	
	delete this->GUI;
	delete this->pmenu;
	delete this->gameOver;
	delete this->player;
	delete this->spawnSystem;
	delete this->map;
	for (auto& it : hpup)
	{
		delete it;
	}
	for (auto& it : bullets)
	{
		delete it;
	}
	for (auto& it : enemyBullets)
	{
		delete it;
	}
	for (auto& it : activeEnemies)
	{
		delete it;
	}
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && this->getKeyTime())
	{
		if (!this->paused)
		{
			this->musics["GAME"].pause();
			this->pauseState();
		}
		else
		{
			this->musics["GAME"].play();
			this->unpauseSatet();
		}
	}
}

void GameState::updatePlayerInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))		
		this->player->move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))		
		this->player->move(0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f, dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) &&
		this->player->getAttakTimer())
	{
		sounds["FIRE"].setVolume(10.f);
		sounds["FIRE"].play();
		this->bullets.emplace_back(new Bullet(
				this->player->getPosition().x + this->player->getSize().width /2.f - 6,
				this->player->getSize().top, 0.f, -1.f,
				800, this->textures["FIRE"]));
	}	
}

void GameState::updatePmButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::updateGameOverButtons()
{
	if (this->gameOver->isButtonPressed("QUIT"))
	{
		this->endState();
		std::ofstream ofs("text.txt", std::ios::app);
		ofs << this->textInput.toAnsiString() << " - "  << this->GUI->getScore() << '\n';
		this->textInput = "";
	}
		
	if (this->gameOver->isButtonPressed("RESTART"))
	{
		this->endState();
		this->states->push(new GameState(this->window, this->states, this->textInput));
		this->gover = false;
		std::ofstream ofs("text.txt", std::ios::app);
		ofs << this->textInput.toAnsiString() << " - " << this->GUI->getScore() << '\n';
		this->textInput = "";
	}
}

void GameState::update(const float& dt)
{
	
	this->updateMousPos();
	this->updateInput(dt);
	this->GUI->update(dt);
	if (!this->paused && !this->gover)// Unpaused update
	{
		this->map->update(dt);
		
		this->spawnSystem->createRandom();
		this->spawnSystem->createRandomBonus();

		//collision and out of bounds checking player bullets
		for (auto& it : bullets)
		{
			it->update(dt);
			for (auto& ip : this->activeEnemies)
			{
				if (ip->getGlobalBounds().intersects(it->getGlobalBounds()))
				{
					ip->loseHP();
					it->dead = true;
					if (ip->getHp() <= 0)
					{
						ip->dead = true;
						sounds["ED_DEATH"].play();
						switch (ip->getType())
						{
						case(1):
							this->GUI->addScore(15);
							break;
						case(2):
							this->GUI->addScore(30);
							break;
						case(3):
							this->GUI->addScore(50);
							break;
						default:
							break;
						}
						this->spawnSystem->removeEntity(this->activeEnemies);
					}
				}
			}
			if (-20 >= it->getPosition().y)
			{
				it->dead = true;
			}
			if (it->dead)
			{
				this->spawnSystem->removeEntity(this->bullets);
			}
				
		}

		//collision and out of bounds checking enemy bullets
		for (auto& it : enemyBullets)
		{
			it->update(dt);
			if (it->getPosition().y > 800)
				it->dead = true;

			if (this->player->getGlobalBounds().intersects(it->getGlobalBounds()))
			{
				this->sounds["DAMAGE"].play();
				this->GUI->lessHp();
				it->dead = true;

				//check for player hp
				if (this->player->getHp() <= 0)
					this->gover = true;
			}

			if (it->dead)
				this->spawnSystem->removeEntity(this->enemyBullets);
		}

		//

	
		//HP and out of bounds checking enemy
		for (auto& enemy : this->activeEnemies)
		{
			enemy->fire();
			enemy->update(dt);
			if (enemy->getPosition().y > 800)
				enemy->dead = true;

			if (this->player->getGlobalBounds().intersects(enemy->getGlobalBounds())
				&& enemy->getType() == 3)
			{
				this->sounds["DAMAGE"].play();
				this->GUI->lessHp();
				enemy->dead = true;
				sounds["ED_DEATH"].play();
			}
			this->spawnSystem->removeEntity(this->activeEnemies);
		}

		//bonus sollision check
		for (auto& it : hpup)
		{
			if (it->getGlobalBounds().intersects(player->getGlobalBounds()))
			{
				this->sounds["BONUS"].play();
				this->GUI->addHp();
				it->dead = true;
				this->spawnSystem->removeEntity(hpup);
			}
				
			it->update(dt);
		}

		this->updatePlayerInput(dt);
		this->player->update(dt);

	}
	else if(this->paused && !this->gover)// Paus update
	{
		this->pmenu->update(this->mousPosView);
		this->updatePmButtons();
		
	}
	else// Game over update
	{
		this->musics["GAME"].stop();
		if (!gameOversound)
		{
			this->sounds["GAME_OVER"].play();
			gameOversound = true;
		}
		this->gameOver->update(this->mousPosView);
		this->updateGameOverButtons();
	}

}

//draw func
void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->map->render(*target);

	for (auto& it : bullets)
	{
		it->render(*target, false);
	}
	for (auto& it : enemyBullets)
	{
		it->render(*target, false);
	}

	for (auto* enemy : this->activeEnemies)
	{
		enemy->render(*target, false);
	}
	for (auto& it : hpup)
	{
		it->render(*target);
	}
	this->player->render(*target, false);
	this->GUI->render(*target);
	if (this->paused) // Pause menu
	{
		this->pmenu->render(*target);
	}
	else if(this->gover)// Game Over
	{
		this->gameOver->render(*target);
	}
}
