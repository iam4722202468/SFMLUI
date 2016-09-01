#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "details.h"
#include "SFMLUI.h"

class UI;
class List;
class Item;

class List : public SFMLObject
{
	friend class Item;
	
	protected:
	
	sf::Texture dropdownSheet;
	
	public:
	
	struct ObjectSprites
	{
		sf::Sprite left;
		sf::Sprite right;
		sf::Sprite middle;
	};
	
	struct SheetInfo
	{
		struct Left	{int width,height;} left;
		struct Middle {int width,height;} middle;
		struct Right {int width,height;} right;
		struct Button {int x,y;} button;
		struct Corner {int x,y;} corner;
		int itemSize = 30;
	} sheetInfo;
	
	struct ListSprites
	{
		ObjectSprites nothing;
		ObjectSprites hover;
		ObjectSprites click;
		ObjectSprites disabled;
		
		struct ItemSprites
		{
			sf::Color nothing;
			sf::Color selected;
			sf::Color hover;
			sf::Color click;
			
			sf::Color divider;
		} itemSprites;
	} dropdownSprites;
	
	void draw();
	void addItem(std::string);
	bool checkmouse(int mouseX, int mouseY, bool mouseStatus);
	
	void init() override;
	
	List(std::string objectType, sf::RenderWindow& window, int &xOrigin, int &yOrigin, int x, int y, int width, int height, int (*hoverEnterFunction)(SFMLObject *object), int (*hoverLeaveFunction)(SFMLObject *object), int (*clickDownFunction)(SFMLObject *object), int (*clickUpFunction)(SFMLObject *object), UI *parent, std::string objectFileName) :
		SFMLObject(objectType, window, xOrigin, yOrigin, x, y, width, height, hoverEnterFunction, hoverLeaveFunction, clickDownFunction, clickUpFunction, parent, objectFileName) {}
};
	
#endif
