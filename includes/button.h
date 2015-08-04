#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "details.h"

class UI;
class Button
{
	sf::RenderWindow& window;
	sf::Texture buttonSheet;
	sf::Sprite sprite;
	
public:
	int &xOrigin, &yOrigin;
	int x, y;
	int height, width;
	
	bool focus = false;
	
	bool hover = false;
	bool clicked = false;
	
	TextClass *text;
	
	UI *parent;
	
	struct Properties
	{
		bool hidden = false;
		bool disabled = false;
	} properties;
	
	int (*hoverEnterFunction)(Button *button);
	int (*hoverLeaveFunction)(Button *button);
	int (*clickDownFunction)(Button *button);
	int (*clickUpFunction)(Button *button);
	
	Button(sf::RenderWindow& window, int &xOrigin, int &yOrigin, int x, int y, int width, int height, int (*hoverEnterFunction)(Button *button), int (*hoverLeaveFunction)(Button *button), int (*clickDownFunction)(Button *button), int (*clickUpFunction)(Button *button), UI *parent);
	
	void draw();
	void setText(std::string text, int place = 9, int size = 14, sf::Color colour = sf::Color::Black);
	bool checkmouse(int mouseX, int mouseY, bool mouseStatus);
};

#endif
