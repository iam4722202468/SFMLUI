#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "SFMLUI.h"
#include "radiobutton.h"

void Radiobutton::init()
{
	if (!radiobuttonSheet.loadFromFile("resources/radiobuttons.png", sf::IntRect(0, 0, 100, 800)))
			std::cout << "Error " << EXIT_FAILURE << " loading sprite";
	std::cout << "radiobutton created" << std::endl;
	
	sprite.setTexture(radiobuttonSheet);
	sprite.scale(width/100.0f, height/100.0f);
	
	group = 0;
	
	text->properties.place = 9;
	text->properties.size = 14;
	text->properties.colour = sf::Color::Black;
}

void Radiobutton::setText(std::string text_)
{
	text->properties.text = text_;
}

void Radiobutton::uncheckOthers()
{
	for(int otherButtons = 0; otherButtons < parent->objects.size(); otherButtons++)
		if(parent->objects.at(otherButtons)->objectType == "Radiobutton" && parent->objects.at(otherButtons)->group == group)
			parent->objects.at(otherButtons)->properties.checked = false;
}

bool Radiobutton::checkmouse(int mouseX, int mouseY, bool mouseStatus)
{
	if(!properties.disabled)
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
				{
					uncheckOthers();
					properties.checked = true;
				}
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
			hover = false;
			clicked = false;
			
			if(mouseStatus)
				focus = false;
		}
	}
	else
	{
		hover = false;
		clicked = false;
	}
	return focus;
}

void Radiobutton::draw()
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
