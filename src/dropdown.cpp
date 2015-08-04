#include <iostream>

#include <SFML/Graphics.hpp>
#include "SFMLUI.h"
#include "dropdown.h"

Dropdown::Dropdown(sf::RenderWindow& window, int &xOrigin, int &yOrigin, int x, int y, int width, int height, int (*hoverEnterFunction)(Dropdown *dropdown), int (*hoverLeaveFunction)(Dropdown *dropdown), int (*clickDownFunction)(Dropdown *dropdown), int (*clickUpFunction)(Dropdown *dropdown), UI *parent) :
	window(window),
	xOrigin(xOrigin),
	yOrigin(yOrigin),
	x(x),
	y(y),
	width(width),
	height(height),
	hoverEnterFunction(hoverEnterFunction),
	hoverLeaveFunction(hoverLeaveFunction),
	clickDownFunction(clickDownFunction),
	clickUpFunction(clickUpFunction),
	parent(parent)
{
	if (!dropdownSheet.loadFromFile("resources/dropdown.png"))
		std::cout << "Error " << EXIT_FAILURE << " loading window border";
	else
		std::cout << "dropdown sheet loaded" << std::endl;
	
	std::cout << "dropdown created" << std::endl;
	
	sf::Image dropdownImage;
	if (!dropdownImage.loadFromFile("resources/dropdown.png"))
		std::cout << "Error " << EXIT_FAILURE << " loading window border";
	
	text = new TextClass(window, width, height);
	setText("");
	
	int counter = 0;
	
	int x1 = 0, y1 = 0;
	int x2,y2;
	
	bool variable = false;
	
	int lastblank = 0;
	
	bool emptyRow = true;
	
	for(int y = 0; y <= dropdownImage.getSize().y; y++)	
		for(int x = 0; x <= dropdownImage.getSize().x; x++)
		{
			if(x == 0)
			{
				emptyRow = true;
			}
			if(counter == 0)
			{
				if(+dropdownImage.getPixel(x,y).r == 255 && +dropdownImage.getPixel(x,y).b == 255 && +dropdownImage.getPixel(x,y).g == 0)
				{
					if(!variable)
					{
						dropdownSprites.left.setTexture(dropdownSheet);
						dropdownSprites.right.setTexture(dropdownSheet);
						dropdownSprites.middle.setTexture(dropdownSheet);
						dropdownSprites.button.setTexture(dropdownSheet);
						dropdownSprites.corner.setTexture(dropdownSheet);
						dropdownSprites.edge.setTexture(dropdownSheet);
						variable = true;
						x2 = x;
					}
					
					if(x == dropdownImage.getSize().x && emptyRow)
					{
						y2 = y;
						dropdownSprites.left.setTextureRect(sf::IntRect(0, 0, x2, y2));
							sheetInfo.left.width = x2;
							sheetInfo.left.height = y2;
							dropdownSprites.left.scale(1.f, float(height)/y);
							
						dropdownSprites.right.setTextureRect(sf::IntRect(lastblank+1, 0, dropdownImage.getSize().x - lastblank, y2));
							sheetInfo.right.width = dropdownImage.getSize().x - lastblank;
							sheetInfo.right.height = y2;
							dropdownSprites.right.scale(1.f, float(height)/y);
							
						dropdownSprites.middle.setTextureRect(sf::IntRect(x2+2, 0, 1, y2));
							sheetInfo.middle.width = width - sheetInfo.right.width - sheetInfo.left.width;
							sheetInfo.middle.height = y2;
							dropdownSprites.middle.scale(sheetInfo.middle.width/1.f, float(height)/y);
						
						counter++;
						
						variable = false;
						lastblank = 0;
					}
					
					if(lastblank < x && !emptyRow && x < dropdownImage.getSize().x)
						lastblank = x;
					
				}
				else
				{
					emptyRow = false;
				}
			}
			else if(counter == 1)
			{
				if(+dropdownImage.getPixel(x,y).r == 255 && +dropdownImage.getPixel(x,y).b == 255 && +dropdownImage.getPixel(x,y).g == 0)
				{
					if(variable && !emptyRow && lastblank == 0)
					{
						lastblank = x;
						x2 = x;
					}
					
					if(variable && emptyRow && dropdownImage.getSize().x == x)
					{
						y2 = y;
						counter++;
						
						dropdownSprites.button.setTextureRect(sf::IntRect(x1, y1, x2 - x1, y2 - y1));
							sheetInfo.button.x = width - (dropdownImage.getSize().x - x1);
							sheetInfo.button.y = (height - (y2 - y1))/2;
					}
				}
				else
				{
					emptyRow = false;
					if(!variable)
					{
						variable = true;
						x1 = x;
						y1 = y;
					}
				}
			}
			else if(counter == 2)
			{
				if(y == sheetInfo.left.height*2 && x == 0)
				{
					dropdownSprites.itemSprites.nothing.r = +dropdownImage.getPixel(x,y).r; dropdownSprites.itemSprites.nothing.g = +dropdownImage.getPixel(x,y).g; dropdownSprites.itemSprites.nothing.b = +dropdownImage.getPixel(x,y).b;
					dropdownSprites.itemSprites.hover.r = +dropdownImage.getPixel(x+1,y).r; dropdownSprites.itemSprites.hover.g = +dropdownImage.getPixel(x+1,y).g; dropdownSprites.itemSprites.hover.b = +dropdownImage.getPixel(x+1,y).b;
					dropdownSprites.itemSprites.click.r = +dropdownImage.getPixel(x+2,y).r; dropdownSprites.itemSprites.click.g = +dropdownImage.getPixel(x+2,y).g; dropdownSprites.itemSprites.click.b = +dropdownImage.getPixel(x+2,y).b;
					dropdownSprites.itemSprites.divider.r = +dropdownImage.getPixel(x+3,y).r; dropdownSprites.itemSprites.divider.g = +dropdownImage.getPixel(x+3,y).g; dropdownSprites.itemSprites.divider.b = +dropdownImage.getPixel(x+3,y).b;
					dropdownSprites.itemSprites.selected.r = +dropdownImage.getPixel(x+4,y).r; dropdownSprites.itemSprites.selected.g = +dropdownImage.getPixel(x+4,y).g; dropdownSprites.itemSprites.selected.b = +dropdownImage.getPixel(x+4,y).b;
				}
				if(y == sheetInfo.left.height*2+2)
				{
					counter++;
					variable = false;
				}
			}
			if(counter == 3)
			{
				if(+dropdownImage.getPixel(x,y).r == 255 && +dropdownImage.getPixel(x,y).b == 255 && +dropdownImage.getPixel(x,y).g == 0)
				{
					if(!variable)
					{
						variable = true;
						x1 = 0; x2 = x;
						y1 = y;
					}
				}
				else
					emptyRow = false;
				
				if(emptyRow)
				{
					y2 = y;
					dropdownSprites.corner.setTextureRect(sf::IntRect(x1, y1, x2 - x1, y2 - y1));
						sheetInfo.corner.x = x2 - x1;
						sheetInfo.corner.y = y2 - y1;
					
					counter++;
					variable = false;
					lastblank = dropdownImage.getSize().x;
					y++;
				}
			}
			if(counter == 4)
			{
				if(!variable)
				{
					x1 = 0;
					y1 = y;
					x2 = 1;
					emptyRow = false;
					variable = true;
				}
				
				if(!(+dropdownImage.getPixel(x,y).r == 255 && +dropdownImage.getPixel(x,y).b == 255 && +dropdownImage.getPixel(x,y).g == 0))
					emptyRow = false;
				
				if(emptyRow)
				{
					y2 = y;
					dropdownSprites.edge.setTextureRect(sf::IntRect(x1, y1, x2 - x1, y2 - y1));
					counter++;
				}
			}
		}
}

