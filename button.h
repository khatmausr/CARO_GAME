#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>

class Button
{
private:
	sf::Sound    soundEffect;

	sf::Sprite   defaultPlaceHolder;
	sf::Sprite   mouseOverPlaceHolder;

	sf::Text     title;
	sf::Text     titleShadow;

	sf::Sprite*  currentSprite;

	unsigned int currentState; // 0 : default | 1 : mouse over OR selected | 2 : pressed

public:
	bool isActive;

	// Constructors of Button
	Button(sf::Texture* defaultTexture,sf::Texture* mouseOverTexture,sf::SoundBuffer* soundBuffer, std::string title, sf::Vector2f position);
	Button(const Button& btn, sf::Vector2f position);

	// Destructor
	~Button();

	// Methods
	void update(sf::Vector2f mousePos, bool isClicked);	

	void setText(std::string title);	
	void setState(unsigned int state);
	void setPosition(sf::Vector2f position);
	void setScale(float scaleX = 1.0f, float scaleY = 1.0f);

	unsigned int getState();
	sf::Vector2f getPosition();
	sf::Vector2f getScale();
	
	void draw();
};

