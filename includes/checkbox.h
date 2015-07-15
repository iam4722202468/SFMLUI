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
	
	struct Properties
	{
		bool hidden = false;
		bool disabled = false;
		bool checked = false;
	} properties;
	
	int (*hoverEnterFunction)(Checkbox *checkbox);
	int (*hoverLeaveFunction)(Checkbox *checkbox);
	int (*clickDownFunction)(Checkbox *checkbox);
	int (*clickUpFunction)(Checkbox *checkbox);
	
	Checkbox(sf::RenderWindow& window, int &xOrigin, int &yOrigin, int x, int y, int width, int height, int (*hoverEnterFunction)(Checkbox *checkbox), int (*hoverLeaveFunction)(Checkbox *checkbox), int (*clickDownFunction)(Checkbox *checkbox), int (*clickUpFunction)(Checkbox *checkbox), UI *parent);
	void draw();
	void checkmouse(int mouseX, int mouseY, bool mouseStatus);
};

#endif