void Item::setText(std::string text_, int place, int size, sf::Color colour)
{
	text->properties.text = text_;
	text->properties.place = place;
	text->properties.size = size;
	text->properties.colour = colour;
}

Item::Item(Dropdown *parent, int index, std::string label) :
	index(index),
	label(label)
{
	std::cout << "item created" << std::endl;
	text = new TextClass(parent->window, parent->width, parent->sheetInfo.itemSize);
	setText(label);	
}

void Item::draw(Dropdown *parent)
{
	if(index == 0)
	{
		parent->dropdownSprites.corner.setRotation(0);
		parent->dropdownSprites.edge.setRotation(0);
		parent->dropdownSprites.corner.setScale(1,1);
		
		//top left
		parent->dropdownSprites.corner.setPosition(sf::Vector2f(parent->x+parent->xOrigin,parent->y+parent->yOrigin+parent->height));
		parent->window.draw(parent->dropdownSprites.corner);
		
		//top
		parent->dropdownSprites.edge.setPosition(sf::Vector2f(parent->x+parent->xOrigin + parent->sheetInfo.corner.x,parent->y+parent->yOrigin+parent->height + parent->sheetInfo.corner.y));
		parent->dropdownSprites.edge.setScale(parent->width - parent->sheetInfo.corner.x*2, -1);
		parent->window.draw(parent->dropdownSprites.edge);
		
		//bottom
		parent->dropdownSprites.edge.setPosition(sf::Vector2f(parent->x+parent->xOrigin + parent->sheetInfo.corner.x,parent->y+parent->yOrigin+parent->height + parent->sheetInfo.corner.y + parent->items.size()*parent->sheetInfo.itemSize));
		parent->dropdownSprites.edge.setScale(parent->width - parent->sheetInfo.corner.x*2, 1);
		parent->window.draw(parent->dropdownSprites.edge);
		
		//right
		parent->dropdownSprites.edge.setRotation(-90);
		parent->dropdownSprites.edge.setPosition(sf::Vector2f(parent->x+parent->xOrigin - parent->sheetInfo.corner.x + parent->width,parent->y+parent->yOrigin+parent->height + parent->sheetInfo.corner.y + parent->items.size()*parent->sheetInfo.itemSize));
		parent->dropdownSprites.edge.setScale(parent->items.size()*parent->sheetInfo.itemSize, 1);
		parent->window.draw(parent->dropdownSprites.edge);
		
		//top right
		parent->dropdownSprites.corner.setScale(-1,1);
		parent->dropdownSprites.corner.setPosition(sf::Vector2f(parent->x+parent->xOrigin + parent->width,parent->y+parent->yOrigin+parent->height));
		parent->window.draw(parent->dropdownSprites.corner);
		
		//left
		parent->dropdownSprites.edge.setRotation(-90);
		parent->dropdownSprites.edge.setPosition(sf::Vector2f(parent->x+parent->xOrigin + parent->sheetInfo.corner.x,parent->y+parent->yOrigin+parent->height + parent->sheetInfo.corner.y + parent->items.size()*parent->sheetInfo.itemSize));
		parent->dropdownSprites.edge.setScale(parent->items.size()*parent->sheetInfo.itemSize, -1);
		parent->window.draw(parent->dropdownSprites.edge);
		
		//bottom left
		parent->dropdownSprites.corner.setScale(1,-1);
		parent->dropdownSprites.corner.setPosition(sf::Vector2f(parent->x+parent->xOrigin,parent->y+parent->yOrigin+parent->height + parent->items.size()*parent->sheetInfo.itemSize + parent->sheetInfo.corner.y*2));
		parent->window.draw(parent->dropdownSprites.corner);
		
		//bottom right
		parent->dropdownSprites.corner.setScale(-1,-1);
		parent->dropdownSprites.corner.setPosition(sf::Vector2f(parent->x+parent->xOrigin + parent->width,parent->y+parent->yOrigin+parent->height + parent->items.size()*parent->sheetInfo.itemSize + parent->sheetInfo.corner.x*2));
		parent->window.draw(parent->dropdownSprites.corner);
	}
	
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(parent->width - parent->sheetInfo.corner.x*2, parent->sheetInfo.itemSize));
	rectangle.setPosition(parent->x+parent->xOrigin + parent->sheetInfo.corner.x, parent->y + parent->yOrigin + parent->sheetInfo.itemSize*index + parent->height + parent->sheetInfo.corner.y);
	
	if(clicked)
		rectangle.setFillColor(parent->dropdownSprites.itemSprites.click);
	else if(hover && !selected)
		rectangle.setFillColor(parent->dropdownSprites.itemSprites.hover);
	else if(selected)
		rectangle.setFillColor(parent->dropdownSprites.itemSprites.selected);
	else
		rectangle.setFillColor(parent->dropdownSprites.itemSprites.nothing);
	
	parent->window.draw(rectangle);
	
	rectangle.setSize(sf::Vector2f(parent->width - parent->sheetInfo.corner.x*2, 1));
	rectangle.setPosition(parent->x+parent->xOrigin + parent->sheetInfo.corner.x, parent->y + parent->yOrigin + parent->sheetInfo.itemSize*index + (parent->sheetInfo.itemSize-1) + parent->height + parent->sheetInfo.corner.y);
	rectangle.setFillColor(parent->dropdownSprites.itemSprites.divider);
	parent->window.draw(rectangle);
	
	text->draw(parent->x+parent->xOrigin, parent->y+parent->yOrigin + parent->height + parent->sheetInfo.itemSize*index + parent->sheetInfo.corner.x/2);
}

