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
	
	this->hpMax = 100;
	this->hp = this->hpMax;
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

const int & Player::getHp() const
{
	return this->hp;

}

const int & Player::getHpMax() const
{
	return this->hpMax;
}

void Player::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::setHp(const int hp)
{
	this->hp = hp;
	
}

void Player::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0)
	{ 
		this->hp = 0;
	}
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
	if (this->attackCooldown < this->attackCooldownMax)
	{
		this->attackCooldown += 0.5f;
	}
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
