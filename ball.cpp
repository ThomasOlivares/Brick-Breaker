#include "ball.hpp"
#include "utility.hpp"

#include <iostream>

Ball::Ball(sf::Vector2f positionInit, sf::Vector2f speedInit)
: speed(speedInit)
, absoluteSpeed(200)
, mSprite(10)
{
	setPosition(positionInit);
	mSprite.setFillColor(sf::Color(255, 255, 255));
	centerOrigin(mSprite);
}

void Ball::update(sf::Time time){
	move(time.asSeconds() * absoluteSpeed * speed);
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates state) const{
	target.draw(mSprite, getTransform());
}

void Ball::reverseSpeedX(){
	speed.x = -speed.x;
}

void Ball::reverseSpeedY(){
	speed.y = -speed.y;
}

int Ball::getRadius(){
	return 10;
}

sf::Vector2f Ball::getCenter() const{
	sf::FloatRect rect = getBoundingRect();
	return sf::Vector2f(rect.left + rect.width/2, 
						rect.top  + rect.height/2);
}

sf::Vector2f Ball::getSpeed(){
	return speed;
}

void Ball::setSpeed(sf::Vector2f newSpeed){
	speed = newSpeed;
}

sf::FloatRect Ball::getBoundingRect() const{
	return getTransform().transformRect(mSprite.getGlobalBounds());
}