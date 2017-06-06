#include "world.hpp"
#include "utility.hpp"

#include <iostream>
#include <cmath>
#include <string> 

#define pi 3.14159

int noCheck = 0;

World::World(sf::RenderTarget& outputTarget)
: mTarget(outputTarget)
, mWorldView(outputTarget.getDefaultView())
, bounds(thickness 
	    ,thickness 
	    ,getWindowDimensions().x - 2*thickness
	  	,getWindowDimensions().y - 2*thickness)
, rectangle()
, ball(sf::Vector2f(getWindowDimensions().x/2, 3*getWindowDimensions().y/4)
		,sf::Vector2f(0, 1))
, platform(sf::Vector2f(bounds.width/2, bounds.height - 4*thickness))
, bricks()
, mScore(0)
, text("Score : 0")
, mTime(sf::Time::Zero)
{
	text.setPosition(40, 0);

	rectangle.setPosition(thickness, thickness);
	rectangle.setSize(sf::Vector2f(bounds.width, bounds.height));
	rectangle.setFillColor(sf::Color(0, 0, 0));

	// définit un contour orange de 10 pixels d'épaisseur
	rectangle.setOutlineThickness(10);
	rectangle.setOutlineColor(sf::Color(255, 255, 255));

	for (int j = thickness; j< getWindowDimensions().y/2; j+=10){
		for (int i = thickness; i<getWindowDimensions().x - thickness; i+=30){
			bricks.push_back(Brick(sf::Vector2f(i, j)));
		}
	}
}

int World::update(sf::Time dt, double mvt){
	
	ball.update(dt);
	platform.update(dt, mvt);
	if (rebound() == false){
		return mScore;
	}
	if(!checkDestroyedBricks()){
		checkCorners();
	}
	if (noCheck == 0){
		checkPlatform();
	}
	else{
		noCheck--;
	}
	
	mTime+=dt;
	mScore -= dt.asSeconds();
	std::string score = std::to_string((int)mScore);
	std::string time = std::to_string(60 - (int)mTime.asSeconds());
	text.setString("Score : " + score + ", Time : " + time);
	if (mTime > sf::seconds(60.f)){
		return mScore;
	}
	return 0;
}

void World::draw() const
{
	mTarget.draw(rectangle);
	ball.draw(mTarget, sf::RenderStates::Default);
	platform.draw(mTarget, sf::RenderStates::Default);
	for (auto itr = bricks.begin(); itr != bricks.end(); itr++){
		if (!itr->isDestroyed()){
			itr->draw(mTarget, sf::RenderStates::Default);
		}
	}
	text.draw(mTarget, sf::RenderStates::Default);
}

void World::drawImputs() const
{
	mTarget.draw(rectangle);
	std::vector<double> imputs = getImputs();
	int count = 0;
	for (int j = thickness; j<getWindowDimensions().y - thickness; j+=10){
		for (int i = thickness; i<getWindowDimensions().x - thickness; i+=30){
			sf::RectangleShape rectangle;
			rectangle.setPosition(i, j);
			rectangle.setSize(sf::Vector2f(30, 10));
			double power = imputs[count]*255;
			count++;
			rectangle.setFillColor(sf::Color(power, power, power));
			mTarget.draw(rectangle);
		}
	}
}

bool World::rebound(){
	int x = ball.getPosition().x;
	int y = ball.getPosition().y;
	if (x < thickness || x + 2*ball.getRadius() > getWindowDimensions().x - thickness){
		ball.reverseSpeedX();
	}
	if (y < thickness){
		ball.reverseSpeedY();
	}

	if (y + 2*ball.getRadius() > getWindowDimensions().y - thickness){
		return false;
	}

	return true;
}

