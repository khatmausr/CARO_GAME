#include "twoPlayers.h"
#include "common.h"

twoPlayers::twoPlayers(sf::Texture* bgTexture):Game(bgTexture)
{
	typeGame = 0; // Two Players
}

twoPlayers::~twoPlayers()
{
}


void twoPlayers::askForName()
{
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

	int i = 0;
	while (i < 2)
	{
		sf::Event e;

		nameInputTitle.setString(std::to_string(i + 1) + "P's Name:");
		nameInputTitleS.setString(std::to_string(i + 1) + "P's Name:");
		
		nameInputTitle.setFillColor(sf::Color::White);
		nameInputTitleS.setFillColor(sf::Color::Black);
		
		nameInput.setString(playerName[i]);
		nameInput.setFillColor(sf::Color::Black);
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				i = 2;
				exitGame();
			}
			else if (e.type == sf::Event::TextEntered)
			{
				if (e.type == Event::TextEntered)
				{
					switch (e.text.unicode)
					{
					case ASCII_BACKSPACE:
					{
						if (!playerName[i].empty())
						{
							playerName[i].pop_back();
							nameInput.setString(playerName[i]);
						}
						break;
					}
					case ASCII_ENTER:
					{
						nameInput.setString("");
						i++;
						break;
					}
					default:
					{
						if (isalnum(e.text.unicode) && playerName[i].length() <= 15)
						{
							playerName[i] += std::toupper(e.text.unicode);
							nameInput.setString(playerName[i]);
						}
					}
					}
				}
			}
		}
		window.clear();
		window.draw(menuBackground);
		window.draw(dialogBox);
		window.draw(nameInputTitleS);
		window.draw(nameInputTitle);
		window.draw(textPlaceholder);
		window.draw(nameInput);
		window.display();
	}

}

void twoPlayers::processKeyPressed(int keyCode)
{
	int x_begin = 0, y_begin = 0, direction = 0;

	if (turn == 1) // X - player could control the game with AWSD and Space buttons
	{
		switch (keyCode)
		{
		case Keyboard::A:
		{
			if (cursorP.y > 0)
			{
				cursorP.y--;
				moveSound.play();
			}
			break;
		}
		case Keyboard::D:
		{
			if (cursorP.y < BOARD_SIZE - 1)
			{
				cursorP.y++;
				moveSound.play();
			}
			break;
		}
		case Keyboard::W:
		{
			if (cursorP.x > 0)
			{
				cursorP.x--;
				moveSound.play();
			}
			break;
		}
		case Keyboard::S:
		{
			if (cursorP.x < BOARD_SIZE - 1)
			{
				cursorP.x++;
				moveSound.play();
			}
			break;
		}
		case Keyboard::Space:
		{
			if (b.markCell(cursorP.x, cursorP.y, turn))
			{
				if (direction = b.checkBoard(cursorP.x, cursorP.y, x_begin, y_begin))
				{
					markWin(x_begin, y_begin, direction);
					sleep(milliseconds(1000));
					isExit = displayWin();
				}
				else if (b.getCountX() + b.getCountO() == BOARD_SIZE * BOARD_SIZE)
				{
					sleep(milliseconds(1000));
					isExit = displayWin(true); // DRAW
				}
				else changeTurn();
			}
			break;
		}
		}
	}
	else if (turn == -1) // O - player could control the game with arrows and Enter buttons
	{
		switch (keyCode)
		{
		case Keyboard::Left:
		{
			if (cursorP.y > 0)
			{
				cursorP.y--;
				moveSound.play();
			}
			break;
		}
		case Keyboard::Right:
		{
			if (cursorP.y < BOARD_SIZE - 1)
			{
				cursorP.y++;
				moveSound.play();
			}
			break;
		}
		case Keyboard::Up:
		{
			if (cursorP.x > 0)
			{
				cursorP.x--;
				moveSound.play();
			}
			break;
		}
		case Keyboard::Down:
		{
			if (cursorP.x < BOARD_SIZE - 1)
			{
				cursorP.x++;
				moveSound.play();
			}
			break;
		}
		case Keyboard::Enter:
		{
			if (b.markCell(cursorP.x, cursorP.y, turn))
			{
				if (direction = b.checkBoard(cursorP.x, cursorP.y, x_begin, y_begin))
				{
					markWin(x_begin, y_begin, direction);
					sleep(milliseconds(1000));
					isExit = displayWin();
				}
				else if (b.getCountX() + b.getCountO() == BOARD_SIZE * BOARD_SIZE)
				{
					sleep(milliseconds(1000));
					isExit = displayWin(true); // DRAW
				}
				else changeTurn();
			}
			break;
		}
		}
	}

	if (keyCode == Keyboard::L) askForSave();
	if (keyCode == Keyboard::T) askForLoad();

	if (keyCode == Keyboard::Escape) isExit = true;
	if(keyCode == Keyboard::M)
	{
		if (vol)
		{
			vol = false;
			gameMusic.setVolume(0);
			moveSound.setVolume(0);
		}
		else
		{
			vol = true;
			gameMusic.setVolume(50);
			moveSound.setVolume(100);
		}
	}
}