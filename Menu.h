#pragma once
#include <SFML/Graphics.hpp>
#include "button.h"

#include <vector>

class Menu
{
protected:
	bool isActive;

	sf::Sprite background;

	std::vector<Button> btnlist;
	float buttonSpacing;

	sf::Vector2f positsion;
	unsigned int selectedItemIndex;
public:
	Menu();
	Menu(sf::Texture* backGroundTexture, std::vector<Button> btnlist, sf::Vector2f position);
	
	~Menu();

	void draw();

};

