#pragma once
#include<map>
#include"Player.h"
#include"Bullet.h"
#include"Enemy.h"
#include <vector>
#include<string>
#include<sstream>

class Game
{
private:
	//window

	sf::RenderWindow* window;

	//Resorce
	std::map<std::string,sf::Texture*>textures;
	std::vector<Bullet*> bullets;


	//GUI
	sf::Font font;
	sf::Text  pointText;

	 //World
	sf::Sprite worldBackground;
	sf::Texture worldBackgroundTex;

	//system
	unsigned points;
	sf::Text gameOvertext;

	//player
	Player* player;

	//PlayerGUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	//Enemys
	std::vector<Enemy*> enemies;
	float spawnTimer;
	float spawnTimerMax;



	//Private functions
	void initwindow();
	void initGUI();
	void initTextures();
	void initPlayer();
	void initEnemies();
	void initWorld();
	void initSystems();

public:
	Game();
	virtual ~Game();


	/// Functions
	void run();
	void updatePollEvents();
	void updateBullets();
	void updateInput();
	void updateGUI();
	void updateEnemies();
	void updateCombat();
	void update();
	void updateWorld();
	void updateCollision();
	void renderGUI();
	void renderWorld();
	void render();

};

