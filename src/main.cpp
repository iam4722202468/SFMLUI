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

int enableCheese(SFMLObject *object)
{
	//same objects
	if(object->properties.checked)
		object->parent->objects.at(8)->properties.disabled = false;
	else
		object->parent->objects.at(8)->properties.disabled = true;
	
	return 0;
}

int main(int argc, char *argv[])
{
	int windowX = 1200;
	int windowY = 600;
	
	sf::RenderWindow window(sf::VideoMode(windowX, windowY), "SFML window");
	
	sf::Clock clock;
	
	bool mouseLeftDown = false;
	int frames = 0;
	int selectedUIElement = -1;
	
	std::vector<UI*> UIVector;
	UI* tempUIPounter;
	
	UIVector.push_back(new UI(window, 200,100, 200,200));
	UIVector.push_back(new UI(window, 300,0, 400,500, ""));
	
	UIVector.at(0)->setText("Pizza Order Form", 4);
	
	UIVector.at(0)->hasBorder = true;
	UIVector.at(0)->moveable = true;
	
	selectedUIElement = 0;
	
	UI* frame1 = UIVector.at(UIVector.size()-1);
	
	frame1->setText("Pizza Order Form", 4);
	
	frame1->hasBorder = true;
	frame1->moveable = true;
	
	frame1->addLabel(10,40,10,10, "Gendre*");
	
	frame1->addObject("Radiobutton", 40,60,16,16, NULL, NULL, NULL, NULL, "resources/radiobuttons_red.png");
		frame1->objects.at(0)->setText("Male");
		frame1->objects.at(0)->group = 1;
	
	frame1->addObject("Radiobutton", 40,80,16,16);
		frame1->objects.at(1)->setText("Female");
		frame1->objects.at(1)->group = 1;
	
	frame1->addObject("Radiobutton", 40,100,16,16);
		frame1->objects.at(2)->setText("Other");
		frame1->objects.at(2)->group = 1;
	
	frame1->addLabel(10,140,10,10, "Phone Number*");
		frame1->addObject("Textbox", 20, 160, 180, 30);
	
	frame1->addLabel(10,210,140,10, "Toppings");
		frame1->addObject("Checkbox", 40,230,16,16);
			frame1->objects.at(4)->setText("Base");
			frame1->objects.at(4)->properties.checked = true;
		
		frame1->addObject("Checkbox", 40,250,16,16);
			frame1->objects.at(5)->setText("Sauce");
			
		frame1->addObject("Checkbox", 40,270,16,16, NULL, NULL, NULL, enableCheese);
			frame1->objects.at(6)->setText("Cheese");
			frame1->objects.at(6)->properties.checked = true;
		
		frame1->addObject("Checkbox", 40,325,16,16);
			frame1->objects.at(7)->setText("Pepperoni");
				
			frame1->addObject("Dropdown", 60,290,140,30);
				frame1->objects.at(8)->addItem("Cheddar");
				frame1->objects.at(8)->addItem("test1");
				frame1->objects.at(8)->addItem("test2");
				
				frame1->objects.at(8)->items.at(0)->selected = true;
				frame1->objects.at(8)->setText("Cheddar");
	
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
		
		while(window.pollEvent(event))
		{
			int mouseX = (int)(sf::Mouse::getPosition(window).x*((float)windowX)/window.getSize().x);
			int mouseY = (int)(sf::Mouse::getPosition(window).y*((float)windowY)/window.getSize().y);
			
			// Close window : exit
			if(event.type == sf::Event::Closed)
				window.close();
			else if(event.type == sf::Event::MouseMoved)
			{
				if(UIVector.size() > 0)
					UIVector.at(0)->checkMouse(mouseX, mouseY, mouseLeftDown);
			}
			else if(event.type == sf::Event::MouseButtonPressed)
			{
				mouseLeftDown = true;
				for(int place = 0; place < UIVector.size(); place++)
					if(UIVector.at(place)->checkMouse(mouseX, mouseY, mouseLeftDown))
					{
						if(place != 0)
						{
							tempUIPounter = UIVector.at(place);
							
							for(int placeSub = place; placeSub > 0; placeSub--)
								UIVector.at(placeSub) = UIVector.at(placeSub-1);
							
							UIVector.at(0) = tempUIPounter;
						}
						break;
					}
			}
			else if(event.type == sf::Event::MouseButtonReleased)
			{
				mouseLeftDown = false;
				if(UIVector.size() > 0)
					UIVector.at(0)->checkMouse(mouseX, mouseY, mouseLeftDown);
			}
			else if(event.type == sf::Event::KeyPressed)
			{
				if(UIVector.size() > 0)
					UIVector.at(0)->checkKey(event.key);
			}
		}
		
		window.clear(sf::Color::Green);
		
		for(int place = UIVector.size()-1; place >= 0; place--)
			UIVector.at(place)->draw();
		
		window.display();
	}
	
	return 0;
}
