#include "common.h"
#include "onePlayer.h"

onePlayer::onePlayer(Texture* bgTexture, int level) : Game(bgTexture)
{
	typeGame = level;
}

onePlayer::~onePlayer()
{
}

void onePlayer::askForName()
{
		menuMusic.stop();

	// Dialog Box
	sf::Sprite dialogBox(t_dialogBox);
	dialogBox.setOrigin(dialogBox.getLocalBounds().width / 2.0f, dialogBox.getLocalBounds().height / 2.0f);
	dialogBox.setPosition((float)WINDOW_WIDTH / 2.0f, (float)WINDOW_HEIGHT / 2.0f);

	// Text Placeholder
	sf::Sprite textPlaceholder(t_textPlaceholder);
	textPlaceholder.setOrigin(textPlaceholder.getLocalBounds().width / 2.0f, textPlaceholder.getLocalBounds().height / 2.0f);
	textPlaceholder.setPosition((float)WINDOW_WIDTH / 2.0f, (float)WINDOW_HEIGHT / 2.0f);

	// Text
	sf::Text nameInputTitle;
	nameInputTitle.setFont(font_bebasNeueBold);
	nameInputTitle.setCharacterSize(40u);
	nameInputTitle.setPosition(sf::Vector2f(370.0f, 215.0f));

	//Shadow title
	sf::Text nameInputTitleS;
	nameInputTitleS.setFont(font_bebasNeueBold);
	nameInputTitleS.setCharacterSize(40u);
	nameInputTitleS.setPosition(sf::Vector2f(374.0f, 215.0f));

	sf::Text nameInput;
	nameInput.setFont(font_bebasNeueBold);
	nameInput.setCharacterSize(30u);
	nameInput.setOrigin(nameInput.getOrigin().x, (nameInput.getLocalBounds().height / 2.0f) + 17.5f);
	nameInput.setPosition(370.0f, (float)WINDOW_HEIGHT / 2.0f);

	nameInputTitle.setString("Player's Name:");
	nameInputTitleS.setString("Player's Name:");

	nameInputTitle.setFillColor(sf::Color::White);
	nameInputTitleS.setFillColor(sf::Color::Black);

	nameInput.setString(playerName[0]);
	nameInput.setFillColor(sf::Color::Black);

	bool isDone = false;
	while (!isDone)
	{
		sf::Event e;
		
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				isDone = true;
				exitGame();
			}

			else if (e.type == sf::Event::TextEntered)
			{
				switch (e.text.unicode)
				{
				case ASCII_BACKSPACE:
				{
					if (!playerName[0].empty())
					{
						playerName[0].pop_back();
						nameInput.setString(playerName[0]);
					}
					break;
				}
				case ASCII_ENTER:
				{
					isDone = true;
					break;
				}
				default:
				{
					if (isalnum(e.text.unicode) && playerName[0].length() <= 15)
					{
						playerName[0] += std::toupper(e.text.unicode);
						nameInput.setString(playerName[0]);
					}
				}
				}
			}
		}
		window.draw(dialogBox);
		window.draw(nameInputTitleS);
		window.draw(nameInputTitle);
		window.draw(textPlaceholder);
		window.draw(nameInput);
		window.display();
	}

	switch (typeGame)
	{
	case 1:
	{
		playerName[1] = "Easy Bot";
		break;
	}
	case 2:
	{
		playerName[1] = "Medium Bot";
		break;
	}
	case 3:
	{
		playerName[1] = "Hard Bot";
	}
	}
}

