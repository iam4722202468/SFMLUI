#ifndef DROPDOWN_H
#define DROPDOWN_H

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "details.h"

class UI;
class Dropdown;

class Item 
{
	TextClass *text;
	
	public:
		int index;
		std::string label;
		void draw(Dropdown*);
		Item(Dropdown*, int index, std::string label);
		bool selected = false;
		bool hover = false;
		bool clicked = false;
		void setText(std::string text_, int place = 10, int size = 14, sf::Color colour = sf::Color::Black);
		int checkmouse(Dropdown *, int mouseX, int mouseY, bool mouseStatus);
};

class Dropdown 
{
	friend class Item;
	
	protected:
	
	sf::RenderWindow& window;
	sf::Texture dropdownSheet;
	
	public:
	
	UI *parent;
	TextClass *text;
	
	bool focus = false;
	
	int (*hoverEnterFunction)(Dropdown *dropdown);
	int (*hoverLeaveFunction)(Dropdown *dropdown);
	int (*clickDownFunction)(Dropdown *dropdown);
	int (*clickUpFunction)(Dropdown *dropdown);
	
	struct SheetInfo
	{
		struct Left	{int width,height;} left;
		struct Middle {int width,height;} middle;
		struct Right {int width,height;} right;
		struct Button {int x,y;} button;
		struct Corner {int x,y;} corner;
		int itemSize = 30;
	} sheetInfo;
	
	struct DropdownSprites
	{
		sf::Sprite button;
		
		sf::Sprite corner;
		sf::Sprite edge;
		
		struct Nothing
		{
			sf::Sprite left;
			sf::Sprite right;
			sf::Sprite middle;
		} nothing;
		
		struct Hover
		{
			sf::Sprite left;
			sf::Sprite right;
			sf::Sprite middle;
		} hover;
		
		struct Click
		{
			sf::Sprite left;
			sf::Sprite right;
			sf::Sprite middle;
		} click;
		
		struct disabled
		{
			sf::Sprite left;
			sf::Sprite right;
			sf::Sprite middle;
		} disabled;
		
		struct ItemSprites
		{
			sf::Color nothing;
			sf::Color selected;
			sf::Color hover;
			sf::Color click;
			
			sf::Color divider;
		} itemSprites;
	} dropdownSprites;
	
	std::vector<Item*> items;
	
	int &xOrigin, &yOrigin;
	
	bool selected = false;
	bool hover = false;
	bool clicked = false;
	
	struct Properties
	{
		bool hidden = false;
		bool disabled = false;
	} properties;
	
	int x, y;
	int width, height;
	bool dropdown = false;
	void draw();
	void addItem(std::string);
	bool checkmouse(int mouseX, int mouseY, bool mouseStatus);
	
	void setText(std::string text, int place = 10, int size = 14, sf::Color colour = sf::Color::Black);
	
	Dropdown(sf::RenderWindow& window, int &xOrigin, int &yOrigin, int x, int y, int width, int height, int (*hoverEnterFunction)(Dropdown *dropdown), int (*hoverLeaveFunction)(Dropdown *dropdown), int (*clickDownFunction)(Dropdown *dropdown), int (*clickUpFunction)(Dropdown *dropdown), UI *parent);
};
	
#endif
