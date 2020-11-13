#include "HealDrop.h"


sf::Texture HealDrop::healDropTex;

HealDrop::HealDrop() {
	speed = 0.2f;
	m_active = true;

	healDropTex.loadFromFile("images/HP_Bonus.png");
	healDropTex.setSmooth(false);
	healDropSprite.setTexture(healDropTex);
	healDropSprite.setOrigin(12.5, 11.5);
}

void HealDrop::Update(sf::RenderWindow& window, float elapsedTime) {
	if (m_active) {
		float x = healDropSprite.getPosition().x;
		float y = healDropSprite.getPosition().y;

		if (y <= window.getSize().y)
			y += speed * elapsedTime;

		else
			m_active = false;

		healDropSprite.setPosition(x, y);
	}
}

void HealDrop::Render(sf::RenderWindow& window) {
	if (m_active)
		window.draw(healDropSprite);
}

void HealDrop::SetPosition(float x, float y) {
	healDropSprite.setPosition(x, y);
}
//sets the entity active or inactive
void HealDrop::setActiveBool(bool active) {
	m_active = active;
}