void onePlayer::drawLine(int x_begin, int y_begin, int direction)
{
	RectangleShape line;
	line.setFillColor(Color::White);
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

bool onePlayer::displayResult(int whoWin)
{
	Text t;
	switch (whoWin)
	{
	case -1:
	{
		t.setString("YOU LOSE!\n Press Esc to Exit or Enter to play another game...");
		break;
	}
	case 0:
	{
		t.setString("DRAW!\n Press Esc to Exit or Enter to play another game...");
		break;
	}
	case 1:
	{
		t.setString("YOU WON!\n Press Esc to Exit or Enter to play another game...");
		break;
	}
	}
	t.setFont(font_arial);
	t.setFillColor(Color::White);
	t.setCharacterSize(30);

	if (whoWin == 1) scoreX++;
	else if (whoWin == -1) scoreO++;

	bool isDone = false;
	while (!isDone)
	{
		// Event
		Event e;

		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				exitGame();
				isDone = true;
			}

			if (e.type == Event::KeyPressed)
			{
				switch (e.key.code)
				{
				case Keyboard::Escape:
				{
					resetData();

					isDone = true;
					return true;
					break;
				}
				case Keyboard::Enter:
				{
					resetData(); turn = 1;

					isDone = true;
					return false;
					break;
				}
				}
			}
		}

		// Display
		displayGame();
		window.display();
	}

	return true;
}

void onePlayer::processKeyPressed(int keyCode)
{
	int x_begin = 0, y_begin = 0, direction = 0;

	switch (keyCode)
	{
	case Keyboard::Left:
	{
		if (cursorP.y > 0) cursorP.y--;
		break;
	}
	case Keyboard::Right:
	{
		if (cursorP.y < BOARD_SIZE - 1) cursorP.y++;
		break;
	}
	case Keyboard::Up:
	{
		if (cursorP.x > 0) cursorP.x--;
		break;
	}
	case Keyboard::Down:
	{
		if (cursorP.x < BOARD_SIZE - 1) cursorP.x++;
		break;
	}
	case Keyboard::Enter:
	{
		// Player's Turn
		if (b.markCell(cursorP.x, cursorP.y, 1))
		{
			if (direction = b.checkBoard(cursorP.x, cursorP.y, x_begin, y_begin))
			{
				drawLine(x_begin, y_begin, direction);
				isExit = displayResult(1);
			}
			else if (b.getCountX() + b.getCountO() == BOARD_SIZE * BOARD_SIZE)
			{
				isExit = displayResult(0);
			}
		}

		// The BOT is thinking
		displayGame(); window.display();
		sleep(milliseconds(rand() % 1001 + 500));

		// Bot's Turn
		Vector2u botMoving = botMove();
		if (b.markCell(botMoving.x, botMoving.y, -1))
		{
			if (direction = b.checkBoard(botMoving.x, botMoving.y, x_begin, y_begin))
			{
				drawLine(x_begin, y_begin, direction);
				isExit = displayResult(-1);
			}
			else if (b.getCountX() + b.getCountO() == BOARD_SIZE * BOARD_SIZE)
			{
				isExit = displayResult(0);
			}
		}

		break;
	}
	case Keyboard::Escape:
	{
		exitGame();
		break;
	}
	case Keyboard::L:
	{
		askForSave();
		break;
	}
	case Keyboard::T:
	{
		askForLoad();
		break;
	}
	}
}

double onePlayer::distance(Vector2u pA, Vector2u pB)
{
	return sqrt((pA.x - pB.x) * (pA.x - pB.x) + (pA.y - pB.y) * (pA.y - pB.y));
}

Vector2u onePlayer::botMove()
{
	if (typeGame == 1) return easyBotMove();
	if (typeGame == 2) return medBotMove();
	return hardBotMove();
}

Vector2u onePlayer::easyBotMove()
{
	Vector2u ans(-1, -1);

	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			if (b.getCell(i, j) == 0) // Not marked yet
			{
				Vector2u temp(i, j);
				if (distance(temp, cursorP) < distance(ans, cursorP))
					ans = temp;
			}

	return ans;
}

Vector2u onePlayer::medBotMove()
{
	Vector2u ans(-1, -1);

	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			if (b.getCell(i, j) == 0) // Not marked yet
			{
				// Try to mark
				b.markCell(i, j, -1);
				
				// Checking
				int dummy_i = 0, dummy_j = 0;
				if (b.checkBoard(i, j, dummy_i, dummy_j)) Vector2u ans(i, j);

				// Redo marking
				b.redoMarkCell(i, j);
			}

	if (ans.x == -1) return easyBotMove(); // Finded notthing
	return ans;
}

Vector2u onePlayer::hardBotMove()
{
	// I'm thinking....
	return easyBotMove();
}