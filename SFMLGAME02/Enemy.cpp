#include "Enemy.h"
#include <random>


void Enemy::initVaribles()
{
	//this->pointCount = rand() %8 + 3;//min=3 max=10
	this->type = 0;
	this->hp = this->hpMax;
	this->hpMax = 100;
	this->speed = 5;
	this->damage = 10;
	this->points = 5;
	
}

void Enemy::initShape()
{
	if (!this->shapetexture.loadFromFile("images/Meteor01.png"))
	{
		printf("Load Fail");
	}
	this->shape.setTexture(&shapetexture);

	this->shape.setRadius(50.f);
	//this->shape.setPointCount(this->pointCount);

	this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1)); //แรนด้อมสี
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
//Accessors
const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return this->points;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

//Function
void Enemy::update()
{
	this->shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}