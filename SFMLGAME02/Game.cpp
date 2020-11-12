#include "Game.h"

/// Private function
void Game::initwindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800,600),"Rocket Game",sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initGUI()
{
	//Load font
	this->font.loadFromFile("font/arial.ttf");
	//init playerGUI
	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
	this->playerHpBarBack = this->playerHpBar;
	

	//Init poin text
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(30);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("test");
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

void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("images/bg.jpg"))
	{
		std::cout << "Error" << "\n";
	}
	this->worldBackground.setTexture(this->worldBackgroundTex);
}

void Game::initSystems()
{
	this->points = 0;
}



/// Con/Des
Game::Game()
{
	this->initwindow();
	this->initPlayer();
	this->initTextures();
	this->initGUI();
	this->initEnemies();
	this->initWorld();
	this->initSystems();
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
	for (auto *i : this->enemies)
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
	unsigned counter = 0;
	for (auto& bullet : this->bullets)
	{
		bullet->update();

		//เลย screen
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
		}
		counter++;
	}
	/*unsigned counter = 0;
	for (auto& bullet : this->bullets)
	{
		
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
	}*/
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
			this->player->getPos().x+this->player->getBounds().width/2.f-20.f, 
			this->player->getPos().y,
			0.f,
			-1.f,
			5.f)
		);
	}
}

void Game::updateGUI()
{
	std::stringstream ss;
	ss <<"Points: "<< this->points;
	this->pointText.setString(ss.str());
	//update player GUI
	this->player->setHp(3);
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(this->playerHpBar.getSize().x* hpPercent,this->playerHpBar.getSize().y));
}


void Game::updateEnemies()
{
	//Spawning
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{ 
		this->enemies.push_back (new Enemy(rand() % this->window->getSize().x-20.f, -100.f));
		this->spawnTimer = 0.f;
	}
	//Update
	unsigned counter = 0;
	for (auto& enemy : this->enemies)
	{
		enemy->update();

		//เลย screen
		if (enemy->getBounds().top  > this->window->getSize().y)
		{
			//delete bullet
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			--counter;
		}
		else if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			--counter;
		}
			++counter;
	}
	

}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false ; k++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				this->points += this->enemies[i]->getPoints();
				
				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				
				enemy_deleted = true;
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
	this->updateGUI();
	this->updateCombat();
	this->updateEnemies();
	this->updateCollision();
	this->updateWorld();
}

void Game::updateWorld()
{

}

void Game::updateCollision()
{
	//left world collision
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}
	//Right world collision
	else if (this->player->getBounds().left +this->player->getBounds().width>= this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x-this->player->getBounds().width, this->player->getBounds().top);
	}

	
	//Top world collision
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}
	//Bottom world collision
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left,this->window->getSize().y-this->player->getBounds().height);
	}

}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);

}

void Game::render()
{
	this->window->clear();
	//Draw world
	this->renderWorld();



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
	
	this->renderGUI();
	this->window->display();

}
