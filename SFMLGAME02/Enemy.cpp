#include "Enemy.h"
#include <random>
void Enemy::initShape()
{
	this->shape.setRadius(rand()%20 + 20);
	this->shape.setPointCount(rand()%20 + 3);
	this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
}

void Enemy::initVaribles()
{
	this->type = 0;
	this->hp = 0;
	this->hpMax = 10;
	this->damage = 1;
	this->points = 5;
}

Enemy::Enemy(float pos_x,float pos_y)
{
	this->shape.setPosition(pos_x, pos_y);
	this->initVaribles();
	this->initShape();
}
Enemy::~Enemy()
{

}
//Function
void Enemy::update()
{

}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
