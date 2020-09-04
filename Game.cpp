#include "Game.h"
#include "SaveLoadManager.h"
#include "HighScoreManager.h"
#include "button.h"
void Game::continueGame()
{
	isExit = false;
	runGame();
}

void Game::newGame()
{
	scoreX = scoreO = 0; playerName[0] = ""; playerName[1] = "";
	resetData(); turn = 1; isExit = false;
	askForName();
	runGame();
}

void Game::askForLoad()
{
	// Declaire some objects
	RectangleShape tint(Vector2f((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT));

	Text txt_title, txt_filename, txt_describe, txt_isAvailable;

	txt_title.setFont(font_arial);
	txt_title.setFillColor(Color::White);
	txt_title.setCharacterSize(100);
	txt_title.setStyle(Text::Bold);
	txt_title.setPosition(Vector2f(150.f, 200.f));
	txt_title.setString("Directly Load Game");

	txt_filename.setFont(font_arial);
	txt_filename.setFillColor(Color::White);
	txt_filename.setCharacterSize(40);
	txt_filename.setPosition(Vector2f(150.f, 400.f));
	txt_filename.setString(".SGO");

	txt_describe.setFont(font_arial);
	txt_describe.setFillColor(Color::White);
	txt_describe.setCharacterSize(30);
	txt_describe.setStyle(Text::Bold);
	txt_describe.setPosition(Vector2f(20.f, 650.f));
	txt_describe.setString("When you're done, Press 'ENTER' to load. Or Press 'ESC' to return to the game...");

	txt_isAvailable.setFont(font_arial);
	txt_isAvailable.setFillColor(Color::Red);
	txt_isAvailable.setCharacterSize(20);
	txt_isAvailable.setPosition(Vector2f(900.f, 420.f));
	txt_isAvailable.setString("This file is unavailable!");

	// Dimming
	for (int i = 0; i <= 20; i++)
	{
		displayGame();
		tint.setFillColor(Color(0, 0, 0, i * 10)); window.draw(tint);
		window.display();
	}

	// Refresh event
	Event temp; window.pollEvent(temp);

	// Entering
	SaveLoadManager SLM;
	bool isDone = false, isAvailable = false;
	std::string filename = "";
	while (!isDone)
	{
		Event e;

		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				exitGame();
				isDone = true;
			}

			if (e.type == Event::TextEntered)
			{
				switch (e.text.unicode)
				{
				case ASCII_BACKSPACE:
				{
					if (filename.length() > 0)
					{
						filename.pop_back();
						txt_filename.setString(filename + ".SGO");
						isAvailable = SLM.checkFile("savegame/" + filename + ".SGO", typeGame);
					}
					break;
				}
				case ASCII_ENTER:
				{
					if (isAvailable)
					{
						loadGame("savegame/" + filename + ".SGO");

						Text txt_status;
						txt_status.setFont(font_arial);
						txt_status.setCharacterSize(25);
						txt_status.setStyle(Text::Italic);
						txt_status.setString("Done!");

						for (int i = 0; i <= 25; i++)
						{
							txt_status.setFillColor(Color(0, 255, 0, i * 10));
							txt_status.setPosition(Vector2f(150.f, 400.f + 2.f * i));

							displayGame(); window.draw(tint);
							window.draw(txt_title); window.draw(txt_filename); window.draw(txt_status); window.draw(txt_describe);
							window.display();
						}

						sleep(milliseconds(1000));

						isDone = true;
					}
					break;
				}
				case ASCII_ESC:
				{
					isDone = true;
					break;
				}
				default:
				{
					if ((('a' <= e.text.unicode) && (e.text.unicode <= 'z')) || (('A' <= e.text.unicode) && (e.text.unicode <= 'Z')) ||
						(('0' <= e.text.unicode) && (e.text.unicode <= '9')) || (e.text.unicode == '_') || (e.text.unicode == '-'))
					{
						filename += e.text.unicode;
						txt_filename.setString(filename + ".SGO");
						isAvailable = SLM.checkFile("savegame/" + filename + ".SGO", typeGame);
					}
				}
				}
			}
		}

		txt_isAvailable.setString((isAvailable) ? "This file is unavailable" : "This file is available");
		txt_isAvailable.setFillColor((isAvailable) ? Color::Green : Color::Red);

		displayGame(); window.draw(tint);
		window.draw(txt_title); window.draw(txt_filename); window.draw(txt_describe); window.draw(txt_isAvailable);
		window.display();
	}

	// Dimming
	for (int i = 20; i >= 0; i--)
	{
		displayGame();
		tint.setFillColor(Color(0, 0, 0, i * 10)); window.draw(tint);
		window.display();
	}
	//return; // Leave here, ill do it later
}

