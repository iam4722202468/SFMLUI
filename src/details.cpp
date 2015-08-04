#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "details.h"

TextClass::TextClass(sf::RenderWindow& window, int parentWidth, int parentHeight, std::string text_, int size, int position) : 
	window(window),
	parentWidth(parentWidth),
	parentHeight(parentHeight)
{
	properties.text = text_;
	properties.size = size;
	
	font.loadFromFile("resources/Verdana.ttf");
	text.setFont(font);
	text.setColor(properties.colour);
}

void TextClass::draw(int x, int y)
{
	
	text.setString(properties.text);
	text.setCharacterSize(properties.size);
	
	switch(properties.place)
	{
		case 0:
			y -= 14;
		break;
		case 1:
			y += (parentHeight - 8 - text.getLocalBounds().height)/2;
		break;
		case 2:
			y += (parentHeight - 8 - text.getLocalBounds().height);
		break;
		case 3:
			x += (parentWidth - text.getLocalBounds().width)/2;
		break;
		case 4:
			x += (parentWidth - text.getLocalBounds().width)/2;
			y += (parentHeight - 8 - text.getLocalBounds().height)/2;
		break;
		case 5:
			x += (parentWidth - text.getLocalBounds().width)/2;
			y += (parentHeight - 8 - text.getLocalBounds().height);
		break;
		case 6:
			x += (parentWidth - 4 - text.getLocalBounds().width);
		break;
		case 7:
			x += (parentWidth - 4 - text.getLocalBounds().width);
			y += (parentHeight - 8 - text.getLocalBounds().height)/2;
		break;
		case 8:
			x += (parentWidth - 4 - text.getLocalBounds().width);
			y += (parentHeight - 8 - text.getLocalBounds().height);
		break;
		case 9:
			x += parentWidth + 6;
			y += (parentHeight - 8 - text.getLocalBounds().height)/2;
		break;
		case 10:
			y += (parentHeight - 8 - text.getLocalBounds().height)/2;
			x += 8;
		break;
	}
	
	text.setPosition(sf::Vector2f(x, y));
	window.draw(text);
}
