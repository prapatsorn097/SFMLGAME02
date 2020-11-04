#pragma once

#include"Player.h"


class Game
{
private:
	sf::RenderWindow* window;
	//player
	Player* player;

	//Private functions
	void initwindow();
	void initPlayer();



public:
	Game();
	virtual ~Game();





	/// Functions
	void run();
	void updatePollEvents();
	void updateInput();
	void update();
	void render();

};

