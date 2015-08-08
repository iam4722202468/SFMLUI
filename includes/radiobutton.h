#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include "details.h"

class UI;
class Radiobutton
{
	sf::RenderWindow& window;
	sf::Texture radiobuttonSheet;
	sf::Sprite sprite;
	
	public:
	int &xOrigin, &yOrigin;
	int x, y;
	int height, width;
	
	bool focus = false;
	
	TextClass *text;
	
	UI *parent;
	
	bool hover = false;
	bool clicked = false;
	
	struct Properties
	{
		bool hidden = false;
		bool disabled = false;
		bool checked = false;
	} properties;
	
	int group;
	
	int (*hoverEnterFunction)(Radiobutton *radiobutton);
	int (*hoverLeaveFunction)(Radiobutton *radiobutton);
	int (*clickDownFunction)(Radiobutton *radiobutton);
	int (*clickUpFunction)(Radiobutton *radiobutton);
	
	Radiobutton(sf::RenderWindow& window, int &xOrigin, int &yOrigin, int x, int y, int width, int height, int (*hoverEnterFunction)(Radiobutton *radiobutton), int (*hoverLeaveFunction)(Radiobutton *radiobutton), int (*clickDownFunction)(Radiobutton *radiobutton), int (*clickUpFunction)(Radiobutton *radiobutton), UI *parent);
	
	void draw();
	bool checkmouse(int mouseX, int mouseY, bool mouseStatus);
	void uncheckOthers();
	
	void setText(std::string text, int place = 9, int size = 14, sf::Color colour = sf::Color::Black);
};

#endif