void Game::askForSave()
{
	// Declaire some objects
	RectangleShape tint(Vector2f((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT));

	Text txt_title, txt_filename, txt_describe;

	txt_title.setFont(font_arial);
	txt_title.setFillColor(Color::White);
	txt_title.setCharacterSize(100);
	txt_title.setStyle(Text::Bold);
	txt_title.setPosition(Vector2f(150.f, 200.f));
	txt_title.setString("Directly Save Game");

	txt_filename.setFont(font_arial);
	txt_filename.setFillColor(Color::White);
	txt_filename.setCharacterSize(40);
	txt_filename.setPosition(Vector2f(150.f, 400.f));
	txt_filename.setString(".SGO");

	txt_describe.setFont(font_arial);
	txt_describe.setFillColor(Color::White);
	txt_describe.setCharacterSize(30);
	txt_describe.setStyle(Text::Bold);
	txt_describe.setPosition(Vector2f(20.f, 650.f));
	txt_describe.setString("When you're done, Press 'ENTER' to save. Or Press 'ESC' to return to the game...");

	// Dimming
	for (int i = 0; i <= 20; i++)
	{
		displayGame();
		tint.setFillColor(Color(0, 0, 0, i * 10)); window.draw(tint);
		window.display();
	}

	// Refresh event
	Event temp; window.pollEvent(temp);

	// Entering
	bool isDone = false;
	std::string filename = "";
	while (!isDone)
	{
		Event e;

		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				exitGame();
				isDone = true;
			}

			if (e.type == Event::TextEntered)
			{
				switch (e.text.unicode)
				{
				case ASCII_BACKSPACE:
				{
					if (filename.length() > 0)
					{
						filename.pop_back();
						txt_filename.setString(filename + ".SGO");
					}
					break;
				}
				case ASCII_ENTER:
				{
					saveGame("savegame/" + filename + ".SGO");

					Text txt_status;
					txt_status.setFont(font_arial);
					txt_status.setCharacterSize(25);
					txt_status.setStyle(Text::Italic);
					txt_status.setString("Done!");

					for (int i = 0; i <= 25; i++)
					{
						txt_status.setFillColor(Color(0, 255, 0, i * 10));
						txt_status.setPosition(Vector2f(150.f, 400.f + 2.f * i));

						displayGame(); window.draw(tint);
						window.draw(txt_title); window.draw(txt_filename); window.draw(txt_status); window.draw(txt_describe);
						window.display();
					}

					sleep(milliseconds(1000));

					isDone = true;
					break;
				}
				case ASCII_ESC:
				{
					isDone = true;
					break;
				}
				default:
				{
					if ((('a' <= e.text.unicode) && (e.text.unicode <= 'z')) || (('A' <= e.text.unicode) && (e.text.unicode <= 'Z')) ||
						(('0' <= e.text.unicode) && (e.text.unicode <= '9')) || (e.text.unicode == '_') || (e.text.unicode == '-'))
					{
						filename += e.text.unicode;
						txt_filename.setString(filename + ".SGO");
					}
				}
				}
			}
		}

		displayGame(); window.draw(tint);
		window.draw(txt_title); window.draw(txt_filename); window.draw(txt_describe);
		window.display();
	}

	// Dimming
	for (int i = 20; i >= 0; i--)
	{
		displayGame();
		tint.setFillColor(Color(0, 0, 0, i * 10)); window.draw(tint);
		window.display();
	}
}

