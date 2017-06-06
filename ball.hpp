#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/System/Time.hpp>

class Ball : public sf::Transformable, public sf::Drawable, private sf::NonCopyable{

	public : 
							Ball(sf::Vector2f positionInit, sf::Vector2f speedInit);
		void 				update(sf::Time time);
		virtual void 		draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void 				reverseSpeedX();
		void 				reverseSpeedY();
		int 				getRadius();
		sf::FloatRect 		getBoundingRect() const;
		sf::Vector2f 		getSpeed();
		void 				setSpeed(sf::Vector2f newSpeed);
		sf::Vector2f 		getCenter() const;

	private :
		sf::CircleShape 	mSprite;
		const float 		absoluteSpeed;
		sf::Vector2f		speed;
		sf::Vector2f 		position;

};