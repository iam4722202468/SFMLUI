#include <SFML/Graphics.hpp>

#include <iostream>
#include "SFMLUI.h"

int test(Button *button)
{
	button->properties.disabled = true;
	std::cout << "button 1 released" << std::endl;
	return 0;
}

int main(int argc, char *argv[])
{
	sf::RenderWindow window(sf::VideoMode(1200, 600), "SFML window");
	UI frame1(window, 100,100);
	
	frame1.addButton(10,10, 80, 50, NULL, NULL, NULL, test);
	//frame1.buttons.at(0)->properties.disabled = true;
	
	frame1.addButton(200,10, 80, 50);
	
	frame1.addCheckbox(300,50, 50,50);
	frame1.addCheckbox(350,50, 50,50);
	
	frame1.checkboxes.at(0)->properties.disabled = true;
	frame1.checkboxes.at(0)->checked = true;
	
	frame1.addCheckbox(400,50, 50,50);
	frame1.addCheckbox(450,50, 50,50);
	frame1.addCheckbox(500,50, 50,50);
	
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
				frame1.checkmouse(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, mouseLeftDown);
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				mouseLeftDown = true;
				frame1.checkmouse(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, mouseLeftDown);
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				mouseLeftDown = false;
				frame1.checkmouse(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, mouseLeftDown);
			}
				
		}
		window.clear();
		frame1.draw();
		window.display();
	}
	
	return 0;
}
