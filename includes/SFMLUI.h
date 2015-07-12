#ifndef SFMLUI_H
#define SFMLUI_H

#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

class Button;
class Checkbox;
class UI
{
	sf::RenderWindow& window;
	
	public:
	
	std::vector<Button*> buttons;
	std::vector<Checkbox*> checkboxes;
	
	int x,y;
	int width, height; //not used as of now
	
	UI(sf::RenderWindow& window, int x, int y);
	void addButton(int posX, int posY, int width, int height, int (*hoverEnterFunction)(Button *button) = NULL, int (*hoverLeaveFunction)(Button *button) = NULL, int (*clickDownFunction)(Button *button) = NULL, int (*clickUpFunction)(Button *button) = NULL);
	void addCheckbox(int posX, int posY, int width, int height, int (*hoverEnterFunction)() = NULL, int (*hoverLeaveFunction)() = NULL, int (*clickDownFunction)() = NULL, int (*clickUpFunction)() = NULL);
	void draw();
	bool checkmouse(int mouseX, int mouseY, bool mouseStatus);
};

#endif
