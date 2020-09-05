#include "Menu.h"
#include "button.h"
#include "common.h"
#include "onePlayer.h"
#include "twoPlayers.h"
#include "SaveLoadManager.h"
#include "HighScoreManager.h"

void common::initGame()
{
	srand((unsigned int)time(NULL));

	window.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "CARO GAME", sf::Style::Close);
	window.setFramerateLimit(60);

	t_menuBackground.loadFromFile("image/menu_background.png");
	menuBackground.setTexture(t_menuBackground);

	t_gameBackground.loadFromFile("image/game_background.png");
	gameBackground.setTexture(t_gameBackground);

	t_logo.loadFromFile("image/menu_logo.png");
	logo.setTexture(t_logo);
	logo.setOrigin(logo.getLocalBounds().width / 2.0f, logo.getLocalBounds().height / 2.0f);
	logo.setPosition(WINDOW_WIDTH / 2.0f, 110.0f);
	icon.loadFromFile("image/logo.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

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
	gameMusic.setVolume(50);

	s_optionSound.loadFromFile("sound/optionSound.ogg");
	optionSound.setBuffer(s_optionSound);

	s_moveSound.loadFromFile("sound/moveSound.ogg");
	moveSound.setBuffer(s_moveSound);

	s_winSound.loadFromFile("sound/winSound.ogg");
	winSound.setBuffer(s_winSound);

	s_loseSound.loadFromFile("sound/loseSound.ogg");
	loseSound.setBuffer(s_loseSound);

	// Blue
	t_blueButton_default.loadFromFile("image/Button/Blue/Button-default.png");
	t_blueButton_default.setSmooth(true);
	t_blueButton_mouseOver.loadFromFile("image/Button/Blue/Button-mouseOver.png");
	t_blueButton_mouseOver.setSmooth(true);

	// Brown
	t_brownButton_default.loadFromFile("image/Button/Brown/Button-default.png");
	t_brownButton_default.setSmooth(true);
	t_brownButton_mouseOver.loadFromFile("image/Button/Brown/Button-mouseOver.png");
	t_brownButton_mouseOver.setSmooth(true);

	// Green
	t_greenButton_default.loadFromFile("image/Button/Green/Button-default.png");
	t_greenButton_default.setSmooth(true);
	t_greenButton_mouseOver.loadFromFile("image/Button/Green/Button-mouseOver.png");
	t_greenButton_mouseOver.setSmooth(true);

	// Red
	t_redButton_default.loadFromFile("image/Button/Red/Button-default.png");
	t_redButton_default.setSmooth(true);
	t_redButton_mouseOver.loadFromFile("image/Button/Red/Button-mouseOver.png");
	t_redButton_mouseOver.setSmooth(true);

	// Yellow
	t_yellowButton_default.loadFromFile("image/Button/Yellow/Button-default.png");
	t_yellowButton_default.setSmooth(true);
	t_yellowButton_mouseOver.loadFromFile("image/Button/Yellow/Button-mouseOver.png");
	t_yellowButton_mouseOver.setSmooth(true);

	// Name Input
	t_dialogBox.loadFromFile("image/dialogBox.png");
	t_board.loadFromFile("image/board.png");
	t_textPlaceholder.loadFromFile("image/textPlaceholder.png");
	t_navReset.loadFromFile("image/Button/Navigation/reset.png");
	t_navReset.setSmooth(true);


	// Animation
	t_cloudLeft.loadFromFile("image/asset/cloudLeft.png");
	t_cloudLeft.setSmooth(true);

	t_cloudRight.loadFromFile("image/asset/cloudRight.png");
	t_cloudRight.setSmooth(true);

	t_star.loadFromFile("image/asset/star.png");
	t_star.setSmooth(true);

	t_shine.loadFromFile("image/asset/shine.png");
	t_shine.setSmooth(true);

	t_smallStar.loadFromFile("image/asset/smallStar.png");
	t_smallStar.setSmooth(true);

	t_smallShine.loadFromFile("image/asset/smallShine.png");
	t_smallShine.setSmooth(true);

	t_bad.loadFromFile("image/asset/bad.png");
	t_bad.setSmooth(true);


	// About us
	aboutUsMusic.openFromFile("sound/aboutus.ogg");
	aboutUsMusic.setLoop(true);

	t_artBg.loadFromFile("image/asset/aboutus/artBg.png");
	t_artBg.setSmooth(true);

	t_artObj.loadFromFile("image/asset/aboutus/artObj.png");
	t_artObj.setSmooth(true);

	t_zoom.loadFromFile("image/asset/aboutus/zoom.png");
	t_zoom.setSmooth(true);

	t_group.loadFromFile("image/asset/aboutus/group.png");
	t_group.setSmooth(true);
	t_fit.loadFromFile("image/asset/aboutus/fit.png");
	t_fit.setSmooth(true);
	t_sLogo.loadFromFile("image/asset/aboutus/logo.png");
	t_sLogo.setSmooth(true);
}

