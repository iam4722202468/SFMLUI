#ifndef SFMLUI_H
#define SFMLUI_H

#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

class Button;
class Checkbox;
class UI
{
	sf::RenderWindow& window;
	sf::Texture borderSheet;
	
	struct BorderInfo {
		int titleWidth;
		int titleHeight;
		
		int borderWidth;
		
		int cornerSide;
		int cornerSideY;
		
		struct CloseButton {
			int x;
			int y;
			int width;
			int height;
		} closeButton;
	} borderInfo;
	
	//sprites
	sf::Sprite left;
	sf::Sprite right;
	sf::Sprite middle;
	
	sf::Sprite xButton;
	sf::Sprite lCorner;
	sf::Sprite rCorner;
	sf::Sprite lBorder;
	sf::Sprite rBorder;
	sf::Sprite dBorder;
	
	sf::RectangleShape background;
	
	public:
	
	std::vector<Button*> buttons;
	std::vector<Checkbox*> checkboxes;
	
	int x,y;
	int width = 700, height = 400;
	bool clicked = false;
	
	int moveLockX, moveLockY;
	int moveX, moveY;
	
	UI(sf::RenderWindow& window, int x, int y);
	void addButton(int posX, int posY, int width, int height, int (*hoverEnterFunction)(Button *button) = NULL, int (*hoverLeaveFunction)(Button *button) = NULL, int (*clickDownFunction)(Button *button) = NULL, int (*clickUpFunction)(Button *button) = NULL);
	void addCheckbox(int posX, int posY, int width, int height, int (*hoverEnterFunction)() = NULL, int (*hoverLeaveFunction)() = NULL, int (*clickDownFunction)() = NULL, int (*clickUpFunction)() = NULL);
	void draw();
	void generateSprites();
	void moveSprites();
	bool checkmouse(int mouseX, int mouseY, bool mouseStatus);
};

#endif
