#ifndef HEALDROP_H
#define HEALDROP_H

#include <SFML/Graphics.hpp>

class HealDrop {
public:
	HealDrop();
	void Update(sf::RenderWindow& window, float elapsedTime);
	void Render(sf::RenderWindow& window);
	void SetPosition(float x, float y);
	void setActiveBool(bool active);

	bool getActiveBool() const { return m_active; }

	sf::Sprite healDropSprite;
private:
	bool m_active;			///< if this is true-> it is active
	float speed;
	static sf::Texture healDropTex;
};
#endif