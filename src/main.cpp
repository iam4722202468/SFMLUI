#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

#include "SFMLUI.h"
#include "button.h"
#include "checkbox.h"

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
	
	std::vector<UI*> frameVector;
	
	UI frame1(window, 200,100);
	
	frame1.addButton(10,50, 80, 40);
	//frame1.buttons.at(0)->properties.disabled = true;
	
	frame1.addButton(200,50, 80, 40);
	
	frame1.addCheckbox(300,90, 16,16, NULL, NULL, NULL, test);
	frame1.addCheckbox(320,90, 16,16);
	
	//frame1.checkboxes.at(0)->properties.disabled = true;
	//frame1.checkboxes.at(0)->checked = true;
	
	frame1.addCheckbox(340,90, 16,16);
	frame1.addCheckbox(360,90, 16,16);
	frame1.addCheckbox(380,90, 16,16);
	
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
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseMoved)
			{
				frame1.checkMouse(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, mouseLeftDown);
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				mouseLeftDown = true;
				frame1.checkMouse(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, mouseLeftDown);
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				mouseLeftDown = false;
				frame1.checkMouse(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, mouseLeftDown);
			}
				
		}
		window.clear();
		frame1.draw();
		window.display();
	}
	
	return 0;
}
