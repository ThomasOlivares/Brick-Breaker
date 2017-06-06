#include "application.hpp"
#include "utility.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>

using namespace std;

const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

Application::Application()
: mWindow(sf::VideoMode(getWindowDimensions().x, getWindowDimensions().y)
	, "Brick Breaker", sf::Style::Close)
, mWorld(mWindow)
, mPlayer(3, {10, 15, 1})
, mvt(0)
{
	mWindow.setKeyRepeatEnabled(false);
	mWindow.setVerticalSyncEnabled(true);
}

void Application::handleEvent(){
		sf::Event event;
        while (mWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                mWindow.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
    			mvt = -2;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
    			mvt = 2;
			}
			else{
				mvt = 0;
			}
        }
}

bool Application::update(sf::Time dt)
{
	mPlayer.setImput({1, 1, 1});
	mPlayer.computeLayers();
	//double mvt = mPlayer.output()[0];
	return (mWorld.update(dt, mvt) == 0);
}

void Application::render()
{
	mWindow.clear();

	mWorld.draw();

	mWindow.display();
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			handleEvent();
			if(!update(TimePerFrame)){
				return;
			}
		}

		render();
	}
}
