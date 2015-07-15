#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "SFMLUI.h"
#include "button.h"
#include "checkbox.h"
#include "border.h"

UI::UI(sf::RenderWindow& window, int x, int y) : window(window), x(x), y(y)
{
	std::cout << "frame created" << std::endl;
	setBorder();
}

void UI::setBorder()
{
	border.init(x, y, width, height);
}

void UI::addButton(int x_, int y_, int width, int height, int (*hoverEnterFunction)(Button *button), int (*hoverLeaveFunction)(Button *button), int (*clickDownFunction)(Button *button), int (*clickUpFunction)(Button *button))
{
	buttons.push_back(new Button(window, x, y, x_, y_, width, height, hoverEnterFunction, hoverLeaveFunction, clickDownFunction, clickUpFunction, this));
}

void UI::addCheckbox(int x_, int y_, int width, int height, int (*hoverEnterFunction)(Checkbox *checkbox), int (*hoverLeaveFunction)(Checkbox *checkbox), int (*clickDownFunction)(Checkbox *checkbox), int (*clickUpFunction)(Checkbox *checkbox))
{
	checkboxes.push_back(new Checkbox(window, x, y, x_, y_, width, height, hoverEnterFunction, hoverLeaveFunction, clickDownFunction, clickUpFunction, this));
}

void UI::draw()
{
	if(hasBorder)
	{
		window.draw(border.background);
		
		window.draw(border.left);
		window.draw(border.right);
		window.draw(border.middle);
		
		window.draw(border.xButton);
		
		window.draw(border.lCorner);
		window.draw(border.rCorner);
		window.draw(border.lBorder);
		window.draw(border.rBorder);
		window.draw(border.dBorder);
	}
	for(int place = 0; place < buttons.size(); place++)
		buttons.at(place)->draw();
	for(int place = 0; place < checkboxes.size(); place++)
		checkboxes.at(place)->draw();
}

bool UI::checkMouse(int mouseX, int mouseY, bool mouseStatus)
{
	for(int place = 0; place < buttons.size(); place++)
		buttons.at(place)->checkmouse(mouseX, mouseY, mouseStatus);
	for(int place = 0; place < checkboxes.size(); place++)
		checkboxes.at(place)->checkmouse(mouseX, mouseY, mouseStatus);
	
	if(hasBorder && border.checkMouse(mouseX, mouseY, mouseStatus))
	{
		x = border.x;
		y = border.y;
		return true;
	}
	else
		return false;
}