//0 hover in, 1 hover out, 2 click down, 3 click up
int Item::checkmouse(Dropdown *parent, int mouseX, int mouseY, bool mouseStatus)
{
	if(mouseX > parent->x + parent->xOrigin && 
	mouseX < parent->x + parent->xOrigin + parent->width && 
	mouseY > parent->y + parent->yOrigin + parent->sheetInfo.itemSize*index + parent->height + parent->sheetInfo.corner.y*2 &&
	mouseY < parent->y + parent->yOrigin + parent->sheetInfo.itemSize*(index+1) + parent->height + parent->sheetInfo.corner.y)
	{
		hover = true;
		if(mouseStatus)
		{
			clicked = true;
			return 2;
		}
		else
		{
			if(clicked)
			{
				clicked = false;
				return 3;
			}
		}
		
		return 0;
	}
	else
	{
		hover = false;
		clicked = false;
		return 1;
	}
	
	return -1;
}

//0 hover in, 1 hover out, 2 click down, 3 click up
bool Dropdown::checkmouse(int mouseX, int mouseY, bool mouseStatus)
{
	
	if(mouseX > x + xOrigin && 
	mouseX < x + xOrigin + width && 
	mouseY > y + yOrigin + sheetInfo.corner.y &&
	mouseY < y + yOrigin + height + sheetInfo.corner.y)
	{
		if(clicked && !mouseStatus)
		{
			dropdown = !dropdown;
			clicked = false;
		}
		else if(mouseStatus)
		{
			clicked = true;
			focus = true;
		}
	}
	else
		if(mouseStatus)
			focus = false;
	
	if(dropdown)
		for(int place = 0; place < items.size(); place++)
		{
			switch(items.at(place)->checkmouse(this, mouseX, mouseY, mouseStatus))
			{
				case 0:
					if(hoverEnterFunction != NULL)
						hoverEnterFunction(this);
				break;
				case 1:
					if(hoverLeaveFunction != NULL)
						hoverLeaveFunction(this);
				break;
				case 2:
					if(clickDownFunction != NULL)
						clickDownFunction(this);
					setText(items.at(place)->label);
					dropdown = false;
					focus = true;
				break;
				case 3:
					if(clickUpFunction != NULL)
						clickUpFunction(this);
				break;
				default: break;
			}
		}
	return focus;
}

