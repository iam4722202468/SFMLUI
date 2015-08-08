#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include "SFMLUI.h"
#include "textbox.h"

Textbox::Textbox(sf::RenderWindow& window, int &xOrigin, int &yOrigin, int x, int y, int width, int height, int (*hoverEnterFunction)(Textbox *textbox), int (*hoverLeaveFunction)(Textbox *textbox), int (*clickDownFunction)(Textbox *textbox), int (*clickUpFunction)(Textbox *textbox), UI *parent) :
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
	if (!textboxSheet.loadFromFile("resources/textbox.png", sf::IntRect(0, 0, 200, 400)))
			std::cout << "Error " << EXIT_FAILURE << " loading sprite";
	
	std::cout << "textbox created" << std::endl;
	
	sf::Image textboxImage;
	if (!textboxImage.loadFromFile("resources/textbox.png"))
		std::cout << "Error " << EXIT_FAILURE << " loading window border";
	
	sprite.setTexture(textboxSheet);
	sprite.scale(width/200.0f, height/100.0f);
	
	text = new TextClass(window, width, height);
	setText(currentText);

	int spriteWidth;
	
	bool emptyRow = true;
	
	for(int y = 0; y <= textboxImage.getSize().y; y++)	
		for(int x = 0; x <= textboxImage.getSize().x; x++)
		{
			if(x == 0)
				emptyRow = true;
			if(+textboxImage.getPixel(x,y).r == 255 && +textboxImage.getPixel(x,y).b == 255 && +textboxImage.getPixel(x,y).g == 0)
			{
				if(!emptyRow)
				{
					spriteWidth = x;
					textboxSprites.leftWidth = x;
					x += 2;
				}
				
				if(x = textboxImage.getSize().x)
					if(emptyRow)
					{
						textboxSprites.nothing.left.setTexture(textboxSheet);
						textboxSprites.nothing.left.setTextureRect(sf::IntRect(0, 0, spriteWidth, y));
						textboxSprites.nothing.left.setScale(1, height*1.f/y);
						
						textboxSprites.nothing.middle.setTexture(textboxSheet);
						textboxSprites.nothing.middle.setTextureRect(sf::IntRect(spriteWidth + 1, 0, 1, y));
						textboxSprites.nothing.middle.setScale(width - spriteWidth - (x - (spriteWidth + 3)), height*1.f/y);
						
						textboxSprites.nothing.right.setTexture(textboxSheet);
						textboxSprites.nothing.right.setTextureRect(sf::IntRect(spriteWidth + 3, 0, x - (spriteWidth + 3), y));
						textboxSprites.nothing.right.setScale(1, height*1.f/y);
						
						textboxSprites.hover.left.setTexture(textboxSheet);
						textboxSprites.hover.left.setTextureRect(sf::IntRect(0, y + 1, spriteWidth, y));
						textboxSprites.hover.left.setScale(1, height*1.f/y);
						
						textboxSprites.hover.middle.setTexture(textboxSheet);
						textboxSprites.hover.middle.setTextureRect(sf::IntRect(spriteWidth + 1, y + 1, 1, y));
						textboxSprites.hover.middle.setScale(width - spriteWidth - (x - (spriteWidth + 3)), height*1.f/y);
						
						textboxSprites.hover.right.setTexture(textboxSheet);
						textboxSprites.hover.right.setTextureRect(sf::IntRect(spriteWidth + 3, y + 1, x - (spriteWidth + 3), y));
						textboxSprites.hover.right.setScale(1, height*1.f/y);
						
						textboxSprites.click.left.setTexture(textboxSheet);
						textboxSprites.click.left.setTextureRect(sf::IntRect(0, y*2 + 2, spriteWidth, y));
						textboxSprites.click.left.setScale(1, height*1.f/y);
						
						textboxSprites.click.middle.setTexture(textboxSheet);
						textboxSprites.click.middle.setTextureRect(sf::IntRect(spriteWidth + 1, y*2 + 2, 1, y));
						textboxSprites.click.middle.setScale(width - spriteWidth - (x - (spriteWidth + 3)), height*1.f/y);
						
						textboxSprites.click.right.setTexture(textboxSheet);
						textboxSprites.click.right.setTextureRect(sf::IntRect(spriteWidth + 3, y*2 + 2, x - (spriteWidth + 3), y));
						textboxSprites.click.right.setScale(1, height*1.f/y);
						
						textboxSprites.disabled.left.setTexture(textboxSheet);
						textboxSprites.disabled.left.setTextureRect(sf::IntRect(0, y*3 + 3, spriteWidth, y));
						textboxSprites.disabled.left.setScale(1, height*1.f/y);
						
						textboxSprites.disabled.middle.setTexture(textboxSheet);
						textboxSprites.disabled.middle.setTextureRect(sf::IntRect(spriteWidth + 1, y*3 + 3, 1, y));
						textboxSprites.disabled.middle.setScale(width - spriteWidth - (x - (spriteWidth + 3)), height*1.f/y);
						
						textboxSprites.disabled.right.setTexture(textboxSheet);
						textboxSprites.disabled.right.setTextureRect(sf::IntRect(spriteWidth + 3, y*3 + 3, x - (spriteWidth + 3), y));
						textboxSprites.disabled.right.setScale(1, height*1.f/y);
						
						return;
					}
			}
			else
				emptyRow = false;
		}
}

