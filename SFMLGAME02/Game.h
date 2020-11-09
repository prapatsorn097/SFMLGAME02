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

	//Enemys
	std::vector<Enemy*> enemies;
	float spawnTimer;
	float spawnTimerMax;

	//Private functions
	void initwindow();
	void initTextures();
	void initPlayer();
	void initEnemies();


public:
	Game();
	virtual ~Game();


	/// Functions
	void run();
	void updatePollEvents();
	void updateBullets();
	void updateInput();
	void updateEnemiesAndCombat();
	void update();
	void render();

};

