#pragma once
#include <SFML/Graphics.hpp>
#include "button.h"
#include "common.h"

#include <vector>

class Menu
{
private:
	bool isActive;

	sf::Sprite background;

	std::vector<Button*> btnList;
	float buttonSpacing;

	sf::Vector2f position;
	
public:
	/*Menu();*/
	int selectedItemIndex;
	Menu(sf::Texture* backGroundTexture, sf::Vector2f position, float buttonSpacing);
	
	~Menu();

	void pushButton(unsigned int btnCode, std::string title);
	void draw();
	void update(sf::Vector2f mousePos, bool isClicked);
	bool onLoad();
	void setActive(bool isActive);
};

