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

	font_arial.loadFromFile("font/arial.ttf");
	font_courierNew.loadFromFile("font/courierNew.ttf");
	font_bebasNeueBold.loadFromFile("font/BebasNeue-Bold.ttf");

	menuMusic.openFromFile("sound/menu_music.ogg");
	menuMusic.setLoop(true);

	s_optionSound.loadFromFile("sound/optionSound.ogg");
	optionSound.setBuffer(s_optionSound);

	// Green
	if (!t_greenButton_default.loadFromFile("image/Button/Green/Button-default.png"))
		std::cout << "Can not load texture!\n";
	if (!t_greenButton_mouseOver.loadFromFile("image/Button/Green/Button-mouseOver.png"))
		std::cout << "Can not load texture!\n";
	if (!t_greenButton_pressed.loadFromFile("image/Button/Green/Button-pressed.png"))
		std::cout << "Can not load texture!\n";

	// Blue
	if (!t_blueButton_default.loadFromFile("image/Button/Blue/Button-default.png"))
		std::cout << "Can not load texture!\n";
	if (!t_blueButton_mouseOver.loadFromFile("image/Button/Blue/Button-mouseOver.png"))
		std::cout << "Can not load texture!\n";
	if (!t_blueButton_pressed.loadFromFile("image/Button/Blue/Button-pressed.png"))
		std::cout << "Can not load texture!\n";

	// Brown
	if (!t_brownButton_default.loadFromFile("image/Button/Brown/Button-default.png"))
		std::cout << "Can not load texture!\n";
	if (!t_brownButton_mouseOver.loadFromFile("image/Button/Brown/Button-mouseOver.png"))
		std::cout << "Can not load texture!\n";
	if (!t_brownButton_pressed.loadFromFile("image/Button/Brown/Button-pressed.png"))
		std::cout << "Can not load texture!\n";

	// Red
	if (!t_redButton_default.loadFromFile("image/Button/Red/Button-default.png"))
		std::cout << "Can not load texture!\n";
	if (!t_redButton_mouseOver.loadFromFile("image/Button/Red/Button-mouseOver.png"))
		std::cout << "Can not load texture!\n";
	if (!t_redButton_pressed.loadFromFile("image/Button/Red/Button-pressed.png"));

	// Yellow
	if (!t_yellowButton_default.loadFromFile("image/Button/Yellow/Button-default.png"))
		std::cout << "Can not load texture!\n";
	if (!t_yellowButton_mouseOver.loadFromFile("image/Button/Yellow/Button-mouseOver.png"))
		std::cout << "Can not load texture!\n";
	if (!t_yellowButton_pressed.loadFromFile("image/Button/Yellow/Button-pressed.png"))
		std::cout << "Can not load texture!\n";

}

void common::runGame()
{
	// Initializing
	game g;
	mainMenu m;
	subMenu sm;
	int choice = 1;
	Button btn(&t_blueButton_default, &t_blueButton_mouseOver, &t_blueButton_pressed, &s_optionSound, "NEW GAME", sf::Vector2f(500.0f, 50.0f));
	// Opening
	//m.displayOpeningScreen();

	// Choosing theme
	//m.chooseTheme();

	// Play mainMenu music
	//menuMusic.play();

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
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			btn.updateState(sf::Vector2f(mousePos), true);
		else if (e.type == sf::Event::MouseMoved)
			btn.updateState(sf::Vector2f(mousePos), false);
		std::cout << mousePos.x << " " << mousePos.y << std::endl;
		window.clear();
		btn.draw();
		window.display();
		//m.displayMainMenu(choice);
	}
}