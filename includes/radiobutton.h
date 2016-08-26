#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include "details.h"
#include "SFMLUI.h"

class UI;
class Radiobutton : public SFMLObject
{
	sf::Texture radiobuttonSheet;
	sf::Sprite sprite;
	
	public:
	
	void init();
	
	Radiobutton(std::string objectType, sf::RenderWindow& window, int &xOrigin, int &yOrigin, int x, int y, int width, int height, int (*hoverEnterFunction)(SFMLObject *object), int (*hoverLeaveFunction)(SFMLObject *object), int (*clickDownFunction)(SFMLObject *object), int (*clickUpFunction)(SFMLObject *object), UI *parent, std::string objectFileName) :
		SFMLObject(objectType, window, xOrigin, yOrigin, x, y, width, height, hoverEnterFunction, hoverLeaveFunction, clickDownFunction, clickUpFunction, parent, objectFileName) {}
	
	void draw();
	bool checkmouse(int mouseX, int mouseY, bool mouseStatus);
	void uncheckOthers();
};

#endif
