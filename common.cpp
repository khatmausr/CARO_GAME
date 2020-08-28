#include "common.h"
#include "mainMenu.h"
#include "Menu.h"
#include "onePlayer.h"
#include "twoPlayers.h"
#include "button.h"
void common::initGame()
{
	srand((unsigned int)time(NULL));

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

	t_cursor_X.loadFromFile("image/x_cursor.png"); t_cursor_X.setSmooth(true);
	cursor_X.setTexture(t_cursor_X);

	t_cursor_O.loadFromFile("image/o_cursor.png"); t_cursor_O.setSmooth(true);
	cursor_O.setTexture(t_cursor_O);

	t_x_big.loadFromFile("image/x_big.png"); t_x_big.setSmooth(true);
	x_big.setTexture(t_x_big);
	x_big.setOrigin(x_big.getLocalBounds().width / 2.0f, x_big.getLocalBounds().height / 2.0f);
	x_big.setPosition(Vector2f(150.f, 365.f));

	t_o_big.loadFromFile("image/o_big.png"); t_o_big.setSmooth(true);
	o_big.setTexture(t_o_big);
	o_big.setOrigin(o_big.getLocalBounds().width / 2.0f, o_big.getLocalBounds().height / 2.0f);
	o_big.setPosition(Vector2f(1060.f, 365.f));

	font_arial.loadFromFile("font/arial.ttf");
	font_courierNew.loadFromFile("font/courierNew.ttf");
	font_bebasNeueBold.loadFromFile("font/BebasNeue-Bold.ttf");
	font_robotoMonoBold.loadFromFile("font/RobotoMono-Bold.ttf");

	menuMusic.openFromFile("sound/menu_music.ogg");
	menuMusic.setLoop(true);

	gameMusic.openFromFile("sound/game_music.ogg");
	gameMusic.setLoop(true);

	s_optionSound.loadFromFile("sound/optionSound.ogg");
	optionSound.setBuffer(s_optionSound);

	// Blue
	t_blueButton_default.loadFromFile("image/Button/Blue/Button-default.png");
	t_blueButton_mouseOver.loadFromFile("image/Button/Blue/Button-mouseOver.png");

	// Brown
	t_brownButton_default.loadFromFile("image/Button/Brown/Button-default.png");
	t_brownButton_mouseOver.loadFromFile("image/Button/Brown/Button-mouseOver.png");

	// Green
	t_greenButton_default.loadFromFile("image/Button/Green/Button-default.png");
	t_greenButton_mouseOver.loadFromFile("image/Button/Green/Button-mouseOver.png");

	// Red
	t_redButton_default.loadFromFile("image/Button/Red/Button-default.png");
	t_redButton_mouseOver.loadFromFile("image/Button/Red/Button-mouseOver.png");

	// Yellow
	t_yellowButton_default.loadFromFile("image/Button/Yellow/Button-default.png");
	t_yellowButton_mouseOver.loadFromFile("image/Button/Yellow/Button-mouseOver.png");

	// Name Input
	t_dialogBox.loadFromFile("image/dialogBox.png");
	t_textPlaceholder.loadFromFile("image/textPlaceholder.png");
	t_navBack.loadFromFile("image/Button/Navigation/back.png");
	t_navOk.loadFromFile("image/Button/Navigation/ok.png");

}

