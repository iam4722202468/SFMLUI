#include <iostream>

#include <SFML/Graphics.hpp>
#include "border.h"

Border::Border()
{
	if (!borderSheet.loadFromFile("resources/border.png"))
		std::cout << "Error " << EXIT_FAILURE << " loading window border";
	else
		std::cout << "window border loaded" << std::endl;
}

void Border::init(int x_, int y_, int width_, int height_)
{
	x = x_;
	y = y_;
	height = height_;
	width = width_;
	
	sf::Image borderImage;
	
	if (!borderImage.loadFromFile("resources/border.png"))
		std::cout << "Error " << EXIT_FAILURE << " loading window border";
	
	int counter = 0;
	
	bool foundButton = false;
	bool inButton = false;
	bool buttonInRow = false;
	
	int lastY;
	
	borderInfo.titleWidth = borderImage.getSize().x;
	
	for(int y = 0; y <= borderImage.getSize().y; y++)	
		for(int x = 0; x <= borderImage.getSize().x; x++)
		{
			if(counter == 0)
			{
				if(x == 0)
					if(+borderImage.getPixel(x,y).r == 255 && +borderImage.getPixel(x,y).b == 255)
					{
						borderInfo.titleHeight = y;
						counter++;
					}
			}
			if(counter == 1)
			{
				if(x == 0)
					buttonInRow = false;
				if(+borderImage.getPixel(x,y).r != 255 or borderImage.getPixel(x,y).b != 255 )
				{
					if(!foundButton)
					{
						borderInfo.closeButton.x = x;
						borderInfo.closeButton.y = y;
						foundButton = true;
					}
					buttonInRow = true;
					inButton = true;
					lastY = y;
				}
				else
				{
					if(inButton)
					{
						borderInfo.closeButton.width = x - borderInfo.closeButton.x - 1;
						inButton = false;
					}
				}
				if(x == borderImage.getSize().x && foundButton)
					if(!buttonInRow)
					{
						borderInfo.closeButton.height = lastY - borderInfo.closeButton.y;
					}
					
				if(y == borderInfo.titleHeight*2)
				{
					counter++;
					buttonInRow = false;
					inButton = false;
				}
						
			}
			if(counter == 2)
			{
				if(+borderImage.getPixel(x,y).r == 255 && +borderImage.getPixel(x,y).b == 255 && x == 0)
				{
					borderInfo.cornerSide = y - borderInfo.titleHeight*2;
					borderInfo.cornerSideY = y - borderInfo.cornerSide;
					counter++;
				}
			}
		}
		
	generateSprites();
}

void Border::generateSprites()
{
	left.setTexture(borderSheet);
	right.setTexture(borderSheet);
	middle.setTexture(borderSheet);
	
	xButton.setTexture(borderSheet);
	lCorner.setTexture(borderSheet);
	rCorner.setTexture(borderSheet);
	lBorder.setTexture(borderSheet);
	rBorder.setTexture(borderSheet);
	dBorder.setTexture(borderSheet);
	
	background.setSize(sf::Vector2f(width, height));
	background.setFillColor(sf::Color(255, 255, 255, 255));
	
	left.setTextureRect(sf::IntRect(0, 0, 1, borderInfo.titleHeight));
	right.setTextureRect(sf::IntRect(borderInfo.titleWidth-1, 0, 1, borderInfo.titleHeight));
	middle.setTextureRect(sf::IntRect(2, 0, 1, borderInfo.titleHeight));
	
	middle.scale(width/1.0f-2, 1);
	
	xButton.setTextureRect(sf::IntRect(borderInfo.closeButton.x, borderInfo.closeButton.y, borderInfo.closeButton.width, borderInfo.closeButton.height));
	
	lCorner.setTextureRect(sf::IntRect(0, borderInfo.cornerSideY, borderInfo.cornerSide, borderInfo.cornerSide));
	
	rCorner.setTextureRect(sf::IntRect(0, borderInfo.cornerSideY, borderInfo.cornerSide, borderInfo.cornerSide));
	rCorner.scale(-1.0f,1.0f);
	
	lBorder.setTextureRect(sf::IntRect(0, borderInfo.cornerSideY + borderInfo.cornerSide + 1, borderInfo.cornerSide, 1));
	lBorder.scale(1, height - borderInfo.titleHeight - borderInfo.cornerSide + 1);
	
	rBorder.setTextureRect(sf::IntRect(0, borderInfo.cornerSideY + borderInfo.cornerSide + 1, borderInfo.cornerSide, 1));
	rBorder.scale(-1.0f, height - borderInfo.titleHeight - borderInfo.cornerSide + 1);
	
	dBorder.setTextureRect(sf::IntRect(0, borderInfo.cornerSideY + borderInfo.cornerSide + 1, borderInfo.cornerSide, 1));
	dBorder.scale(-1.0f, width - borderInfo.cornerSide*2);
	dBorder.rotate(-90);
	
	moveSprites();
}

void Border::moveSprites()
{
	background.setPosition(sf::Vector2f(x,y));
	left.setPosition(sf::Vector2f(x,y));
	right.setPosition(sf::Vector2f(x+width-1,y));
	middle.setPosition(sf::Vector2f(x+1,y));
	xButton.setPosition(sf::Vector2f(x + borderInfo.closeButton.x - borderInfo.titleWidth + width, y + borderInfo.closeButton.y - borderInfo.titleHeight));
	lCorner.setPosition(sf::Vector2f(x, y + height - borderInfo.cornerSide));
	rCorner.setPosition(sf::Vector2f(x + width, y + height - borderInfo.cornerSide));
	lBorder.setPosition(sf::Vector2f(x, y + borderInfo.titleHeight - 1));
	rBorder.setPosition(sf::Vector2f(x + width, y + borderInfo.titleHeight - 1));
	dBorder.setPosition(sf::Vector2f(x + borderInfo.cornerSide, y + height - borderInfo.cornerSide));
}

bool Border::checkMouse(int mouseX, int mouseY, bool mouseStatus)
{
	if(mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + borderInfo.titleHeight && mouseStatus)
	{
		if(!clicked)
		{
			moveLockX = mouseX;
			moveLockY = mouseY;
			moveX = x;
			moveY = y;
			clicked = true;
		}
	}
	
	if(!mouseStatus && clicked)
		clicked = false;
	
	if(clicked)
	{
		x = moveX - (moveLockX - mouseX);
		y = moveY - (moveLockY - mouseY);
		moveSprites();
	}
	
	if(clicked)
		return true;
	else
		return false;
}
