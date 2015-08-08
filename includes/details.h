#ifndef DETAILS_H
#define DETAILS_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class IconClass {
};

class TextClass {
	sf::RenderWindow& window;
	sf::Font font;
	
	int parentWidth, parentHeight;
	
	public:
	
	sf::Text text;
	
	struct Properties{
		sf::Color colour = sf::Color::Black;
		std::string text;
		int size;
		int place; 
	
	// 0 - left top; 1 - left centre; 2 - left bottom; 
	// 3 - middle top; 4 - middle centre; 5 - middle bottom; 
	// 6 - right top; 7 - right centre; 8 - right bottom; 
	
	// 0 3 6
	// 1 4 7
	// 2 5 8
	
	} properties;
	
	TextClass(sf::RenderWindow& window, int parentWidth, int parentHeight, std::string text = "", int size = 14, int position = 0);
	void draw(int x, int y);
};

#endif
