#include "common.h"

void mainMenu::displayOpeningScreen()
{
	Texture t_icon; t_icon.loadFromFile("image/group02_logo.png");
	Sprite icon(t_icon); icon.setPosition(Vector2f(500.f, 225.f));

	Music menuStartup;
	menuStartup.openFromFile("sound/menu_startup.ogg");
	menuStartup.play();

	for (int i = 0; i <= 255; i++)
	{
		window.clear(Color::White);
		icon.setColor(sf::Color(255, 255, 255, i));
		window.draw(icon);
		window.display(); 
	}

	sleep(milliseconds(1500));

	for (int i = 255; i >= 0; i--)
	{
		window.clear(Color::White);
		icon.setColor(sf::Color(255, 255, 255, i));
		window.draw(icon);
		window.display();
	}
}

void mainMenu::chooseTheme()
{
	bool isDone = false;
	do
	{
		Event e;

		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				isDone = true;
				window.close();
			}

			if (e.type == Event::KeyPressed)
			{
				switch (e.key.code)
				{
				case Keyboard::Left:
				{
					
					break;
				}
				case Keyboard::Right:
				{
					
					break;
				}
				case Keyboard::Enter:
				{
					isDone = true;
					break;
				}
				}
			}
		}
		
		window.clear(Color::White);
		window.display();
	} while (!isDone);
}

void mainMenu::displayMainMenu(int choice)
{
	window.clear(Color::White);
	window.draw(menuBackground);
	window.draw(logo);

	Texture t; t.loadFromFile("image/menu_choosing.png");
	Sprite choosing(t); choosing.setPosition(Vector2f(980.f, 435.f + choice * 80.f));
	window.draw(choosing);

	Text text[7];
	text[0].setString("Continue");
	text[1].setString("New Game");
	text[2].setString("Load Game");
	text[3].setString("High Score");
	text[4].setString("Settings");
	text[5].setString("About");
	text[6].setString("Exit");

	for (int i = 0; i < 7; i++)
	{
		text[i].setFont(font_arial);
		text[i].setCharacterSize(40);
		text[i].setFillColor((i == choice) ? Color::White : Color::Black);
		if (i == choice) text[i].setStyle(Text::Bold);
		text[i].setPosition(Vector2f(1000.f, 450.f + i * 80.f));
		window.draw(text[i]);
	}

	RectangleShape line(Vector2f(5.f, 560.f));
	line.setFillColor(Color::Black);
	line.setPosition(Vector2f(980.f, 435.f));
	window.draw(line);

	Text describeText;
	Texture t_describeImage;
	Sprite describeImage;

	switch (choice)
	{
	case 0:
	{
		describeText.setString("Continue the game you're playing...");
		t_describeImage.loadFromFile("image/menu_option_0.png");
		break;
	}
	case 1:
	{
		describeText.setString("Start a new game! \nPlay with AI or Play with a friend!");
		t_describeImage.loadFromFile("image/menu_option_1.png");
		break;
	}
	case 2:
	{
		describeText.setString("Load a saved game.");
		t_describeImage.loadFromFile("image/menu_option_2.png");
		break;
	}
	case 3:
	{
		describeText.setString("High Score! Let's be the best!");
		t_describeImage.loadFromFile("image/menu_option_3.png");
		break;
	}
	case 4:
	{
		describeText.setString("Configure this game.");
		t_describeImage.loadFromFile("image/menu_option_4.png");
		break;
	}
	case 5:
	{
		describeText.setString("About this game...");
		t_describeImage.loadFromFile("image/menu_option_5.png");
		break;
	}
	case 6:
	{
		describeText.setString("Exiting...");
		t_describeImage.loadFromFile("image/menu_option_6.png");
		break;
	}
	}
	describeText.setFont(font_arial);
	describeText.setCharacterSize(40);
	describeText.setFillColor(Color::Black);
	describeText.setPosition(Vector2f(100.f, 500.f));
	window.draw(describeText);

	describeImage.setTexture(t_describeImage);
	describeImage.setPosition(Vector2f(300.f, 650.f));
	window.draw(describeImage);

	window.display();
}