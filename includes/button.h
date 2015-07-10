#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

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
	
	struct Properties
	{
		bool hidden = false;
		bool disabled = false;
	} properties;
	
	int (*hoverEnterFunction)(), (*hoverLeaveFunction)(), (*clickDownFunction)(), (*clickUpFunction)();
	
	Button(sf::RenderWindow& window, int &xOrigin, int &yOrigin, int x, int y, int width, int height, int (*hoverEnterFunction)(), int (*hoverLeaveFunction)(), int (*clickDownFunction)(), int (*clickUpFunction)());
	void draw();
	void checkmouse(int mouseX, int mouseY, bool mouseStatus);
};

#endif