int Game::getType()
{
	return typeGame;
}

Game::Game(sf::Texture* bgTexture)
{
	vol = true;
	background.setTexture(*bgTexture);
	cursorP = Vector2u(BOARD_SIZE / 2 - 1, BOARD_SIZE / 2 - 1);
	scoreX = scoreO = 0; playerName[0] = ""; playerName[1] = "";
	turn = 1; isExit = false;
}

Game::~Game()
{
	if (typeGame)
	{
		time_t now = time(0);
		HighScoreInfo temp; temp._ltm = new tm;
		temp._playerName = playerName[0];
		temp._typeGame = typeGame;
		temp._score = scoreX - scoreO;
		temp._scoreX = scoreX;
		temp._scoreO = scoreO;
		localtime_s(temp._ltm, &now);

		HighScoreManager HSM;
		HSM.pushHighScore(temp);
	}
}

bool Game::isContinue()
{
	return turn;
}

void Game::runGame()
{
	// Managing musics
	menuMusic.stop();
	gameMusic.play();

	// Game Window
	while (!isExit)
	{
		// Event
		Event e;

		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed) exitGame();

			if (e.type == Event::KeyPressed)
				processKeyPressed(e.key.code);
		}

		// Display
		displayGame();
		window.display();
	}

	// Managing musics after exiting the game
	gameMusic.stop();
	if (window.isOpen()) menuMusic.play();
}

void Game::resetData()
{
	b.resetBoard();
	cursorP.x = BOARD_SIZE / 2 - 1; cursorP.y = BOARD_SIZE / 2 - 1;
	turn = 0; isExit = false;
}

void Game::exitGame()
{
	turn = 0; isExit = true;
	gameMusic.stop(); menuMusic.stop();

	if (typeGame)
	{
		time_t now = time(0);
		HighScoreInfo temp; temp._ltm = new tm;
		temp._playerName = playerName[0];
		temp._typeGame = typeGame;
		temp._score = scoreX - scoreO;
		temp._scoreX = scoreX;
		temp._scoreO = scoreO;
		localtime_s(temp._ltm, &now);

		HighScoreManager HSM;
		HSM.pushHighScore(temp);
	}

	window.close();
}

void Game::saveGame(std::string fileName)
{
	// Save to origin file
	std::vector <int> dataBoard = b.exportBoard();

	saveGameData data;
	for (int i = 0; i < BOARD_SIZE * BOARD_SIZE + 2; i++) data._board[i] = dataBoard[i];
	data._typeGame = this->typeGame;
	data._turn = turn;
	data.cursorP = this->cursorP;
	data._scoreX = scoreX; data._scoreO = scoreO;
	data._isExit = isExit;

	std::fstream fout(fileName, std::ios::out | std::ios::binary);
	fout.write((char*)&data, sizeof(saveGameData));
	fout.close();

	// Push to manager file
	time_t now = time(0);
	saveGameInfo temp; temp._ltm = new tm;
	temp._filename = fileName;
	temp._typeGame = typeGame;
	temp._s1 = playerName[0];
	temp._s2 = playerName[1];
	localtime_s(temp._ltm, &now);

	SaveLoadManager SLM;
	SLM.pushSaveGame(temp);
}

void Game::loadGame(std::string fileName)
{
	saveGameData data;

	std::fstream fin(fileName, std::ios::in | std::ios::binary);
	fin.read((char*)&data, sizeof(saveGameData));
	fin.close();

	std::vector <int> dataBoard;
	for (int i = 0; i < BOARD_SIZE * BOARD_SIZE + 2; i++) dataBoard.push_back(data._board[i]);
	b.importBoard(dataBoard);
	this->typeGame = data._typeGame;
	turn = data._turn;
	this->cursorP = data.cursorP;
	scoreX = data._scoreX; scoreO = data._scoreO;
	isExit = data._isExit;
}

