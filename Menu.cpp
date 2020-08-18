#include "Menu.h"

//Menu::Menu()
//{
//	isActive = true;
//	buttonSpacing = 0;
//	positsion = sf::Vector2f(0.0f, 0.0f);
//	selectedItemIndex = 0;
//}

Menu::Menu(sf::Texture* backGroundTexture, sf::Vector2f position, float buttonSpacing)
{
	background.setTexture(*backGroundTexture);
	selectedItemIndex = -1;
	this->buttonSpacing = buttonSpacing;
	this->isActive = false;
	this->position = position;
}

Menu::~Menu()
{
	for (Button* btn : btnList)
	{
		delete btn;
		btn = NULL;
	}
	btnList.clear();
}

void Menu::pushButton(unsigned int btnCode, std::string title)
{
	sf::Vector2f absPosition = sf::Vector2f(position.x, position.y + this->btnList.size() * buttonSpacing);
	Button* btnTemp;
	switch (btnCode)
	{
	case 0:
		btnTemp = new Button(&t_blueButton_default, &t_blueButton_mouseOver, &s_optionSound, title, absPosition);
		break;
	case 1:
		btnTemp = new Button(&t_brownButton_default, &t_brownButton_mouseOver, &s_optionSound, title, absPosition);
		break;
	case 2:
		btnTemp = new Button(&t_greenButton_default, &t_greenButton_mouseOver, &s_optionSound, title, absPosition);
		break;
	case 3:
		btnTemp = new Button(&t_redButton_default, &t_redButton_mouseOver, &s_optionSound, title, absPosition);
		break;
	case 4:
		btnTemp = new Button(&t_yellowButton_default, &t_yellowButton_mouseOver, &s_optionSound, title, absPosition);
		break;
	}
	btnList.push_back(btnTemp);
}

void Menu::draw()
{
	window.draw(background);
	for (unsigned int i = 0; i < btnList.size(); ++i)
		btnList[i]->draw();
}

void Menu::update(sf::Vector2f mousePos, bool isClicked)
{
	selectedItemIndex = -1;
	for (unsigned int i = 0; i < this->btnList.size(); ++i)
	{
		btnList[i]->updateState(mousePos, isClicked);
		if (btnList[i]->getState() == 2)
			selectedItemIndex = i;
	}
}

bool Menu::onLoad()
{
	return isActive;
}

void Menu::setActive(bool isActive)
{
	this->isActive = isActive;
	if (this->isActive)
		for (Button* btn : btnList)
			btn->setState(0);
}
