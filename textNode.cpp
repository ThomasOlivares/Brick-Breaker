#include "textNode.hpp"
#include "utility.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>
    
TextNode::TextNode(const std::string& text)
{
	// Load it from a file
	if (!mFont.loadFromFile("Sansation.ttf"))
	{
    	printf("Error while loading font\n");
    	exit(EXIT_FAILURE);
	}

	mText.setPosition(20, 380);
	mText.setFont(mFont);
	mText.setCharacterSize(20);
	mText.setStyle(sf::Text::Bold);
	mText.setColor(sf::Color::Red);
	setString(text);
	centerOrigin(mText);
}

void TextNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mText, getTransform());
}

void TextNode::setString(const std::string& text)
{
	mText.setString(text);
}