void Textbox::setText(std::string text_, int place, int size, sf::Color colour)
{
	text->properties.text = text_;
	text->properties.place = place;
	text->properties.size = size;
	text->properties.colour = colour;
}

void Textbox::checkKey(sf::Event::KeyEvent keyInfo)
{
	if(focus)
	{
		int addchar = 0;
		std::string toadd = "";
		
		if(keyInfo.code == 71) // left
		{
			if(highlighted)
			{
				highlighted = false;
				placeHolderPlace = 0;
			}
			else if(placeHolderPlace > 0)
				placeHolderPlace--;
		}
		else if(keyInfo.code == 72) // right
		{
			if(highlighted)
			{
				highlighted = false;
				placeHolderPlace = currentText.size();
			}
			else if(placeHolderPlace < currentText.size())
				placeHolderPlace++;
		}
		else if(keyInfo.control && keyInfo.code == 0)
			highlighted = true;
		else if(keyInfo.code == 71) // left
		{
			if(highlighted)
			{
				highlighted = false;
				placeHolderPlace = 0;
			}
			else if(placeHolderPlace > 0)
				placeHolderPlace--;
		}
		else if(keyInfo.code == 57) // space space space core spaceeeeeee
		{
			if(highlighted)
			{
				currentText.clear();
				textWidth.clear();
				placeHolderPlace = 0;
			}
			addchar = 1;
			toadd = " ";
		}
		else if(keyInfo.code == 66) // delete
		{
			if(highlighted)
			{
				currentText.clear();
				textWidth.clear();
				placeHolderPlace = 0;
			}
			if(placeHolderPlace != currentText.size())
			{
				addchar = -1;
				placeHolderPlace++;
			}
		}
		else if(keyInfo.code == 59 && currentText.size() > 0) //backspaceeeee coreeee
		{
			if(highlighted)
			{
				currentText.clear();
				textWidth.clear();
				placeHolderPlace = 0;
			}
			else if(placeHolderPlace > 0)
				addchar = -1;
			highlighted = false;
		}
		else if(keyInfo.shift && keyInfo.code <= 25) //capital
		{
			if(highlighted)
			{
				currentText.clear();
				textWidth.clear();
				placeHolderPlace = 0;
			}
			addchar = 1;
			toadd += keyInfo.code + 65;
			highlighted = false;
		}
		else if(keyInfo.code <= 25) //lower
		{
			if(highlighted)
			{
				currentText.clear();
				textWidth.clear();
				placeHolderPlace = 0;
			}
			addchar = 1;
			toadd += keyInfo.code + 97;
			highlighted = false;
		}
		
		if(addchar == 1)
		{
			currentText.insert(placeHolderPlace, toadd);
			setText(currentText);
			text->draw(x+xOrigin + 4, y+yOrigin);
			placeHolderPlace++;
			
			textWidth.push_back(text->text.getLocalBounds().width);
		}
		else if(addchar == -1)
		{
			currentText.erase(placeHolderPlace - 1, 1);
			setText(currentText);
			text->draw(x+xOrigin + 4, y+yOrigin);
			placeHolderPlace--;
			
			textWidth.pop_back();
		}
		
		placeHolder = true;
		typingCounter.restart();
	}
}

