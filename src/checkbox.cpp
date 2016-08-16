#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "checkbox.h"

void Checkbox::init()
{
	if (!checkboxSheet.loadFromFile("resources/checkboxes.png", sf::IntRect(0, 0, 100, 800)))
			std::cout << "Error " << EXIT_FAILURE << " loading sprite";
	std::cout << "checkbox created" << std::endl;
	
	sprite.setTexture(checkboxSheet);
	sprite.scale(width/100.0f, height/100.0f);
	
	text->properties.place = 9;
	text->properties.size = 14;
	text->properties.colour = sf::Color::Black;
}

bool Checkbox::checkmouse(int mouseX, int mouseY, bool mouseStatus)
{
	if(!properties.disabled && !properties.hidden)
	{
		if(mouseX >= x+xOrigin && mouseX <= x+xOrigin+width && mouseY >= y+yOrigin && mouseY <= y+yOrigin+height && mouseStatus)
		{
			if(!clicked)
				if(clickDownFunction != NULL)
					clickDownFunction(this);
			if(!hover)
				if(hoverEnterFunction != NULL)
					hoverEnterFunction(this);
			
			focus = true;
			hover = true;
			clicked = true;
		}
		else if(mouseX >= x+xOrigin && mouseX <= x+xOrigin+width && mouseY >= y+yOrigin && mouseY <= y+yOrigin+height && !mouseStatus)
		{
			if(clicked)
			{
				if(!properties.checked)
					properties.checked = true;
				else
					properties.checked = false;
				if(clickUpFunction != NULL)
					clickUpFunction(this);
			}
			if(!hover)
				if(hoverEnterFunction != NULL)
					hoverEnterFunction(this);
			
			hover = true;
			clicked = false;
		}
		else
		{
			if(hover)
				if(hoverLeaveFunction != NULL)
					hoverLeaveFunction(this);
			if(mouseStatus)
				focus = false;
			hover = false;
			clicked = false;
		}
	}
	else
	{
		hover = false;
		clicked = false;
	}
	return focus;
}

void Checkbox::draw()
{
	if(!properties.hidden)
	{
		if(!properties.disabled)
		{
			if(!properties.checked)
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
			if(!properties.checked)
				sprite.setTextureRect(sf::IntRect(0, 600, 100, 100));
			else
				sprite.setTextureRect(sf::IntRect(0, 700, 100, 100));
		}
		sprite.setPosition(sf::Vector2f(x+xOrigin,y+yOrigin));
		
		window.draw(sprite);
		text->draw(x+xOrigin, y+yOrigin);
	}
}
