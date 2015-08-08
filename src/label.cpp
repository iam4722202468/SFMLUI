#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include "label.h"

Label::Label(sf::RenderWindow& window, int &xOrigin, int &yOrigin, int x, int y, int width, int height, UI* parent, std::string text_, int place, int size, sf::Color colour) :
	window(window),
	xOrigin(xOrigin),
	yOrigin(yOrigin),
	x(x),
	y(y),
	width(width),
	height(height),
	parent(parent)
{
	text = new TextClass(window, width, height);
	setText(text_, place, size, colour);
}

void Label::setText(std::string text_, int place, int size, sf::Color colour)
{
	text->properties.text = text_;
	text->properties.place = place;
	text->properties.size = size;
	text->properties.colour = colour;
}

void Label::draw()
{
	text->draw(x+xOrigin, y+yOrigin);
}