bool World::checkDestroyedBricks(){
	int x = ball.getCenter().x;
	int y = ball.getCenter().y;
	sf::FloatRect rect = ball.getBoundingRect();
	for (auto itr = bricks.begin(); itr != bricks.end(); itr++){
		if (!itr->isDestroyed()){
			sf::FloatRect brickRect = itr->getBoundingRect();
			if (rect.intersects(brickRect)){
				if (x >= brickRect.left && x <= brickRect.left + brickRect.width){
					ball.reverseSpeedY();
					mScore+=BRICK_VALUE;
					itr->destroy();
					return true;
				}
				else if (y >= brickRect.top && y <= brickRect.top + brickRect.height){
					ball.reverseSpeedX();
					mScore+=BRICK_VALUE;
					itr->destroy();
					return true;
				}/*
				else{
					reboundOnCorner(brickRect);
				}*/
			}
		}
	}
}

bool World::checkCorners(){
	int x = ball.getCenter().x;
	int y = ball.getCenter().y;
	sf::FloatRect rect = ball.getBoundingRect();
	for (auto itr = bricks.begin(); itr != bricks.end(); itr++){
		if (!itr->isDestroyed()){
			sf::FloatRect brickRect = itr->getBoundingRect();
			if (rect.intersects(brickRect)){
				reboundOnCorner(brickRect);
				mScore+=BRICK_VALUE;
				itr->destroy();
				return true;
			}
		}
	}
}

void World::reboundOnCorner(sf::FloatRect brickRect){
	sf::Vector2f corner = getCorner(brickRect);
	sf::Vector2f u = ball.getCenter() - corner;
	u = unitVector(u);
	float vx = ball.getSpeed().x;
	float vy = ball.getSpeed().y;

	float alpha = acos(u.x*vx+u.y*vy);
	sf::Vector2f v(sf::Vector2f(-cos(alpha)*vy + sin(alpha)*vx, 
								-cos(alpha)*vx - sin(alpha)*vy));
	ball.setSpeed(v);
}

sf::Vector2f World::getCorner(sf::FloatRect brickRect){
	int cornerX;
	int cornerY;

	if (ball.getCenter().x < brickRect.left){
		cornerX = brickRect.left;
	}
	else if (ball.getCenter().x > brickRect.left + brickRect.width){
		cornerX = brickRect.left + brickRect.width;
	}
	else{
		printf("ErrorX\n");
		exit(EXIT_FAILURE);
	}

	if (ball.getCenter().y < brickRect.top){
		cornerY = brickRect.top;
	}
	else if (ball.getCenter().y > brickRect.top + brickRect.height){
		cornerY = brickRect.top + brickRect.height;
	}
	else{
		printf("ErrorY\n");
		exit(EXIT_FAILURE);
	}

	return sf::Vector2f(cornerX, cornerY);
}


void World::checkPlatform(){
	if (ball.getBoundingRect().intersects(platform.getBoundingRect())){
		// We compute the spreading of the ball from the center of the platform
		float x = ball.getBoundingRect().left + ball.getBoundingRect().width/2 
			- platform.getBoundingRect().left - platform.getBoundingRect().width/2;

		//Same but in proportions
		float w = platform.getBoundingRect().width;
		float p = x/w;

		float vx = ball.getSpeed().x;
		float vy = ball.getSpeed().y;
		float deviationAngle = atan2(vx, vy);

		float newAngle = deviationAngle + p*pi/4;

		float diff = newAngle - deviationAngle;

		ball.setSpeed(sf::Vector2f(vx*cos(diff)+vy*sin(diff), 
					  			   vx*sin(diff)-vy*cos(diff)));

		noCheck = 20;
	}
}

std::vector<double> World::getImputs() const{
	std::vector<double> imputs;
	for (auto itr = bricks.begin(); itr!=bricks.end(); itr++){
		imputs.push_back(itr->isDestroyed() == 0);
	}
	for (int i = 10; i<getWindowDimensions().x - thickness; i+=30){
		for (int j = getWindowDimensions().y/2; j< getWindowDimensions().y - thickness; 
				j+=10){
			imputs.push_back(0);
		}
	}
	int x = ball.getCenter().x/30;
	int y = ball.getCenter().y/10;
	imputs[y*13+x] = 1;

	x = platform.getPosition().x;
	y = platform.getPosition().y;

	return imputs;
}
