#include "Game.h"

/// Private function
void Game::initwindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800,600),"Rocket Game",sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("images/bullet.png");
}

void Game::initPlayer()
{
	this->player = new Player();
	
	
}

void Game::initEnemies()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimerMax = this->spawnTimerMax;
}



/// Con/Des
Game::Game()
{
	this->initwindow();
	this->initPlayer();
	this->initTextures();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
	delete this->player;
	//Delete textures
	for (auto &i : this->textures)
	{
		delete i.second;
	}
	//Delete Bullet
	for (auto *i : this->bullets)
	{
		delete i;
	}
	//Delete Enemy
	for (auto* i : this->enemies)
	{
		delete i;
	}

}


/// Functions
void Game::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}

void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
	}

}

void Game::updateBullets()
{
	for (auto *bullet : this->bullets)
	{
		unsigned counter = 0;
		bullet->update();
		//Bullet culling (top of screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//Delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
			std::cout << this->bullets.size() << "\n";
		}
		++counter;
	}
}

void Game::updateInput()
{
	//Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&& this->player->canAttack())
	{
		this->bullets.push_back(
			new Bullet(
			this->textures["BULLET"],
			this->player->getPos().x+this->player->getBounds().width/2.f, 
			this->player->getPos().y,
			0.f,
			-1.f,
			5.f)
		);
	}
}

void Game::updateEnemiesAndCombat()
{
	bool enemy_removed = false;
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{ 
		this->enemies.push_back (new Enemy(rand() % this->window->getSize().x-20.f, -100.f));
		this->spawnTimer = 0.f;
	}
	for (int i=0;i<this->enemies.size();++i)
	{
		this->enemies[i]->update();

		for (size_t k = 0; k < this->bullets.size()&& !enemy_removed; k++)
		{
			if (this->bullets[k]->getBounds().intersects(this->enemies[k]->getBounds()))
			{
				this->bullets.erase(this->bullets.begin() + k);
				this->enemies.erase(this->enemies.begin() + i);
				enemy_removed = true;
			}
		}


		//Remove enemy at the bottom of the screen
		if (!enemy_removed)
		{

		
			if (this->enemies[i]->getBounds().top > this->window->getSize().y)
			{
			this->enemies.erase(this->enemies.begin() + i);
			std::cout << this->enemies.size() << "\n";
			enemy_removed = true;
			}

		}
	}

}


void Game::update()
{
	this->updatePollEvents();
	this->updateInput();
	this->updateBullets();
	this->player->update();
	this->updateEnemiesAndCombat();
}

void Game::render()
{
	this->window->clear();

	//Draw all the stuff
	this->player->render(*this->window);

	for (auto *bullet : this->bullets)
	{
		bullet->render(this->window);
	}
	
	
	
	for (auto *enemy : this->enemies)
	{
		enemy->render(this->window);
	}
	

	this->window->display();

}
