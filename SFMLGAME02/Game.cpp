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



/// Con/Des
Game::Game()
{
	this->initwindow();
	this->initPlayer();
	this->initTextures();
}

Game::~Game()
{
	delete this->window;
	delete this->player;
	//Delet textures
	for (auto &i : this->textures)
	{
		delete i.second;
	}
	for (auto* i : this->bullets)
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

void Game::updateBullet()
{
	for (auto* bullet : this->bullets)
	{
		bullet->update();
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
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->bullets.push_back(new Bullet(this->textures["BULLET"],this->player->getPos().x, this->player->getPos().y,0.f,0.f,0.f));
	}
}


void Game::update()
{
	this->updatePollEvents();
	this->updateInput();
	this->updateBullet();
	
}

void Game::render()
{
	this->window->clear();

	//Draw all the stuff
	this->player->render(*this->window);

	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}
	this->window->display();
	
}
