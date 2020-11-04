#include "Game.h"

/// Private function
void Game::initwindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800,600),"Rocket Game",sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
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

}

Game::~Game()
{
	delete this->window;
	delete this->player;
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
}

void Game::update()
{
	this->updatePollEvents();
	this->updateInput();
	
}

void Game::render()
{
	this->window->clear();

	//Draw all the stuff
	this->player->render(*this->window);

	this->window->display();
	
}
