#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "checkbox.h"

Checkbox::Checkbox(sf::RenderWindow& window, int &xOrigin, int &yOrigin, int x, int y, int width, int height, int (*hoverEnterFunction)(), int (*hoverLeaveFunction)(), int (*clickDownFunction)(), int (*clickUpFunction)(), UI *parent) : 
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
	if (!checkboxSheet.loadFromFile("resources/checkboxes.png", sf::IntRect(0, 0, 100, 800)))
			std::cout << "Error " << EXIT_FAILURE << " loading sprite";
	std::cout << "checkbox created" << std::endl;
}

void Checkbox::checkmouse(int mouseX, int mouseY, bool mouseStatus)
{
	if(!properties.disabled)
	{
		if(mouseX >= x+xOrigin && mouseX <= x+xOrigin+width && mouseY >= y+yOrigin && mouseY <= y+yOrigin+height && mouseStatus)
		{
			if(!clicked)
				if(clickDownFunction != NULL)
					clickDownFunction();
			if(!hover)
				if(hoverEnterFunction != NULL)
					hoverEnterFunction();
			
			hover = true;
			clicked = true;
		}
		else if(mouseX >= x+xOrigin && mouseX <= x+xOrigin+width && mouseY >= y+yOrigin && mouseY <= y+yOrigin+height && !mouseStatus)
		{
			if(clicked)
			{
				if(!checked)
					checked = true;
				else
					checked = false;
				if(clickUpFunction != NULL)
					clickUpFunction();
			}
			if(!hover)
				if(hoverEnterFunction != NULL)
					hoverEnterFunction();
			
			hover = true;
			clicked = false;
		}
		else
		{
			if(hover)
				if(hoverLeaveFunction != NULL)
					hoverLeaveFunction();
			hover = false;
			clicked = false;
		}
	}
	else
	{
		hover = false;
		clicked = false;
	}
}

void Checkbox::draw()
{
	sf::Sprite sprite(checkboxSheet);
	
	if(!properties.disabled)
	{
		if(!checked)
		{
			if(!hover && !clicked)
				sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));
			else if(hover && clicked)
				sprite.setTextureRect(sf::IntRect(0, 400, 100, 100));
			else if(hover)
				sprite.setTextureRect(sf::IntRect(0, 200, 100, 100));
		}
		else
		{
			if(!hover && !clicked)
				sprite.setTextureRect(sf::IntRect(0, 100, 100, 100));
			else if(hover && clicked)
				sprite.setTextureRect(sf::IntRect(0, 500, 100, 100));
			else if(hover)
				sprite.setTextureRect(sf::IntRect(0, 300, 100, 100));
		}
	}
	else
	{
		if(!checked)
			sprite.setTextureRect(sf::IntRect(0, 600, 100, 100));
		else
			sprite.setTextureRect(sf::IntRect(0, 700, 100, 100));
	}
	
	sprite.scale(width/100.0f, height/100.0f);
	
	sprite.setPosition(sf::Vector2f(x+xOrigin,y+yOrigin));
	window.draw(sprite);
}
