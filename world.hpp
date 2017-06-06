#pragma once

#include "ball.hpp"
#include "brick.hpp"
#include "platform.hpp"
#include "textNode.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/View.hpp>

#include <vector>

#define thickness 10

#define BRICK_VALUE 10

class World{

	public :
							World(sf::RenderTarget& outputTarget);
		int 				update(sf::Time dt, double mvt);
		void 				draw() const;
		void 				drawImputs() const;
		bool 				rebound();
		bool 				checkDestroyedBricks();
		void 				checkPlatform();
		void 				reboundOnCorner(sf::FloatRect brickRect);
		sf::Vector2f 		getCorner(sf::FloatRect brickRect);
		bool 				checkCorners();
		std::vector<double> 	getImputs() const;

	private :
		TextNode 							text;
		sf::RenderTarget&					mTarget;
		sf::FloatRect						bounds;
		sf::RectangleShape 					rectangle;
		sf::View							mWorldView;
		Ball 								ball;
		Platform							platform;
		std::vector<Brick>					bricks;
		float 								mScore;
		sf::Time 							mTime;
};	