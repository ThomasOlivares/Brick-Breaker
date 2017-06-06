#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "neuralNetwork.hpp"
#include "world.hpp"


class Application
{
	public:
								Application();
		void					run();
		

	private:
		void 					handleEvent();
		bool					update(sf::Time dt);
		void					render();


	private:
		static const sf::Time	TimePerFrame;

		sf::RenderWindow		mWindow;

		World					mWorld;
		NeuralNetwork 			mPlayer;
		double 					mvt;
};
