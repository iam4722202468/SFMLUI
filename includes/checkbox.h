#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include "details.h"
#include "SFMLUI.h"

class UI;
class Checkbox : public SFMLObject
{
	sf::Texture checkboxSheet;
	sf::Sprite sprite;
	
	public:
	
	void init();
	
	Checkbox(std::string objectType, sf::RenderWindow& window, int &xOrigin, int &yOrigin, int x, int y, int width, int height, int (*hoverEnterFunction)(SFMLObject *object), int (*hoverLeaveFunction)(SFMLObject *object), int (*clickDownFunction)(SFMLObject *object), int (*clickUpFunction)(SFMLObject *object), UI *parent) :
		SFMLObject(objectType, window, xOrigin, yOrigin, x, y, width, height, hoverEnterFunction, hoverLeaveFunction, clickDownFunction, clickUpFunction, parent) {}
	
	void draw();
	bool checkmouse(int mouseX, int mouseY, bool mouseStatus);
	void setText(std::string text);
};

#endif