void Dropdown::addItem(std::string title)
{
	items.push_back(new Item(this, items.size(), title));
}

void Dropdown::setText(std::string text_, int place, int size, sf::Color colour)
{
	text->properties.text = text_;
	text->properties.place = place;
	text->properties.size = size;
	text->properties.colour = colour;
}

void Dropdown::draw()
{
	dropdownSprites.left.setPosition(sf::Vector2f(x+xOrigin, y+yOrigin));
	dropdownSprites.middle.setPosition(sf::Vector2f(x+xOrigin+sheetInfo.left.width, y+yOrigin));
	dropdownSprites.right.setPosition(sf::Vector2f(x+xOrigin + width - sheetInfo.right.width, y+yOrigin));
	dropdownSprites.button.setPosition(sf::Vector2f(x+xOrigin+sheetInfo.button.x, y+yOrigin+sheetInfo.button.y));
	
	window.draw(dropdownSprites.left);
	window.draw(dropdownSprites.middle);
	window.draw(dropdownSprites.right);
	window.draw(dropdownSprites.button);
	
	text->draw(x+xOrigin+5, y+yOrigin);
	
	if(!focus)
		dropdown = false;
	
	if(dropdown)
		for(int place = 0; place < items.size(); place++)
			items.at(place)->draw(this);
}
