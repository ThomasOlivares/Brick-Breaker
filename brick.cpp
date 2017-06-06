#include "brick.hpp"
#include "utility.hpp"

Brick::Brick(sf::Vector2f positionInit)
: mSprite(sf::Vector2f(30, 10))
, destroyed(false)
{
	setPosition(positionInit);
	mSprite.setFillColor(sf::Color(255, 255, 255));
	centerOrigin(mSprite);
}

void Brick::draw(sf::RenderTarget& target, sf::RenderStates state) const{
	target.draw(mSprite, getTransform());
}

bool Brick::isDestroyed() const{
	return destroyed;
}

void Brick::destroy(){
	destroyed = true;
}

sf::FloatRect Brick::getBoundingRect(){
	return getTransform().transformRect(mSprite.getGlobalBounds());
}