void common::runGame()
{
	// Initializing
	Game* g = new twoPlayers(&t_gameBackground);
	
	Menu mainMenu(&t_menuBackground, Vector2f(window.getSize().x / 2.0f, MENU_TOP), MENU_BUTTON_SPACING);
	Menu newGameMenu(&t_menuBackground, Vector2f(window.getSize().x / 2.0f, MENU_TOP), MENU_BUTTON_SPACING);
	Menu botMenu(&t_menuBackground, Vector2f(window.getSize().x / 2.0f, MENU_TOP), MENU_BUTTON_SPACING);
	
	SaveLoadManager  LoadGameMenu;
	HighScoreManager HighScore;

	int choice = 1;

	// Opening Screen
	displayOpeningScreen();

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

	// Init Event
	Event e;

	// Play mainMenu music
	menuMusic.play();

	// Opening Window
	while (window.isOpen())
	{
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
							if (g->isContinue()) g->continueGame();
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
							std::string filename = "";
							int typeGame = LoadGameMenu.loadForGame(filename);

							if (typeGame != -1)
							{
								if (typeGame != g->getType())
									delete g;

								switch (typeGame)
								{
								case 0:
									g = new twoPlayers(&t_gameBackground);
									g->loadGame(filename);
									g->continueGame();
									break;
								case 1:
									g = new onePlayer(&t_gameBackground, 1);
									g->loadGame(filename);
									g->continueGame();
									break;
								case 2:
									g = new onePlayer(&t_gameBackground, 2);
									g->loadGame(filename);
									g->continueGame();
									break;
								case 3:
									g = new onePlayer(&t_gameBackground, 3);
									g->loadGame(filename);
									g->continueGame();
									break;

								}
							}
							break;
						}
						case 3:
						{
							HighScore.showHighScore();
							break;
						}
						case 4:
						{
							aboutMenu();
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
				else if (e.type == sf::Event::MouseMoved) mainMenu.update(sf::Vector2f((float)e.mouseMove.x, (float)e.mouseMove.y), false);
			}
			/// <summary>
			/// DO NOT REMOVE THIS!!!
			/// </summary>
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
				else if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
				{
					newGameMenu.isActive = false;
					mainMenu.isActive = true;
				}
				else if (e.type == sf::Event::MouseButtonPressed)
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
							delete g;
							g = new twoPlayers(&t_gameBackground);
							g->newGame();
							if (g->isContinue()) mainMenu.setActiveBtn(0, true);
							else mainMenu.setActiveBtn(0, false);
							mainMenu.isActive = true;
							newGameMenu.isActive = false;
							break;
						}
					}
				}
				else if (e.type == sf::Event::MouseMoved) newGameMenu.update(sf::Vector2f((float)e.mouseMove.x, (float)e.mouseMove.y), false);
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
				else if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
				{
					newGameMenu.isActive = true;
					botMenu.isActive = false;
				}
				else if (e.type == sf::Event::MouseButtonPressed)
				{
					botMenu.update(sf::Vector2f((float)e.mouseButton.x, (float)e.mouseButton.y), true);
					if (e.mouseButton.button == sf::Mouse::Left)
					{
						switch (botMenu.selectedItemIndex)
						{
						case 0:
							delete g;
							g = new onePlayer(&t_gameBackground, 1);
							g->newGame();
							if (g->isContinue()) mainMenu.setActiveBtn(0, true);
							else mainMenu.setActiveBtn(0, false);
							mainMenu.isActive = true;
							botMenu.isActive = false;
							break;
						case 1:
							delete g;
							g = new onePlayer(&t_gameBackground, 2);
							g->newGame();
							if (g->isContinue()) mainMenu.setActiveBtn(0, true);
							else mainMenu.setActiveBtn(0, false);
							mainMenu.isActive = true;
							botMenu.isActive = false;
							break;
						case 2:
							delete g;
							g = new onePlayer(&t_gameBackground, 3);
							g->newGame();
							if (g->isContinue()) mainMenu.setActiveBtn(0, true);
							else mainMenu.setActiveBtn(0, false);
							mainMenu.isActive = true;
							botMenu.isActive = false;
							break;
						}
					}
				}
				else if (e.type == sf::Event::MouseMoved) botMenu.update(sf::Vector2f((float)e.mouseMove.x, (float)e.mouseMove.y), false);
			}
		}
	}

	delete g;
}

