#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Brick : public sf::Drawable, public sf::Transformable{

	public : 
							Brick(sf::Vector2f positionInit);
		virtual void 		draw(sf::RenderTarget& target, sf::RenderStates states) const;
		bool 				isDestroyed() const;
		sf::FloatRect 		getBoundingRect();
		void 				destroy();
		
	private :
		sf::RectangleShape 	mSprite;
		bool 				destroyed;
};