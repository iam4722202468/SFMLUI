#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include "SFMLUI.h"
#include "button.h"

void Button::init()
{
	if(objectFileName == "")
		objectFileName = "resources/buttons.png";
	
	if(!buttonSheet.loadFromFile(objectFileName))
			std::cout << "Error " << EXIT_FAILURE << " loading sprite";
	std::cout << "button created" << std::endl;
	
	sprite.setTexture(buttonSheet);
	sprite.scale(width/200.0f, height/100.0f);
	
	text->properties.place = 9;
	text->properties.size = 14;
	text->properties.colour = sf::Color::Black;
}

bool Button::checkmouse(int mouseX, int mouseY, bool mouseStatus)
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
				if(clickUpFunction != NULL)
					clickUpFunction(this);
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

void Button::draw()
{
	if(!properties.hidden)
	{
		if(!properties.disabled)
		{
			if(!hover && !clicked)
				sprite.setTextureRect(sf::IntRect(0, 0, 200, 100));
			else if(hover && clicked)
				sprite.setTextureRect(sf::IntRect(0, 200, 200, 100));
			else if(hover)
				sprite.setTextureRect(sf::IntRect(0, 100, 200, 100));
		}
		else
		{
			sprite.setTextureRect(sf::IntRect(0, 300, 200, 100));
		}
		
		sprite.setPosition(sf::Vector2f(x+xOrigin,y+yOrigin));
		window.draw(sprite);
		
		text->draw(x+xOrigin, y+yOrigin);
	}
}
