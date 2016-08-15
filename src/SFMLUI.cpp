#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "SFMLUI.h"
#include "button.h"
#include "checkbox.h"
#include "dropdown.h"
#include "border.h"
#include "textbox.h"
#include "radiobutton.h"
#include "label.h"

SFMLObject::SFMLObject(std::string objectType, sf::RenderWindow& window, int &xOrigin, int &yOrigin, int x, int y, int width, int height, int (*hoverEnterFunction)(SFMLObject *object), int (*hoverLeaveFunction)(SFMLObject *object), int (*clickDownFunction)(SFMLObject *object), int (*clickUpFunction)(SFMLObject *object), UI *parent) :
	objectType(objectType),
	window(window),
	xOrigin(xOrigin),
	yOrigin(yOrigin),
	x(x),
	y(y),
	width(width),
	height(height),
	hoverEnterFunction(hoverEnterFunction),
	hoverLeaveFunction(hoverLeaveFunction),
	clickDownFunction(clickDownFunction),
	clickUpFunction(clickUpFunction),
	parent(parent)
{
	group = -1;
	text = new TextClass(window, width, height);
}

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

void UI::addObject(std::string objectType, int x_, int y_, int width, int height, int (*hoverEnterFunction)(SFMLObject *object), int (*hoverLeaveFunction)(SFMLObject *object), int (*clickDownFunction)(SFMLObject *object), int (*clickUpFunction)(SFMLObject *object))
{
	if(objectType == "Button")
		objects.push_back(new Button(objectType, window, x, y, x_, y_, width, height, hoverEnterFunction, hoverLeaveFunction, clickDownFunction, clickUpFunction, this));
	else if(objectType == "Checkbox")
		objects.push_back(new Checkbox(objectType, window, x, y, x_, y_, width, height, hoverEnterFunction, hoverLeaveFunction, clickDownFunction, clickUpFunction, this));
	else if(objectType == "Dropdown")
		objects.push_back(new Dropdown(objectType, window, x, y, x_, y_, width, height, hoverEnterFunction, hoverLeaveFunction, clickDownFunction, clickUpFunction, this));
	else if(objectType == "Textbox")
		objects.push_back(new Textbox(objectType, window, x, y, x_, y_, width, height, hoverEnterFunction, hoverLeaveFunction, clickDownFunction, clickUpFunction, this));
	else if(objectType == "Radiobutton")
		objects.push_back(new Radiobutton(objectType, window, x, y, x_, y_, width, height, hoverEnterFunction, hoverLeaveFunction, clickDownFunction, clickUpFunction, this));
	objects.at(objects.size()-1)->init();
}

void UI::addLabel(int x_, int y_, int width, int height, std::string text_, int place, int size, sf::Color colour)
{
	labels.push_back(new Label(window, x, y, x_, y_, width, height, this, text_, place, size, colour));
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
	for(int place = 0; place < objects.size(); place++)
		objects.at(place)->draw();
	for(int place = 0; place < labels.size(); place++)
		labels.at(place)->draw();
}

void UI::checkKey(sf::Event::KeyEvent keyInfo)
{
	for(int place = 0; place < objects.size(); place++)
		objects.at(place)->checkKey(keyInfo);
}

bool UI::checkMouse(int mouseX, int mouseY, bool mouseStatus)
{
	int infocus = 0;
	
	for(int place = 0; place < objects.size(); place++)
		if(objects.at(place)->checkmouse(mouseX, mouseY, mouseStatus))
			infocus = 1;
	
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
	
	if(moveable && hasBorder && border.checkMouse(mouseX, mouseY, mouseStatus))
	{
		x = border.x;
		y = border.y;
		return true;
	}
	else
		return false;
}
