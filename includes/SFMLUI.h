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

class UI;

class Item 
{
	TextClass *text;
	
	public:
		Item(Dropdown*, int index, std::string label);
		~Item();
		
		int index;
		std::string label;
		void draw(Dropdown*);
		
		bool selected = false;
		bool hover = false;
		bool clicked = false;
		void setText(std::string text_, int place = 10, int size = 14, sf::Color colour = sf::Color::Black);
		int checkmouse(Dropdown*, int mouseX, int mouseY, bool mouseStatus);
};
class SFMLObject;

class SFMLObject
{
	public:
	
	sf::RenderWindow& window;
	
	int &xOrigin, &yOrigin;
	int x, y;
	int height, width;
	
	bool focus = false;
	bool hover = false;
	bool clicked = false;
	
	int group;
	
	TextClass *text;
	
	UI *parent;
	
	struct Properties
	{
		bool hidden = false;
		bool disabled = false;
		bool checked = false;
	} properties;
	
	std::vector<Item*> items; //for dropdown
	
	int (*hoverEnterFunction)(SFMLObject *object);
	int (*hoverLeaveFunction)(SFMLObject *object);
	int (*clickDownFunction)(SFMLObject *object);
	int (*clickUpFunction)(SFMLObject *object);
	
	std::string objectType;
	std::string objectFileName;
	
	SFMLObject(std::string objectType, sf::RenderWindow& window, int &xOrigin, int &yOrigin, int x, int y, int width, int height, int (*hoverEnterFunction)(SFMLObject *object), int (*hoverLeaveFunction)(SFMLObject *object), int (*clickDownFunction)(SFMLObject *object), int (*clickUpFunction)(SFMLObject *object), UI *parent, std::string objectFileName);
	~SFMLObject();
	
	virtual void init() {};
	virtual void checkKey(sf::Event::KeyEvent keyInfo) {};
	virtual void addItem(std::string) {};
	virtual void draw() = 0;
	
	virtual void setText(std::string text);
	virtual bool checkmouse(int mouseX, int mouseY, bool mouseStatus) = 0;
};

class UI
{
	sf::RenderWindow& window;
	Border *border;
	
	TextClass *text;
	
	public:
	
	std::vector<SFMLObject*> objects;
	std::vector<Label*> labels;
	
	int x,y;
	int width, height;
	bool clicked = false;
	
	bool hasBorder = false;
	bool moveable = false;
	
	UI(sf::RenderWindow& window, int x, int y, int height, int width, std::string borderFileName = "");
	void addObject(std::string objectType, int posX, int posY, int width, int height, int (*hoverEnterFunction)(SFMLObject *object) = NULL, int (*hoverLeaveFunction)(SFMLObject *object) = NULL, int (*clickDownFunction)(SFMLObject *object) = NULL, int (*clickUpFunction)(SFMLObject *object) = NULL, std::string objectFileName = "");
	void addLabel(int posX, int posY, int width, int height, std::string text_ = "", int place = 10, int size = 14, sf::Color colour = sf::Color::Black);
	
	void draw();
	
	void setBorder();
	
	void deleteObject(int objectNumber);
	
	bool checkMouse(int mouseX, int mouseY, bool mouseStatus);
	void checkKey(sf::Event::KeyEvent keyInfo);
	
	void setText(std::string text, int place = 10, int size = 14, sf::Color colour = sf::Color::Black);
};

#endif