bool Textbox::checkmouse(int mouseX, int mouseY, bool mouseStatus)
{
	if(!properties.disabled)
	{
		if(mouseX >= x+xOrigin && mouseX <= x+xOrigin+width && mouseY >= y+yOrigin && mouseY <= y+yOrigin+height && mouseStatus)
		{
			if(!clicked)
				if(clickDownFunction != NULL)
					clickDownFunction(this);
			if(!hover)
				if(hoverEnterFunction != NULL)
					hoverEnterFunction(this);
			
			focus = true;
			hover = true;
			clicked = true;
			clock.restart();
			placeHolder = true;
		}
		else if(mouseX >= x+xOrigin && mouseX <= x+xOrigin+width && mouseY >= y+yOrigin && mouseY <= y+yOrigin+height && !mouseStatus)
		{
			if(clicked)
				if(clickUpFunction != NULL)
					clickUpFunction(this);
			if(!hover)
				if(hoverEnterFunction != NULL)
					hoverEnterFunction(this);
			
			hover = true;
			clicked = false;
		}
		else
		{
			if(hover)
				if(hoverLeaveFunction != NULL)
					hoverLeaveFunction(this);
			if(mouseStatus)
				focus = false;
			hover = false;
			clicked = false;
		}
	}
	else
	{
		hover = false;
		clicked = false;
	}
	return focus;
}

void Textbox::draw()
{
	sf::Sprite *leftSprite;
	sf::Sprite *middleSprite;
	sf::Sprite *rightSprite;
	sf::RectangleShape rectangle;
	
	if(properties.disabled)
	{
		leftSprite = &textboxSprites.disabled.left;
		middleSprite = &textboxSprites.disabled.middle;
		rightSprite = &textboxSprites.disabled.right;
		highlighted = false;
	}
	else if(clicked || focus)
	{
		leftSprite = &textboxSprites.click.left;
		middleSprite = &textboxSprites.click.middle;
		rightSprite = &textboxSprites.click.right;
	}
	else if(hover)
	{
		leftSprite = &textboxSprites.hover.left;
		middleSprite = &textboxSprites.hover.middle;
		rightSprite = &textboxSprites.hover.right;
		highlighted = false;
	}
	else
	{
		leftSprite = &textboxSprites.nothing.left;
		middleSprite = &textboxSprites.nothing.middle;
		rightSprite = &textboxSprites.nothing.right;
		highlighted = false;
	}
	
	leftSprite->setPosition(sf::Vector2f(x+xOrigin, y+yOrigin));
	middleSprite->setPosition(sf::Vector2f(x+xOrigin + textboxSprites.leftWidth, y+yOrigin));
	rightSprite->setPosition(sf::Vector2f(x+xOrigin + width - textboxSprites.leftWidth, y+yOrigin));
	
	if(clock.getElapsedTime().asSeconds() > 1)
	{
		clock.restart();
		if(!typing)
			placeHolder = !placeHolder;
		else
			placeHolder = true;
	}
	
	if(typingCounter.getElapsedTime().asSeconds() < 0.8)
		typing = true;
	else
		typing = false;
	
	window.draw(*leftSprite);
	window.draw(*middleSprite);
	window.draw(*rightSprite);
	
	if(highlighted)
	{
		rectangle.setFillColor(sf::Color(150, 150, 150));
		rectangle.setSize(sf::Vector2f(text->text.getLocalBounds().width, height - 16));
		rectangle.setPosition(x+xOrigin + 5, y+yOrigin + 8);
		window.draw(rectangle);
	}
	
	setText(currentText);
	text->draw(x+xOrigin + 4, y+yOrigin);
	
	if(placeHolder && focus && !highlighted)
	{
		rectangle.setFillColor(sf::Color::Black);
		rectangle.setSize(sf::Vector2f(1, height - 16));
		if(placeHolderPlace == 0)
			rectangle.setPosition(x+xOrigin + 4, y+yOrigin + 8);
		else
		{
			rectangle.setPosition(x+xOrigin + 4 + textWidth.at(placeHolderPlace-1), y+yOrigin + 8);
		}
		window.draw(rectangle);
	}
}
