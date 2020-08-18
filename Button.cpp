#include "button.h"
#include "common.h"
#include <iostream>
//Button::Button()
//{
//	currentSprite = NULL;
//	currentState = 0;
//}
Button::Button(sf::Texture* defaultTexture, sf::Texture* mouseOverTexture, sf::SoundBuffer* soundBuffer, std::string title, sf::Vector2f position)
{
	currentState = 0;

	defaultPlaceHolder.setTexture(*defaultTexture);
	defaultPlaceHolder.setOrigin(defaultPlaceHolder.getLocalBounds().width / 2.0f, defaultPlaceHolder.getLocalBounds().height / 2.0f);
	defaultPlaceHolder.setPosition(position);
	std::cout << defaultPlaceHolder.getPosition().x - defaultPlaceHolder.getLocalBounds().width / 2.0f << " " << defaultPlaceHolder.getPosition().y - defaultPlaceHolder.getLocalBounds().height / 2.0f << std::endl;
	std::cout << defaultPlaceHolder.getPosition().x + defaultPlaceHolder.getLocalBounds().width / 2.0f << " " << defaultPlaceHolder.getPosition().y + defaultPlaceHolder.getLocalBounds().height / 2.0f << std::endl;

	mouseOverPlaceHolder.setTexture(*mouseOverTexture);
	mouseOverPlaceHolder.setOrigin(mouseOverTexture->getSize().x / 2.0f, mouseOverTexture->getSize().y / 2.0f);
	mouseOverPlaceHolder.setPosition(position);

	currentSprite = &defaultPlaceHolder; // Default placeHolder (no cursor on this button)

	soundEffect.setBuffer(*soundBuffer);

	this->title.setString(title);
	this->title.setFont(font_bebasNeueBold);
	this->title.setCharacterSize(34);
	sf::FloatRect titleRect = this->title.getLocalBounds();
	//std::cout << this->title.getOrigin().x << " " << this->title.getOrigin().y << std::endl;
	this->title.setOrigin(titleRect.width / 2.0f, titleRect.height / 2.0f + 10.0f);
	//std::cout << this->title.getOrigin().x << " " << this->title.getOrigin().y << std::endl;

	this->titleShadow = this->title;

	this->title.setFillColor(sf::Color::White);
	this->title.setPosition(position);

	this->titleShadow.setFillColor(sf::Color(117, 76, 40));
	this->titleShadow.setPosition(position.x + 3, position.y);
}

Button::Button(const Button& btn, sf::Vector2f position)
{
	this->defaultPlaceHolder = btn.defaultPlaceHolder;
	this->defaultPlaceHolder.setPosition(position);

	this->mouseOverPlaceHolder = btn.defaultPlaceHolder;
	this->mouseOverPlaceHolder.setPosition(position);

	this->currentSprite = &this->defaultPlaceHolder;

	this->soundEffect.setBuffer(*btn.soundEffect.getBuffer());

	this->title = btn.title;
	this->title.setPosition(position);

	this->titleShadow = btn.titleShadow;
	this->title.setPosition(position.x + 3, position.y);

	this->currentState = 0;
}

Button::~Button()
{
	currentSprite = NULL;
}

void Button::updateState(sf::Vector2f mousePos, bool isClicked)
{
	sf::FloatRect radius = currentSprite->getGlobalBounds();
	if ((mousePos.x > radius.left) && (mousePos.x < (radius.left + radius.width))
		&& (mousePos.y > radius.top) && (mousePos.y < (radius.top + radius.height)))
	{
		if (isClicked && this->getState() < 2)
		{
			soundEffect.play();
			this->setState(2);
		}
		else if(!isClicked && this->getState() < 1)
		{
			soundEffect.play();
			this->setState(1);
		}
	} else if(this->getState())
		this->setState(0);
}

void Button::setText(std::string title)
{
	this->title.setString(title);
	sf::FloatRect titleRect = this->title.getLocalBounds();
	this->title.setOrigin(titleRect.width / 2.0f, titleRect.height / 2.0f + 10.0f);
	this->titleShadow = this->title;
	this->title.setFillColor(sf::Color::White);
	this->titleShadow.setFillColor(sf::Color(117, 76, 40));

}

void Button::setState(unsigned int state)
{
	currentState = state;
	if (currentState == 0)
		currentSprite = &defaultPlaceHolder;
	else if (currentState == 1)
		currentSprite = &mouseOverPlaceHolder;
}

unsigned int Button::getState()
{
	return this->currentState;
}

void Button::setPosition(sf::Vector2f position)
{
	defaultPlaceHolder.setPosition(position);
	mouseOverPlaceHolder.setPosition(position);
	title.setPosition(position);
}

void Button::draw()
{
	window.draw(*this->currentSprite);
	window.draw(this->titleShadow);
	window.draw(this->title);
}
