#ifndef SFMLUI_H
#define SFMLUI_H

#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include "border.h"

class Button;
class Checkbox;

class UI
{
	sf::RenderWindow& window;
	
	Border border;
	
	public:
	
	std::vector<Button*> buttons;
	std::vector<Checkbox*> checkboxes;
	
	int x,y;
	int width = 700, height = 400;
	bool clicked = false;
	
	bool hasBorder = false;
	
	UI(sf::RenderWindow& window, int x, int y);
	void addButton(int posX, int posY, int width, int height, int (*hoverEnterFunction)(Button *button) = NULL, int (*hoverLeaveFunction)(Button *button) = NULL, int (*clickDownFunction)(Button *button) = NULL, int (*clickUpFunction)(Button *button) = NULL);
	void addCheckbox(int posX, int posY, int width, int height, int (*hoverEnterFunction)(Checkbox *checkbox) = NULL, int (*hoverLeaveFunction)(Checkbox *checkbox) = NULL, int (*clickDownFunction)(Checkbox *checkbox) = NULL, int (*clickUpFunction)(Checkbox *checkbox) = NULL);
	void draw();
	
	void setBorder();
	
	bool checkMouse(int mouseX, int mouseY, bool mouseStatus);
};

#endif
