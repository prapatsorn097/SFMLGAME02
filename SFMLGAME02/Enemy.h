#ifndef ENEMY_H
#define ENEMY_H
#include<SFML/Graphics.hpp>


class Enemy
{
private:
	sf::CircleShape shape;
	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;
	void initShape();
	void initVaribles();

public:
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();
	//Accessors
	const sf::FloatRect getBounds() const;

	//Function
	void update();
	void render(sf::RenderTarget* target);
};

#endif //!ENEMY_H