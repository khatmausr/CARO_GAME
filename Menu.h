#pragma once
#include <SFML/Graphics.hpp>
#include "button.h"
#include "common.h"

#include <vector>

class Menu
{
private:
	float buttonSpacing;
	sf::Sprite background;
	sf::Vector2f position;
	std::vector<Button*> btnList;

public:
	bool isActive;
	int  selectedItemIndex;

	Menu(sf::Texture* backGroundTexture, sf::Vector2f position, float buttonSpacing);
	~Menu();

	void pushButton(unsigned int btnCode, std::string title);
	void update(sf::Vector2f mousePos, bool isClicked);
	void setActiveBtn(unsigned int idx, bool isActive);
	void draw();
};

