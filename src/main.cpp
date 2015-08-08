#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

#include "SFMLUI.h"
#include "button.h"
#include "checkbox.h"
#include "dropdown.h"
#include "textbox.h"
#include "radiobutton.h"
#include "label.h"

int enableCheese(Checkbox *checkbox)
{
	//same objects
	if(checkbox->properties.checked)
		checkbox->parent->dropdowns.at(0)->properties.disabled = false;
	else
		checkbox->parent->dropdowns.at(0)->properties.disabled = true;
	
	return 0;
}

int main(int argc, char *argv[])
{
	sf::RenderWindow window(sf::VideoMode(1200, 600), "SFML window");
	
	UI frame1(window, 200,100);
	frame1.setText("Pizza Order Form", 4);
	
	frame1.hasBorder = true;
	frame1.moveable = true;
	
	frame1.addLabel(10,40,10,10, "Gendre*");
	
	frame1.addRadiobutton(40,60,16,16);
		frame1.radiobuttons.at(0)->setText("Male");
		
	frame1.addRadiobutton(40,80,16,16);
		frame1.radiobuttons.at(1)->setText("Female");
		
	frame1.addRadiobutton(40,100,16,16);
		frame1.radiobuttons.at(2)->setText("Other");
	
	frame1.addLabel(10,140,10,10, "Phone Number*");
		frame1.addTextbox(20, 160, 180, 30);
	
	frame1.addLabel(10,210,140,10, "Toppings");
		frame1.addCheckbox(40,230,16,16);
			frame1.checkboxes.at(0)->setText("Base");
			frame1.checkboxes.at(0)->properties.checked = true;
			
		frame1.addCheckbox(40,250,16,16);
			frame1.checkboxes.at(1)->setText("Sauce");
			
		frame1.addCheckbox(40,270,16,16, NULL, NULL, NULL, enableCheese);
			frame1.checkboxes.at(2)->setText("Cheese");
			frame1.checkboxes.at(2)->properties.checked = true;
			
			frame1.addDropdown(60,290,140,30);
				frame1.dropdowns.at(0)->addItem("Cheddar");
				frame1.dropdowns.at(0)->addItem("test1");
				frame1.dropdowns.at(0)->addItem("test2");
				
				frame1.dropdowns.at(0)->items.at(0)->selected = true;
				frame1.dropdowns.at(0)->setText("Cheddar");
		
		frame1.addCheckbox(40,325,16,16);
			frame1.checkboxes.at(3)->setText("Pepperoni");
		//	frame1.addRadiobutton(40, 345, 16, 16);
		//		frame1.radiobuttons.at(3)->group = 1;
		
	
	bool mouseLeftDown = false;
	
	sf::Clock clock;
	int frames = 0;
	
	// Start the game loop
	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		//sf::Mouse mouse;
		if(int(clock.getElapsedTime().asSeconds()) == 1)
		{
			clock.restart();
			//std::cout << frames << std::endl;
			frames = 0;
		}
		
		frames++;
		
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
			if(event.type == sf::Event::KeyPressed)
			{
				frame1.checkKey(event.key);
			}
		}
		window.clear(sf::Color::Green);
		frame1.draw();
		window.display();
	}
	
	return 0;
}