void Game::displayGame()
{
	// Loading some statistics
	Text txt_countX, txt_countO, txt_scoreX, txt_scoreO, txt_playerName[2],txt_playerNameS[2];

	txt_scoreX.setFont(font_bebasNeueBold);
	txt_scoreX.setFillColor(Color::White);
	txt_scoreX.setCharacterSize(100);

	txt_scoreO.setFont(font_bebasNeueBold);
	txt_scoreO.setFillColor(Color::White);
	txt_scoreO.setCharacterSize(100);


	for (int i = 0; i <= 1; i++)
	{
		txt_playerName[i].setFont(font_bebasNeueBold);
		txt_playerName[i].setFillColor(Color::White);
		txt_playerName[i].setCharacterSize(30);
		txt_playerName[i].setString(playerName[i]);
		txt_playerName[i].setOrigin(txt_playerName[i].getLocalBounds().width / 2.0f, txt_playerName[i].getLocalBounds().height / 2 + 10.0f);
	}
	txt_playerNameS[0] = txt_playerName[0]; txt_playerNameS[1] = txt_playerName[1];
	txt_playerNameS[0].setFillColor(Color::Black); txt_playerNameS[1].setFillColor(Color::Black);
	txt_playerNameS[0].setPosition(Vector2f(143.f, 70.f)); txt_playerNameS[1].setPosition(Vector2f(1053.f, 70.f));
	txt_playerName[0].setPosition(Vector2f(140.f, 70.f)); txt_playerName[1].setPosition(Vector2f(1050.f, 70.f));

	window.clear(Color::White);
	window.draw(background);

	b.displayBoard();

	txt_scoreX.setString(std::to_string(scoreX));
	txt_scoreX.setOrigin(float(txt_scoreX.getLocalBounds().width / 2.0), float(txt_scoreX.getLocalBounds().height / 2.0f + 10.0f));
	txt_scoreX.setPosition(Vector2f(130.f, 620.f));
	window.draw(txt_scoreX);

	txt_scoreO.setString(std::to_string(scoreO));
	txt_scoreO.setOrigin(float(txt_scoreO.getLocalBounds().width / 2.0), float(txt_scoreO.getLocalBounds().height / 2.0f + 10.0f));
	txt_scoreO.setPosition(Vector2f(1040.f, 620.f));
	window.draw(txt_scoreO);

	window.draw(txt_playerNameS[0]); window.draw(txt_playerNameS[1]);
	window.draw(txt_playerName[0]); window.draw(txt_playerName[1]);

	if (turn == 1)
	{
		x_big.setColor(Color(255, 255, 255, 255)); o_big.setColor(Color(255, 255, 255, 100));
		cursor_X.setPosition(Vector2f(BOARD_LEFT + cursorP.y * 30, BOARD_TOP + cursorP.x * 30));
		window.draw(cursor_X);
	}
	else if (turn == -1)
	{
		x_big.setColor(Color(255, 255, 255, 100)); o_big.setColor(Color(255, 255, 255, 255));
		cursor_O.setPosition(Vector2f(BOARD_LEFT + cursorP.y * 30, BOARD_TOP + cursorP.x * 30));
		window.draw(cursor_O);
	}

	window.draw(x_big); window.draw(o_big);
}

void Game::changeTurn()
{
	if (turn == 1) turn = -1; else turn = 1;
}

