#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Time.hpp>

class Platform : public sf::Drawable, public sf::Transformable{

	public : 
							Platform(sf::Vector2f positionInit);
		virtual void 		draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void 				update(sf::Time dt, double mvt);
		sf::FloatRect 		getBoundingRect();
		
	private :
		sf::RectangleShape 	mSprite;
		int 				maxSpeed;
};