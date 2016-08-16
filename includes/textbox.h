#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "details.h"
#include "SFMLUI.h"

class UI;
class Textbox : public SFMLObject
{
	sf::Texture textboxSheet;
	sf::Sprite sprite;
	
public:
	
	std::string currentText = "";
	
	bool placeHolder = false;
	int placeHolderPlace = 0;
	bool typing = false;
	bool highlighted = false;
	
	std::vector<double> textWidth;
	
	struct TextboxSprites
	{
		int leftWidth;
		
		struct Nothing
		{
			sf::Sprite left;
			sf::Sprite middle;
			sf::Sprite right;
		} nothing;
		
		struct Hover
		{
			sf::Sprite left;
			sf::Sprite middle;
			sf::Sprite right;
		} hover;
		
		struct Click
		{
			sf::Sprite left;
			sf::Sprite middle;
			sf::Sprite right;
		} click;
		
		struct Disabled
		{
			sf::Sprite left;
			sf::Sprite middle;
			sf::Sprite right;
		} disabled;
		
	} textboxSprites;
	
	sf::Clock clock;
	sf::Clock typingCounter;
	
	void init();
	
	Textbox(std::string objectType, sf::RenderWindow& window, int &xOrigin, int &yOrigin, int x, int y, int width, int height, int (*hoverEnterFunction)(SFMLObject *object), int (*hoverLeaveFunction)(SFMLObject *object), int (*clickDownFunction)(SFMLObject *object), int (*clickUpFunction)(SFMLObject *object), UI *parent) :
		SFMLObject(objectType, window, xOrigin, yOrigin, x, y, width, height, hoverEnterFunction, hoverLeaveFunction, clickDownFunction, clickUpFunction, parent) {}
	
	void draw();
	bool checkmouse(int mouseX, int mouseY, bool mouseStatus);
	void checkKey(sf::Event::KeyEvent keyInfo);
};

#endif
