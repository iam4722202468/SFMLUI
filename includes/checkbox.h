#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

class UI;
class Checkbox
{
	sf::RenderWindow& window;
	sf::Texture checkboxSheet;
	
	public:
	int &xOrigin, &yOrigin;
	int x, y;
	int height, width;
	
	UI *parent;
	
	bool hover = false;
	bool clicked = false;
	
	bool checked = false;
	
	struct Properties
	{
		bool hidden = false;
		bool disabled = false;
	} properties;
	
	int (*hoverEnterFunction)(), (*hoverLeaveFunction)(), (*clickDownFunction)(), (*clickUpFunction)();
	
	Checkbox(sf::RenderWindow& window, int &xOrigin, int &yOrigin, int x, int y, int width, int height, int (*hoverEnterFunction)(), int (*hoverLeaveFunction)(), int (*clickDownFunction)(), int (*clickUpFunction)(), UI *parent);
	void draw();
	void checkmouse(int mouseX, int mouseY, bool mouseStatus);
};

#endif
