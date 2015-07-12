#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class UI;
class Button
{
	sf::RenderWindow& window;
	sf::Texture buttonSheet;
	
public:
	int &xOrigin, &yOrigin;
	int x, y;
	int height, width;
	
	bool hover = false;
	bool clicked = false;
	
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
	void checkmouse(int mouseX, int mouseY, bool mouseStatus);
};

#endif