void Game::markWin(int x_begin, int y_begin, int direction)
{
	// Draw a line first
	RectangleShape line;
	line.setFillColor(Color::Black);
	int length = 0;

	switch (direction)
	{
	case 1:
	{
		line.setPosition(Vector2f((float)BOARD_LEFT + y_begin * 30.f + 16.f, (float)BOARD_TOP + x_begin * 30.f));
		length = 150;
		line.rotate(90);
		break;
	}
	case 2:
	{
		line.setPosition(Vector2f((float)BOARD_LEFT + y_begin * 30.f, (float)BOARD_TOP + x_begin * 30.f + 14.f));
		length = 150;
		break;
	}
	case 3:
	{
		line.setPosition(Vector2f((float)BOARD_LEFT + y_begin * 30.f + 3.f, (float)BOARD_TOP + x_begin * 30.f));
		length = 210;
		line.rotate(45);
		break;
	}
	case 4:
	{
		line.setPosition(Vector2f((float)BOARD_LEFT + (y_begin + 1) * 30.f, (float)BOARD_TOP + x_begin * 30.f + 2.f));
		length = 210;
		line.rotate(135);
		break;
	}
	}

	for (int i = 0; i < length; i += 5)
	{
		displayGame();
		line.setSize(Vector2f((float)i, 5.f)); window.draw(line);
		window.display();
	}
}

