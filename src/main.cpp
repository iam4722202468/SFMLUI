#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

#include "SFMLUI.h"
#include "button.h"
#include "checkbox.h"
#include "dropdown.h"

int test(Checkbox *checkbox)
{
	//same objects
	if(checkbox->properties.checked)
		checkbox->parent->hasBorder = true;
	else
		checkbox->parent->hasBorder = false;
	
	return 0;
}

int main(int argc, char *argv[])
{
	sf::RenderWindow window(sf::VideoMode(1200, 600), "SFML window");
	
	UI frame1(window, 200,100);
	frame1.setText("Hello, I'm a window title!", 4);
	
	frame1.addButton(10,50, 80, 40);
	//frame1.buttons.at(0)->setText("I'm disabled :(", 4, 9);
	
	//frame1.buttons.at(0)->properties.disabled = true;
	
	//frame1.addButton(200,50, 80, 40);
	
	frame1.addCheckbox(300,90, 16,16, NULL, NULL, NULL, test);
	//frame1.checkboxes.at(0)->setText("I'm a checkbox!");
	//frame1.addDropdown(100,100,250,35);
	frame1.addDropdown(160,150,200,35);
	frame1.dropdowns.at(0)->addItem("first 1");
	
	frame1.addDropdown(380,150,200,35);
	frame1.dropdowns.at(1)->addItem("second 1");
	frame1.dropdowns.at(1)->addItem("second 2");
	//frame1.addCheckbox(320,120, 16,16);
	
	//frame1.checkboxes.at(0)->properties.disabled = true;
	//frame1.checkboxes.at(0)->properties.checked = true;
	
	bool mouseLeftDown = false;
	
	// Start the game loop
	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		//sf::Mouse mouse;
		
		while (window.pollEvent(event))
		{
			// Close window : exit
			if(event.type == sf::Event::Closed)
				window.close();
			if(event.type == sf::Event::MouseMoved)
			{
				frame1.checkMouse(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, mouseLeftDown);
			}
			if(event.type == sf::Event::MouseButtonPressed)
			{
				mouseLeftDown = true;
				frame1.checkMouse(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, mouseLeftDown);
			}
			if(event.type == sf::Event::MouseButtonReleased)
			{
				mouseLeftDown = false;
				frame1.checkMouse(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, mouseLeftDown);
			}
			if(event.type == sf::Event::Resized)
			{
				window.setSize(sf::Vector2u(event.size.width, event.size.height));
				window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
			}
			
		}
		window.clear(sf::Color::Green);
		frame1.draw();
		window.display();
	}
	
	return 0;
}
