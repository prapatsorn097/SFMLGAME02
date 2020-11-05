#pragma once
#include<map>
#include"Player.h"
#include"Bullet.h"
#include"Enemy.h"
class Game
{
private:
	//window

	sf::RenderWindow* window;

	//Resorce
	std::map<std::string,sf::Texture*>textures;
	std::vector<Bullet*> bullets;

	//player
	Player* player;

	//Enemy
	Enemy* enemy;

	//Private functions
	void initwindow();
	void initTextures();
	void initPlayer();



public:
	Game();
	virtual ~Game();


	/// Functions
	void run();
	void updatePollEvents();
	void updateBullets();
	void updateInput();
	void update();
	void render();

};

