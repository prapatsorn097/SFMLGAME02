#ifndef ENEMY_H
#define ENEMY_H
#include<SFML/Graphics.hpp>


class Enemy
{
private:
	sf::CircleShape shape;
	sf::Texture shapetexture;
	//unsigned pointCount;
	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;
	void initVaribles();
	void initShape();
	
public:
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();
	//Accessors
	const sf::FloatRect getBounds() const;
	
	const int& getDamage() const;

	//Function
	void update();
	void render(sf::RenderTarget* target);
	const int& getPoints() const;
};

#endif //!ENEMY_H