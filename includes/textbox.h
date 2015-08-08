#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "details.h"

class UI;
class Textbox
{
	sf::RenderWindow& window;
	sf::Texture textboxSheet;
	sf::Sprite sprite;
	
public:
	int &xOrigin, &yOrigin;
	int x, y;
	int height, width;
	
	std::string currentText = "";
	
	bool focus = false;
	bool hover = false;
	bool clicked = false;
	
	bool placeHolder = false;
	int placeHolderPlace = 0;
	bool typing = false;
	bool highlighted = false;
	
	std::vector<double> textWidth;
	TextClass *text;
	
	UI *parent;
	
	struct Properties
	{
		bool hidden = false;
		bool disabled = false;
	} properties;
	
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
	
	int (*hoverEnterFunction)(Textbox *textbox);
	int (*hoverLeaveFunction)(Textbox *textbox);
	int (*clickDownFunction)(Textbox *textbox);
	int (*clickUpFunction)(Textbox *textbox);
	
	Textbox(sf::RenderWindow& window, int &xOrigin, int &yOrigin, int x, int y, int width, int height, int (*hoverEnterFunction)(Textbox *textbox), int (*hoverLeaveFunction)(Textbox *textbox), int (*clickDownFunction)(Textbox *textbox), int (*clickUpFunction)(Textbox *textbox), UI *parent);
	
	void draw();
	void setText(std::string text, int place = 1, int size = 14, sf::Color colour = sf::Color::Black);
	bool checkmouse(int mouseX, int mouseY, bool mouseStatus);
	void checkKey(sf::Event::KeyEvent keyInfo);
};

#endif
