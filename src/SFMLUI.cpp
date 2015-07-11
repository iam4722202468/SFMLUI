#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "SFMLUI.h"
#include "button.h"
#include "checkbox.h"

UI::UI(sf::RenderWindow& window, int x, int y) : window(window), x(x), y(y)
{
	std::cout << "frame created" << std::endl;
}

void UI::addButton(int x_, int y_, int width, int height, int (*hoverEnterFunction)(Button *button), int (*hoverLeaveFunction)(Button *button), int (*clickDownFunction)(Button *button), int (*clickUpFunction)(Button *button))
{
	buttons.push_back(new Button(window, x, y, x_, y_, width, height, hoverEnterFunction, hoverLeaveFunction, clickDownFunction, clickUpFunction));
}

void UI::addCheckbox(int x_, int y_, int width, int height, int (*hoverEnterFunction)(), int (*hoverLeaveFunction)(), int (*clickDownFunction)(), int (*clickUpFunction)())
{
	checkboxes.push_back(new Checkbox(window, x, y, x_, y_, width, height, hoverEnterFunction, hoverLeaveFunction, clickDownFunction, clickUpFunction));
}

void UI::draw()
{
	for(int place = 0; place < buttons.size(); place++)
	{
		buttons.at(place)->draw();
	}
	for(int place = 0; place < checkboxes.size(); place++)
	{
		checkboxes.at(place)->draw();
	}
}

bool UI::checkmouse(int mouseX, int mouseY, bool mouseStatus)
{
	for(int place = 0; place < buttons.size(); place++)
		buttons.at(place)->checkmouse(mouseX, mouseY, mouseStatus);
	for(int place = 0; place < checkboxes.size(); place++)
		checkboxes.at(place)->checkmouse(mouseX, mouseY, mouseStatus);
}
