#ifndef DROPDOWN_H
#define DROPDOWN_H

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "details.h"
#include "SFMLUI.h"

class UI;
class Dropdown;
class Item;

class Dropdown : public SFMLObject
{
	friend class Item;
	
	protected:
	
	sf::Texture dropdownSheet;
	
	public:
	
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
	
	bool dropdown = false;
	void draw();
	void addItem(std::string);
	bool checkmouse(int mouseX, int mouseY, bool mouseStatus);
	
	void init() override;
	
	Dropdown(std::string objectType, sf::RenderWindow& window, int &xOrigin, int &yOrigin, int x, int y, int width, int height, int (*hoverEnterFunction)(SFMLObject *object), int (*hoverLeaveFunction)(SFMLObject *object), int (*clickDownFunction)(SFMLObject *object), int (*clickUpFunction)(SFMLObject *object), UI *parent) :
		SFMLObject(objectType, window, xOrigin, yOrigin, x, y, width, height, hoverEnterFunction, hoverLeaveFunction, clickDownFunction, clickUpFunction, parent) {}
};
	
#endif
