#include "Player.h"

void Player::initTexture()
{
	//Load a Texture from file
	if (!this->texture.loadFromFile("images/11.png"))
	{
		std::cout << "Error::Player::not load." << "\n";
	}
		
}

void Player::initSprite()
{
	//Set ther tecture to the sprite
	this->sprite.setTexture(this->texture);
	

	//Resize sprite
	this->sprite.scale(0.5f, 0.5f);

}

Player::Player()
{
	this->initTexture();
	this->initSprite();
	this->movementSpeed = 6.f;
	
}

Player::~Player()
{
	
	
}
const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}
void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed*dirX,this->movementSpeed*dirY);
}
//Functions
void Player::update()
{

}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
