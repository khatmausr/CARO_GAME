#include "common.h"

void common::initGame()
{
	window.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "CARO GAME");

	t_menuBackground.loadFromFile("image/menu_background.png");
	menuBackground.setTexture(t_menuBackground);

	t_gameBackground.loadFromFile("image/game_background.png");
	gameBackground.setTexture(t_gameBackground);

	t_logo; t_logo.loadFromFile("image/menu_logo.png");
	logo.setTexture(t_logo); logo.setPosition(Vector2f(450.f, 50.f));

	font_arial.loadFromFile("font/arial.ttf");
	font_courierNew.loadFromFile("font/courierNew.ttf");

	menuMusic.openFromFile("sound/menu_music.ogg");
	menuMusic.setLoop(true);

	s_optionSound.loadFromFile("sound/optionSound.ogg");
	optionSound.setBuffer(s_optionSound);
}

void common::runGame()
{
	// Starting screen
	Texture t_icon; t_icon.loadFromFile("image/group02_logo.png");
	Sprite icon(t_icon); icon.setPosition(Vector2f(850.f, 400.f));

	Music menuStartup;
	menuStartup.openFromFile("sound/menu_startup.ogg");
	menuStartup.play();

	for (int i = 0; i < 256; i++)
	{
		window.clear(Color::White);
		icon.setColor(sf::Color(255, 255, 255, i));
		window.draw(icon);
		window.display();
	}
	for (int i = 0; i < 1000; i++)
	{
		window.clear(Color::White);
		window.draw(icon);
		window.display();
	}
	for (int i = 255; i >= 0; i--)
	{
		window.clear(Color::White);
		icon.setColor(sf::Color(255, 255, 255, i));
		window.draw(icon);
		window.display();
	}

	menuMusic.play();

	// Initializing Menu
	game g;
	mainMenu m;
	subMenu sm;
	int choice = 1;

	// Opening Window
	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed) window.close();

			if (e.type == Event::KeyPressed)
				switch (e.key.code)
				{
				case Keyboard::Up:
				{
					if (choice > 0)
					{
						optionSound.play();
						choice--;
					}
					break;
				}
				case Keyboard::Down:
				{
					if (choice < 6)
					{
						optionSound.play();
						choice++;
					}
					break;
				}
				case Keyboard::Enter:
				{
					optionSound.play();
					switch (choice)
					{
					case 0:
					{
						g.startTwoPlayers();
						break;
					}
					case 1:
					{
						sm.newGameMenu(g);
						break;
					}
					case 2:
					{
						sm.loadGameMenu(g);
						break;
					}
					case 3:
					{
						sm.highScoreMenu();
						break;
					}
					case 4:
					{
						sm.settingsMenu();
						break;
					}
					case 5:
					{
						sm.aboutMenu();
						break;
					}
					case 6:
					{
						window.close();
						break;
					}
					}
					break;
				}
				}
		}
		m.displayMainMenu(choice);
	}
}