void common::displayOpeningScreen()
{
	Texture t_icon; t_icon.loadFromFile("image/group02_logo.png");
	Sprite  icon(t_icon); icon.setPosition(Vector2f(500.f, 225.f));

	Music menuStartup;
	menuStartup.openFromFile("sound/menu_startup.ogg");
	menuStartup.play();

	for (int i = 0; i <= 40; i++)
	{
		window.clear(Color::White);
		icon.setColor(sf::Color(255, 255, 255, i * 6));
		window.draw(icon);
		window.display();
	}

	sleep(milliseconds(1000));

	for (int i = 40; i >= 0; i--)
	{
		window.clear(Color::White);
		icon.setColor(sf::Color(255, 255, 255, i * 6));
		window.draw(icon);
		window.display();
	}
}

void common::aboutMenu()
{
	menuMusic.stop();
	aboutUsMusic.play();
	sf::Sprite bg(t_menuBackground), group(t_group), fit(t_fit), logo(t_sLogo);

	logo.setPosition(754.5f, 700.0f);
	group.setPosition(836.5f, 870.0f);
	fit.setPosition(716.5f, 1630.0f);

	sf::RectangleShape contentBg(sf::Vector2f(1200.0f, 700.0f)),
	top(sf::Vector2f(526.0f, 180.0f)),
	bot(sf::Vector2f(526.9f, 180.0f));

	contentBg.setFillColor(sf::Color(255, 255, 255, 0));
	top.setFillColor(sf::Color::White);
	top.setPosition(674.0f, 0.0f);
	bot.setFillColor(sf::Color::White);
	bot.setPosition(674.0f, 520.0f);

	sf::Sprite artBg(t_artBg), artObj(t_artObj), zoom(t_zoom);
	artBg.setPosition(100.0f, 207.5f);
	artObj.setPosition(120.25f, 200.0f);
	zoom.setOrigin(182.5f, 73.0f);
	zoom.setPosition(379.5f, 390.5f);

	// Dimming white
	for (int i = 0; i <= 60; ++i)
	{
		window.clear();
		contentBg.setFillColor(sf::Color(255, 255, 255, sf::Uint8(i * 4.25)));
		window.draw(bg);
		window.draw(contentBg);
		window.display();
	}

	// Text list
	std::vector<sf::Text> textList;

	textList.push_back(Text("Ho Chi Minh City University of Science", font_bebasNeueBold, 24));
	textList.push_back(Text("Viet Nam National University, Ho Chi Minh City", font_bebasNeueBold, 24));
	textList.push_back(Text("Project", font_bebasNeueBold, 24));
	textList.push_back(Text("Object Oriented Programming", font_bebasNeueBold, 40));
	textList.push_back(Text("Game CARO (Version 1.0)", font_bebasNeueBold, 30));
	textList.push_back(Text("Ho Huu Vien - 18127251", font_bebasNeueBold, 24));
	textList.push_back(Text("Pham Anh Tuan - 19127084", font_bebasNeueBold, 24));
	textList.push_back(Text("Nguyen Thanh Tinh - 19127292", font_bebasNeueBold, 24));
	textList.push_back(Text("Tran Xuan Son - 19127321", font_bebasNeueBold, 24));
	textList.push_back(Text("Special thanks to", font_bebasNeueBold, 30));
	textList.push_back(Text("PhD. Truong Toan Thinh - Theory Lecturer", font_bebasNeueBold, 24));
	textList.push_back(Text("PhD. Nguyen Thanh An - Teaching Assistant", font_bebasNeueBold, 24));
	textList.push_back(Text("M. Tran Ngoc Dat Thanh - LAB Lecturer", font_bebasNeueBold, 24));

	for (unsigned int i = 0; i < textList.size(); ++i)
	{
		textList[i].setFillColor(sf::Color(112, 112, 112));
		textList[i].setOrigin(textList[i].getLocalBounds().width / 2.0f, 0.0f);
		textList[i].setPosition(916.5f, 1110.0f + MENU_LINE_SPACING * i + 10.0f);
	}

	bool dir = true,dirText = true;
	int alpha = 100;

	bool show = false;
	Text getOut("Press any key to get back", font_bebasNeueBold, 30);
	getOut.setFillColor(Color(112, 112, 112, alpha));
	getOut.setPosition(808.0f, 444.0f);

	Event e;
	bool flag = true;
	while (window.isOpen() && flag)
	{
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				aboutUsMusic.stop();
				window.close();
			}
			if (e.type == sf::Event::KeyPressed || e.type == sf::Event::MouseButtonPressed)
			{
				menuMusic.play();
				aboutUsMusic.stop();
				flag = false;
			}
		}
		if (dir && artBg.getPosition().x < 145.0f)
		{
			zoom.rotate(0.1f);
			artBg.move(0.5f, 0.0f);
		}
		else dir = false;
		if (!dir && artBg.getPosition().x > 100.0f)
		{
			zoom.rotate(-0.1f);
			artBg.move(-0.5f, 0.0f);
		}
		else dir = true;
		if (textList.back().getPosition().y > 151.0f)
		{
			logo.move(0, -0.75f);
			group.move(0, -0.75f);
			for (unsigned int i = 0; i < textList.size(); ++i)
				textList[i].move(0, -0.75f);
		}
		else
		{
			show = true;
			if (dirText && alpha < 255)
			{
				alpha += 5;
				getOut.setFillColor(Color(112, 112, 112, alpha));
			}
			else dirText = false;
			if (!dirText && alpha > 100)
			{
				alpha -= 5;
				getOut.setFillColor(Color(112, 112, 112, alpha));
			}
			else dirText = true;
		}
		if (fit.getPosition().y > 278.0f)
			fit.move(0, -0.75f);
		window.clear();
		window.draw(contentBg);
		window.draw(logo);
		window.draw(group);
		
		for (unsigned int i = 0; i < textList.size(); ++i)
			window.draw(textList[i]);

		window.draw(fit);
		window.draw(top);
		window.draw(bot);
		window.draw(artBg);
		window.draw(artObj);
		window.draw(zoom);
		if (show) window.draw(getOut);
		window.display();
	}

	for (int i = 60; i >= 0; --i)
	{
		window.clear();
		contentBg.setFillColor(sf::Color(255, 255, 255, sf::Uint8(i * 4.25)));
		window.draw(bg);
		window.draw(contentBg);
		window.display();
	}
}