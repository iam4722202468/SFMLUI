#ifndef LABEL_H
#define LABEL_H

#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include "details.h"

class UI;

class Label
{
	public:
	
	sf::RenderWindow& window;
	
	UI *parent;
	TextClass *text;
	
	struct Properties
	{
		bool hidden = false;
	} properties;

	int &xOrigin, &yOrigin;
	int x, y;
	int width, height;
	
	void draw();
	void setText(std::string text, int place = 3, int size = 14, sf::Color colour = sf::Color::Black);
	
	Label(sf::RenderWindow& window, int &xOrigin, int &yOrigin, int x, int y, int width, int height, UI* parent, std::string text_, int place, int size, sf::Color colour);
};

#endif
