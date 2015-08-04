#ifndef BORDER_H
#define BORDER_H

class Border
{
	sf::Texture borderSheet;
	sf::Font font;
	sf::Text text;
	
	public:
	
	int x, y;
	int height, width;
	
	int moveLockX, moveLockY;
	int moveX, moveY;
	
	bool clicked = false;
	
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
	
	Border();
	void generateSprites();
	void moveSprites();
	void init(int x, int y, int width, int height);
	
	bool checkMouse(int mouseX, int mouseY, bool mouseStatus);
};

#endif
