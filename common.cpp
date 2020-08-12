#include "common.h"

void common::initGame()
{
	window.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "CARO GAME");

	t_menuBackground.loadFromFile("image/menu_background.png");
	menuBackground.setTexture(t_menuBackground);

	t_gameBackground.loadFromFile("image/game_background.png");
	gameBackground.setTexture(t_gameBackground);

	t_logo.loadFromFile("image/menu_logo.png");
	logo.setTexture(t_logo); logo.setPosition(Vector2f(450.f, 50.f));

	t_button_X.loadFromFile("image/X.png");
	button_X.setTexture(t_button_X);

	t_button_O.loadFromFile("image/O.png");
	button_O.setTexture(t_button_O);

	font_arial.loadFromFile("font/arial.ttf");
	font_courierNew.loadFromFile("font/courierNew.ttf");

	menuMusic.openFromFile("sound/menu_music.ogg");
	menuMusic.setLoop(true);

	s_optionSound.loadFromFile("sound/optionSound.ogg");
	optionSound.setBuffer(s_optionSound);
}

void common::runGame()
{
	// Initializing
	game g;
	mainMenu m;
	subMenu sm;
	int choice = 1;

	// Opening
	m.displayOpeningScreen();

	// Choosing theme
	m.chooseTheme();

	// Play mainMenu music
	menuMusic.play();

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