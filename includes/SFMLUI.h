#ifndef SFMLUI_H
#define SFMLUI_H

#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include "border.h"
#include "details.h"

class Button;
class Checkbox;
class Dropdown;
class Textbox;
class Radiobutton;
class Label;

class UI
{
	sf::RenderWindow& window;
	Border border;
	
	TextClass *text;
	
	public:
	
	std::vector<Button*> buttons;
	std::vector<Checkbox*> checkboxes;
	std::vector<Dropdown*> dropdowns;
	std::vector<Textbox*> textboxes;
	std::vector<Radiobutton*> radiobuttons;
	std::vector<Label*> labels;
	
	int x,y;
	int width = 700, height = 400;
	bool clicked = false;
	
	bool hasBorder = false;
	bool moveable = false;
	
	UI(sf::RenderWindow& window, int x, int y);
	void addButton(int posX, int posY, int width, int height, int (*hoverEnterFunction)(Button *button) = NULL, int (*hoverLeaveFunction)(Button *button) = NULL, int (*clickDownFunction)(Button *button) = NULL, int (*clickUpFunction)(Button *button) = NULL);
	void addCheckbox(int posX, int posY, int width, int height, int (*hoverEnterFunction)(Checkbox *checkbox) = NULL, int (*hoverLeaveFunction)(Checkbox *checkbox) = NULL, int (*clickDownFunction)(Checkbox *checkbox) = NULL, int (*clickUpFunction)(Checkbox *checkbox) = NULL);
	void addDropdown(int posX, int posY, int width, int height, int (*hoverEnterFunction)(Dropdown *dropdown) = NULL, int (*hoverLeaveFunction)(Dropdown *dropdown) = NULL, int (*clickDownFunction)(Dropdown *dropdown) = NULL, int (*clickUpFunction)(Dropdown *dropdown) = NULL);
	void addTextbox(int posX, int posY, int width, int height, int (*hoverEnterFunction)(Textbox *textbox) = NULL, int (*hoverLeaveFunction)(Textbox *textbox) = NULL, int (*clickDownFunction)(Textbox *textbox) = NULL, int (*clickUpFunction)(Textbox *textbox) = NULL);
	void addRadiobutton(int posX, int posY, int width, int height, int (*hoverEnterFunction)(Radiobutton *radiobutton) = NULL, int (*hoverLeaveFunction)(Radiobutton *radiobutton) = NULL, int (*clickDownFunction)(Radiobutton *radiobutton) = NULL, int (*clickUpFunction)(Radiobutton *radiobutton) = NULL);
	void addLabel(int posX, int posY, int width, int height, std::string text_ = "", int place = 10, int size = 14, sf::Color colour = sf::Color::Black);
	
	void draw();
	
	void setBorder();
	
	bool checkMouse(int mouseX, int mouseY, bool mouseStatus);
	void checkKey(sf::Event::KeyEvent keyInfo);
	
	void setText(std::string text, int place = 10, int size = 14, sf::Color colour = sf::Color::Black);
};

#endif
