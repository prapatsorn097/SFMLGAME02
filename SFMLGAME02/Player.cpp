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

void Player::initVaribles()
{
	this->movementSpeed = 6.f;
	this->attackCooldownMax = 10.f;
	this->attackCooldown = attackCooldownMax;
}

Player::Player()
{
	this->initTexture();
	this->initSprite();
	this->initVaribles();
	
}

Player::~Player()
{
	
	
}
const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{

	return this->sprite.getGlobalBounds();

}


void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed*dirX,this->movementSpeed*dirY);
}


const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		this->attackCooldown = 0.f;
		return true;
	}

	return false;
}

void Player::updateAttack()
{
	if(this->attackCooldown<this->attackCooldownMax)
		this->attackCooldown += 0.5f;
}
//Functions
void Player::update()
{
	this->updateAttack();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
