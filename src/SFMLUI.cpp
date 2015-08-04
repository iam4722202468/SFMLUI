#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "SFMLUI.h"
#include "button.h"
#include "checkbox.h"
#include "dropdown.h"
#include "border.h"

UI::UI(sf::RenderWindow& window, int x, int y) : window(window), x(x), y(y)
{
	std::cout << "frame created" << std::endl;
	setBorder();
	text = new TextClass(window, width - border.borderInfo.closeButton.width, border.borderInfo.titleHeight);
}

void UI::setBorder()
{
	border.init(x, y, width, height);
}

void UI::setText(std::string text_, int place, int size, sf::Color colour)
{
	text->properties.text = text_;
	text->properties.place = place;
	text->properties.size = size;
	text->properties.colour = colour;
}

void UI::addButton(int x_, int y_, int width, int height, int (*hoverEnterFunction)(Button *button), int (*hoverLeaveFunction)(Button *button), int (*clickDownFunction)(Button *button), int (*clickUpFunction)(Button *button))
{
	buttons.push_back(new Button(window, x, y, x_, y_, width, height, hoverEnterFunction, hoverLeaveFunction, clickDownFunction, clickUpFunction, this));
}

void UI::addCheckbox(int x_, int y_, int width, int height, int (*hoverEnterFunction)(Checkbox *checkbox), int (*hoverLeaveFunction)(Checkbox *checkbox), int (*clickDownFunction)(Checkbox *checkbox), int (*clickUpFunction)(Checkbox *checkbox))
{
	checkboxes.push_back(new Checkbox(window, x, y, x_, y_, width, height, hoverEnterFunction, hoverLeaveFunction, clickDownFunction, clickUpFunction, this));
}

void UI::addDropdown(int x_, int y_, int width, int height, int (*hoverEnterFunction)(Dropdown *dropdown), int (*hoverLeaveFunction)(Dropdown *dropdown), int (*clickDownFunction)(Dropdown *dropdown), int (*clickUpFunction)(Dropdown *dropdown))
{
	dropdowns.push_back(new Dropdown(window, x, y, x_, y_, width, height, hoverEnterFunction, hoverLeaveFunction, clickDownFunction, clickUpFunction, this));
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
		text->draw(x, y);
	}
	for(int place = 0; place < buttons.size(); place++)
		buttons.at(place)->draw();
	for(int place = 0; place < checkboxes.size(); place++)
		checkboxes.at(place)->draw();
	for(int place = 0; place < dropdowns.size(); place++)
		dropdowns.at(place)->draw();
}

bool UI::checkMouse(int mouseX, int mouseY, bool mouseStatus)
{
	int infocus = 0;
	
	for(int place = 0; place < buttons.size(); place++)
		if(buttons.at(place)->checkmouse(mouseX, mouseY, mouseStatus))
			infocus = 1;
	for(int place = 0; place < checkboxes.size(); place++)
		if(checkboxes.at(place)->checkmouse(mouseX, mouseY, mouseStatus))
			infocus = 2;
	for(int place = 0; place < dropdowns.size(); place++)
		if(dropdowns.at(place)->checkmouse(mouseX, mouseY, mouseStatus))
			infocus = 3;
	
	/*		
	if(mouseStatus)
		if(infocus == 0)
			std::cout << "nothing infocus" << std::endl;
		else if(infocus == 1)
			std::cout << "button infocus" << std::endl;
		else if(infocus == 2)
			std::cout << "checkbox infocus" << std::endl;
		else if(infocus == 3)
			std::cout << "dropdown infocus" << std::endl;
	*/
	
	if(hasBorder && border.checkMouse(mouseX, mouseY, mouseStatus))
	{
		x = border.x;
		y = border.y;
		return true;
	}
	else
		return false;
}