void common::runGame()
{
	// Initializing
	Game* g2 = new twoPlayers(&t_gameBackground);
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
					mainMenu.update(sf::Vector2f((float)e.mouseButton.x, (float)e.mouseButton.y), true);
					if (e.mouseButton.button == sf::Mouse::Left)
					{
						switch (mainMenu.selectedItemIndex)
						{
						case 0:
						{
							if (g2->isContinue()) g2->continueGame();
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
							aboutMenu();
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
					mainMenu.update(sf::Vector2f((float)e.mouseMove.x, (float)e.mouseMove.y), false);
			}

			if (!window.isOpen()) mainMenu.isActive = false;
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
					newGameMenu.update(sf::Vector2f((float)e.mouseButton.x, (float)e.mouseButton.y), true);
					if (e.mouseButton.button == sf::Mouse::Left)
					{
						switch (newGameMenu.selectedItemIndex)
						{
						case 0:
							botMenu.isActive = true;
							newGameMenu.isActive = false;
							break;
						case 1:
							delete g2;
							g2 = new twoPlayers(&t_gameBackground);
							g2->newGame();
							if (g2->isContinue()) mainMenu.setActiveBtn(0, true);
							else mainMenu.setActiveBtn(0, false);
							mainMenu.isActive = true;
							newGameMenu.isActive = false;
							break;
						}
					}
				}
				else if (e.type == sf::Event::MouseMoved)
					newGameMenu.update(sf::Vector2f((float)e.mouseMove.x, (float)e.mouseMove.y), false);
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
					botMenu.update(sf::Vector2f((float)e.mouseButton.x, (float)e.mouseButton.y), true);
					if (e.mouseButton.button == sf::Mouse::Left)
					{
						switch (botMenu.selectedItemIndex)
						{
						case 0:
							delete g2;
							g2 = new onePlayer(&t_gameBackground, 1);
							g2->newGame();
							if (g2->isContinue()) mainMenu.setActiveBtn(0, true);
							else mainMenu.setActiveBtn(0, false);
							mainMenu.isActive = true;
							botMenu.isActive = false;
							break;
						case 1:
							delete g2;
							g2 = new onePlayer(&t_gameBackground, 2);
							g2->newGame();
							if (g2->isContinue()) mainMenu.setActiveBtn(0, true);
							else mainMenu.setActiveBtn(0, false);
							mainMenu.isActive = true;
							botMenu.isActive = false;
							break;
						case 2:
							delete g2;
							g2 = new onePlayer(&t_gameBackground, 3);
							g2->newGame();
							if (g2->isContinue()) mainMenu.setActiveBtn(0, true);
							else mainMenu.setActiveBtn(0, false);
							mainMenu.isActive = true;
							botMenu.isActive = false;
							break;
						}
					}
				}
				else if (e.type == sf::Event::MouseMoved)
					botMenu.update(sf::Vector2f((float)e.mouseMove.x, (float)e.mouseMove.y), false);
			}
		}

	}
	delete g2;
}

void common::aboutMenu()
{
	sf::Sprite bg(t_menuBackground);
	sf::RectangleShape contentBg(sf::Vector2f(800.0f, 530.0f));
	contentBg.setFillColor(sf::Color(0, 0, 0, 150));
	contentBg.setOrigin(contentBg.getLocalBounds().width / 2.0f, 0);
	contentBg.setPosition(WINDOW_WIDTH / 2.0f, 170.0f);
	std::vector<sf::Text> textList;

	textList.push_back(Text("Ho Chi Minh City University of Science", font_robotoMonoBold, 24));
	textList.push_back(Text("Viet Nam National University, Ho Chi Minh City", font_robotoMonoBold, 24));
	textList.push_back(Text("Project", font_robotoMonoBold, 24));
	textList.push_back(Text("Object Oriented Programming", font_robotoMonoBold, 40));
	textList.push_back(Text("Game CARO (Version 1.0)", font_robotoMonoBold, 30));
	textList.push_back(Text("Ho Huu Vien                               18127251", font_robotoMonoBold, 24));
	textList.push_back(Text("Pham Anh Tuan                             19127084", font_robotoMonoBold, 24));
	textList.push_back(Text("Nguyen Thanh Tinh                         19127292", font_robotoMonoBold, 24));
	textList.push_back(Text("Tran Xuan Son                             19127321", font_robotoMonoBold, 24));
	textList.push_back(Text("Special thanks to", font_robotoMonoBold, 30));
	textList.push_back(Text("M. Truong Toan Thinh      -        Theory Lecturer", font_robotoMonoBold, 24));
	textList.push_back(Text("M. Nguyen Thanh An        -     Teaching Assistant", font_robotoMonoBold, 24));
	textList.push_back(Text("M. Tran Ngoc Dat Thanh    -           LAB Lecturer", font_robotoMonoBold, 24));

	window.clear();
	window.draw(bg);
	window.draw(contentBg);
	for (int i = 0; i < textList.size(); ++i)
	{
		textList[i].setFillColor(sf::Color::White);
		textList[i].setOrigin(textList[i].getLocalBounds().width / 2.0f + 10.0f, 0);
		textList[i].setPosition(WINDOW_WIDTH / 2.0f, 170.0f + MENU_LINE_SPACING * i + 10.0f);
		window.draw(textList[i]);
	}
	window.display();
	bool isExit = false;
	while (!isExit)
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				isExit = true;
				window.close();
			}
			if (e.type == sf::Event::KeyPressed)
				return;
		}
	}
}
