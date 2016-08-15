#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "details.h"
#include "SFMLUI.h"

class UI;
class Button : public SFMLObject
{
	sf::Texture buttonSheet;
	sf::Sprite sprite;
	
public:
	
	void init();
	
	Button(std::string objectType, sf::RenderWindow& window, int &xOrigin, int &yOrigin, int x, int y, int width, int height, int (*hoverEnterFunction)(SFMLObject *object), int (*hoverLeaveFunction)(SFMLObject *object), int (*clickDownFunction)(SFMLObject *object), int (*clickUpFunction)(SFMLObject *object), UI *parent) :
		SFMLObject(objectType, window, xOrigin, yOrigin, x, y, width, height, hoverEnterFunction, hoverLeaveFunction, clickDownFunction, clickUpFunction, parent) {}
	
	void draw();
	void setText(std::string text);
	bool checkmouse(int mouseX, int mouseY, bool mouseStatus);
};

#endif
