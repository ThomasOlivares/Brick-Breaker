#include "platform.hpp"
#include "utility.hpp"

Platform::Platform(sf::Vector2f positionInit)
: mSprite(sf::Vector2f(50, 10))
, maxSpeed(150)
{
	setPosition(positionInit);
	mSprite.setFillColor(sf::Color(255, 255, 255));
	centerOrigin(mSprite);
}

void Platform::update(sf::Time dt, double mvt){
	sf::Vector2f mouvement(mvt, 0);
	move(dt.asSeconds() * maxSpeed * mouvement);
}

void Platform::draw(sf::RenderTarget& target, sf::RenderStates state) const{
	target.draw(mSprite, getTransform());
}

sf::FloatRect Platform::getBoundingRect(){
	return getTransform().transformRect(mSprite.getGlobalBounds());
}