bool Game::displayWin(bool isDraw)
{
	// Process winner
	std::string winnerString;
	if (isDraw) winnerString = "TIE!!!";
	else
	{
		switch (turn)
		{
		case -1:
			++scoreO;
			winnerString = playerName[1];
			break;
		case 1:
			++scoreX;
			winnerString = playerName[0];
			break;
		}
		winnerString += " WON!!";
	}

	// Init
	Sprite cloudL, cloudR, star, starL, starR, shine, shineL, shineR;
	Sprite dialogBox;
	Text winner(winnerString, font_bebasNeueBold, 50);
	winner.setOrigin(winner.getLocalBounds().width / 2.0f, winner.getLocalBounds().height / 2.0f + 15.0f);
	winner.setScale(0.0f, 0.0f);

	Text winnerS(winner);
	winner.setFillColor(Color::White); winnerS.setFillColor(Color(87, 151, 255));
	winner.setPosition(WINDOW_WIDTH / 2.0f, 240.0f); winnerS.setPosition(WINDOW_WIDTH / 2.0f + 3.0f, 240.0f);

	Text title("STATISTICS", font_bebasNeueBold, 40);
	title.setOrigin(title.getLocalBounds().width / 2.0f, title.getLocalBounds().height / 2.0f + 13.0f);
	title.setScale(0.0f, 0.0f);

	Text titleS(title);
	title.setFillColor(Color::White); titleS.setFillColor(Color::Black);
	title.setPosition(WINDOW_WIDTH / 2.0f, 310.0f);	titleS.setPosition(WINDOW_WIDTH / 2.0f + 3.0f, 310.0f);

	std::vector<Text> statTitle;
	for (int i = 0; i < 2; ++i)
	{
		Text tS("", font_bebasNeueBold, 35);
		Text t(tS);
		tS.setFillColor(Color::Black);
		tS.setPosition(353.0f, 350.0f + 70.0f * i);
		tS.setScale(0.0f, 0.0f);
		t.setFillColor(Color::White);
		t.setPosition(350.0f, 350.0f + 70.0f * i);
		t.setScale(0.0f, 0.0f);
		statTitle.push_back(tS);
		statTitle.push_back(t);
	}
	statTitle[0].setString("SCORE"); statTitle[1].setString("SCORE");
	statTitle[2].setString("TICKS"); statTitle[3].setString("TICKS");

	std::vector<std::vector<Text>> stats(2);
	for (unsigned int i = 0; i < 2; ++i)
	{
		for (unsigned int j = 0; j < 2; ++j)
		{
			Text tS("", font_bebasNeueBold, 35);
			Text t(tS);
			tS.setFillColor(Color::Black);
			tS.setPosition(473.0f + j * 220.0f, 350.0f + i * 70);
			tS.setScale(0.0f, 0.0f);
			t.setFillColor(Color::White);
			t.setPosition(470.0f + j * 220.0f, 350.0f + i * 70);
			t.setScale(0.0f, 0.0f);
			stats[i].push_back(tS);
			stats[i].push_back(t);
		}
	}
	stats[0][0].setString(std::to_string(scoreX)); stats[0][1].setString(std::to_string(scoreX));
	stats[0][2].setString(std::to_string(scoreO)); stats[0][3].setString(std::to_string(scoreO));
	stats[1][0].setString(std::to_string(b.getCountX())); stats[1][1].setString(std::to_string(b.getCountX()));
	stats[1][2].setString(std::to_string(b.getCountO())); stats[1][3].setString(std::to_string(b.getCountO()));

	Button replayBtn(&t_blueButton_default, &t_blueButton_mouseOver, &s_optionSound, "[ENTER] REPLAY", Vector2f(WINDOW_WIDTH / 2.0f + 180.0f, 580.0f));
	replayBtn.setScale(0.0f, 0.0f);

	Button backMenuBtn(&t_yellowButton_default, &t_yellowButton_mouseOver, &s_optionSound, "[ESC] MENU", Vector2f(WINDOW_WIDTH / 2.0f - 180.0f, 580.0f));
	backMenuBtn.setScale(0.0f, 0.0f);

	// Configure
	cloudL.setTexture(t_cloudLeft);
	cloudL.setOrigin(cloudL.getLocalBounds().width, 0.0f);

	cloudR.setTexture(t_cloudRight);
	cloudR.setPosition(WINDOW_WIDTH, 0.0f);

	star.setTexture(t_star);
	star.setOrigin(star.getLocalBounds().width / 2.0f, star.getLocalBounds().height / 2.0f);
	star.setPosition(WINDOW_WIDTH / 2.0f, 120.0f);
	star.setScale(0.0f, 0.0f);

	starL.setTexture(t_smallStar);
	starL.setOrigin(starL.getLocalBounds().width / 2.0f, starL.getLocalBounds().height / 2.0f);
	starL.setPosition(WINDOW_WIDTH / 2.0f - 180.0f, 150.0f);
	starL.setScale(0.0f, 0.0f);


	starR.setTexture(t_smallStar);
	starR.setOrigin(starR.getLocalBounds().width / 2.0f, starR.getLocalBounds().height / 2.0f);
	starR.setPosition(WINDOW_WIDTH / 2.0f + 180.0f, 150.0f);
	starR.setScale(0.0f, 0.0f);

	shine.setTexture(t_shine);
	shine.setOrigin(shine.getLocalBounds().width / 2.0f, shine.getLocalBounds().height / 2.0f);
	shine.setPosition(WINDOW_WIDTH / 2.0f, 120.0f);
	shine.setScale(0.0f, 0.0f);

	shineL.setTexture(t_smallShine);
	shineL.setOrigin(shineL.getLocalBounds().width / 2.0f, shineL.getLocalBounds().height / 2.0f);
	shineL.setPosition(WINDOW_WIDTH / 2.0f - 180.0f, 150.0f);
	shineL.setScale(0.0f, 0.0f);

	shineR.setTexture(t_smallShine);
	shineR.setOrigin(shineR.getLocalBounds().width / 2.0f, shineR.getLocalBounds().height / 2.0f);
	shineR.setPosition(WINDOW_WIDTH / 2.0f + 180.0f, 150.0f);
	shineR.setScale(0.0f, 0.0f);

	dialogBox.setTexture(t_dialogBox);
	dialogBox.setOrigin(dialogBox.getLocalBounds().width / 2.0f, dialogBox.getLocalBounds().height / 2.0f);
	dialogBox.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
	dialogBox.setScale(0.0f, 0.0f);

	Event e;
	bool flag = true;

	winSound.play();

	while (window.isOpen() && flag)
	{
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				exitGame();
			else if (e.type == Event::KeyPressed)
			{
				switch (e.key.code)
				{
				case Keyboard::Escape:
					resetData();
					return true;
					break;
				case Keyboard::Enter:
					resetData();
					turn = 1;
					return false;
					break;
				}
			}
			else if (e.type == Event::MouseMoved)
			{
				backMenuBtn.update(sf::Vector2f((float)e.mouseMove.x, (float)e.mouseMove.y), false);
				replayBtn.update(sf::Vector2f((float)e.mouseMove.x, (float)e.mouseMove.y), false);
			}
			else if (e.type == Event::MouseButtonPressed)
			{
				backMenuBtn.update(sf::Vector2f((float)e.mouseButton.x, (float)e.mouseButton.y), true);
				if (backMenuBtn.getState() == 2)
				{
					resetData();
					return true;
				}
				replayBtn.update(sf::Vector2f((float)e.mouseButton.x, (float)e.mouseButton.y), true);
				if (replayBtn.getState() == 2)
				{
					resetData();
					turn = 1;
					return false;
				}
			}
		}
		if (cloudR.getPosition().x > 600.0f)
		{
			cloudL.move(30.0f, 0.0f);
			cloudR.move(-30.0f, 0.0f);
			dialogBox.setScale(dialogBox.getScale().x + 0.05f, dialogBox.getScale().y + 0.05f);
			titleS.setScale(titleS.getScale().x + 0.05f, titleS.getScale().y + 0.05f);
			title.setScale(title.getScale().x + 0.05f, title.getScale().y + 0.05f);
			for (unsigned int i = 0; i < statTitle.size(); ++i)
				statTitle[i].setScale(statTitle[i].getScale().x + 0.05f, statTitle[i].getScale().y + 0.05f);
			for (unsigned int i = 0; i < stats.size(); ++i)
				for (unsigned int j = 0; j < stats[i].size(); ++j)
					stats[i][j].setScale(stats[i][j].getScale().x + 0.05f, stats[i][j].getScale().y + 0.05f);
			backMenuBtn.setScale(backMenuBtn.getScale().x + 0.05f, backMenuBtn.getScale().y + 0.05f);
			replayBtn.setScale(replayBtn.getScale().x + 0.05f, replayBtn.getScale().y + 0.05f);
			winner.setScale(winner.getScale().x + 0.05f, winner.getScale().y + 0.05f);
			winnerS.setScale(winnerS.getScale().x + 0.05f, winnerS.getScale().y + 0.05f);
			shine.setScale(shine.getScale().x + 0.05f, shine.getScale().y + 0.05f);
			star.setScale(star.getScale().x + 0.05f, star.getScale().y + 0.05f);
			shineL.setScale(shineL.getScale().x + 0.05f, shineL.getScale().y + 0.05f);
			starL.setScale(starL.getScale().x + 0.05f, starL.getScale().y + 0.05f);
			shineR.setScale(shineR.getScale().x + 0.05f, shineR.getScale().y + 0.05f);
			starR.setScale(starR.getScale().x + 0.05f, starR.getScale().y + 0.05f);
		}

		// Rotate shine
		shine.rotate(1);
		shineL.rotate(1);
		shineR.rotate(1);

		window.clear();
		window.draw(menuBackground);
		window.draw(cloudL);
		window.draw(cloudR);
		window.draw(dialogBox);
		window.draw(titleS);
		window.draw(title);
		for (unsigned int i = 0; i < statTitle.size(); ++i)
			window.draw(statTitle[i]);
		for (unsigned int i = 0; i < stats.size(); ++i)
			for (unsigned int j = 0; j < stats[i].size(); ++j)
				window.draw(stats[i][j]);
		backMenuBtn.draw();
		replayBtn.draw();
		window.draw(winnerS);
		window.draw(winner);
		window.draw(shine);
		window.draw(star);
		window.draw(shineL);
		window.draw(starL);
		window.draw(shineR);
		window.draw(starR);
		window.display();
	}
	return true;
}
