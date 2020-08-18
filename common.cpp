#include "common.h"

void common::initGame()
{
	window.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "CARO GAME");
	window.setFramerateLimit(60);

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
	font_bebasNeueBold.loadFromFile("font/BebasNeue-Bold.ttf");

	menuMusic.openFromFile("sound/menu_music.ogg");
	menuMusic.setLoop(true);

	s_optionSound.loadFromFile("sound/optionSound.ogg");
	optionSound.setBuffer(s_optionSound);

	// Blue
	if (!t_blueButton_default.loadFromFile("image/Button/Blue/Button-default.png"))
		std::cout << "Can not load texture!\n";
	if (!t_blueButton_mouseOver.loadFromFile("image/Button/Blue/Button-mouseOver.png"))
		std::cout << "Can not load texture!\n";

	// Brown
	if (!t_brownButton_default.loadFromFile("image/Button/Brown/Button-default.png"))
		std::cout << "Can not load texture!\n";
	if (!t_brownButton_mouseOver.loadFromFile("image/Button/Brown/Button-mouseOver.png"))
		std::cout << "Can not load texture!\n";

	// Green
	if (!t_greenButton_default.loadFromFile("image/Button/Green/Button-default.png"))
		std::cout << "Can not load texture!\n";
	if (!t_greenButton_mouseOver.loadFromFile("image/Button/Green/Button-mouseOver.png"))
		std::cout << "Can not load texture!\n";

	// Red
	if (!t_redButton_default.loadFromFile("image/Button/Red/Button-default.png"))
		std::cout << "Can not load texture!\n";
	if (!t_redButton_mouseOver.loadFromFile("image/Button/Red/Button-mouseOver.png"))
		std::cout << "Can not load texture!\n";

	// Yellow
	if (!t_yellowButton_default.loadFromFile("image/Button/Yellow/Button-default.png"))
		std::cout << "Can not load texture!\n";
	if (!t_yellowButton_mouseOver.loadFromFile("image/Button/Yellow/Button-mouseOver.png"))
		std::cout << "Can not load texture!\n";

}

void common::runGame()
{
	// Initializing
	game g;
	mainMenu m;
	Menu mainMenu(&t_menuBackground, Vector2f(window.getSize().x / 2.0f, MENU_TOP), MENU_BUTTON_SPACING);
	Menu newGameMenu(&t_menuBackground, Vector2f(window.getSize().x / 2.0f, MENU_TOP), MENU_BUTTON_SPACING);
	Menu botMenu(&t_menuBackground, Vector2f(window.getSize().x / 2.0f, MENU_TOP), MENU_BUTTON_SPACING);
	//subMenu sm;
	int choice = 1;
	//Button btn(&t_blueButton_default, &t_blueButton_mouseOver, &t_blueButton_pressed, &s_optionSound, "NEW GAME", sf::Vector2f(500.0f, 50.0f));
	// Opening
	m.displayOpeningScreen();
	window.setFramerateLimit(60);

	// Init menu
	mainMenu.pushButton(2, "CONTINUE");
	mainMenu.pushButton(0, "NEW GAME");
	mainMenu.pushButton(1, "LOAD GAME");
	mainMenu.pushButton(1, "HIGH SCORE");
	mainMenu.pushButton(1, "ABOUT");
	mainMenu.pushButton(3, "QUIT");
	mainMenu.setActiveBtn(0, false);
	mainMenu.isActive = true;

	// Init newGameMenu
	newGameMenu.pushButton(2, "SINGLE PLAYER");
	newGameMenu.pushButton(0, "TWO PLAYERS");

	// Init botMenu
	botMenu.pushButton(2, "EASY");
	botMenu.pushButton(4, "MEDIUM");
	botMenu.pushButton(3, "HARD");

	// Init fundamental

	// Choosing theme
	//m.chooseTheme();

	// Play mainMenu music
	menuMusic.play();

	// Opening Window
	while (window.isOpen())
	{
		Event e;
		/*while (window.pollEvent(e))
			if (e.type == sf::Event::Closed) window.close();*/
		while (mainMenu.isActive)
		{
			window.clear();
			mainMenu.draw();
			window.display();
			while (window.pollEvent(e))
			{
				if (e.type == sf::Event::Closed)
				{
					window.close();
					mainMenu.isActive = false;
				}
				if (e.type == sf::Event::MouseButtonPressed)
				{
					mainMenu.update(sf::Vector2f((float) e.mouseButton.x, (float) e.mouseButton.y), true);
					if (e.mouseButton.button == sf::Mouse::Left)
					{
						switch (mainMenu.selectedItemIndex)
						{
						case 0:
						{
							g.continueGame();
							//if(!g.isContinue()) mainMenu.setActive(false);
							break;
						}
						case 1:
						{
							newGameMenu.isActive = true;
							mainMenu.isActive = false;
							break;
						}
						case 2:
						{
							//sm.loadGameMenu(g);
							//mainMenu.setActive(false);
							break;
						}
						case 3:
						{
							//sm.highScoreMenu();
							//mainMenu.setActive(false);
							break;
						}
						case 4:
						{
							//sm.aboutMenu();
							//mainMenu.setActive(false);
							break;
						}
						case 5:
						{
							window.close();
							mainMenu.isActive = false;
							break;
						}
						}
					}
				}
				else if (e.type == sf::Event::MouseMoved)
					mainMenu.update(sf::Vector2f((float) e.mouseMove.x, (float) e.mouseMove.y), false);
			}
		}
		while (newGameMenu.isActive)
		{
			window.clear();
			newGameMenu.draw();
			window.display();
			while (window.pollEvent(e))
			{
				if (e.type == sf::Event::Closed)
				{
					window.close();
					newGameMenu.isActive = false;
				}
				if (e.type == sf::Event::MouseButtonPressed)
				{
					newGameMenu.update(sf::Vector2f((float) e.mouseButton.x, (float) e.mouseButton.y), true);
					if (e.mouseButton.button == sf::Mouse::Left)
					{
						switch (newGameMenu.selectedItemIndex)
						{
						case 0:
							botMenu.isActive = true;
							newGameMenu.isActive = false;
							break;
						case 1:
							g.startTwoPlayers();
							if (g.isContinue()) mainMenu.setActiveBtn(0, true);
							else mainMenu.setActiveBtn(0, false);
							mainMenu.isActive = true;
							newGameMenu.isActive = false;
							break;
						}
					}
				}
				else if (e.type == sf::Event::MouseMoved)
					newGameMenu.update(sf::Vector2f((float) e.mouseMove.x, (float) e.mouseMove.y), false);
			}
		}
		while (botMenu.isActive)
		{
			window.clear();
			botMenu.draw();
			window.display();
			while (window.pollEvent(e))
			{
				if (e.type == sf::Event::Closed)
				{
					window.close();
					botMenu.isActive = false;
				}
				if (e.type == sf::Event::MouseButtonPressed)
				{
					botMenu.update(sf::Vector2f((float) e.mouseButton.x, (float) e.mouseButton.y), true);
					if (e.mouseButton.button == sf::Mouse::Left)
					{
						switch (botMenu.selectedItemIndex)
						{
						case 0:
							break;
						case 1:
							break;
						case 3:
							break;
						}
					}
				}
				else if (e.type == sf::Event::MouseMoved)
					botMenu.update(sf::Vector2f((float) e.mouseMove.x, (float) e.mouseMove.y), false);
			}
		}

	}

}