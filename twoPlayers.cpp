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
		window.draw(dialogBox);
		window.draw(nameInputTitleS);
		window.draw(nameInputTitle);
		window.draw(textPlaceholder);
		window.draw(nameInput);
		window.display();
	}

}

// Declaire some objects
//    RectangleShape tint(Vector2f((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT));
//    tint.setFillColor(Color(0, 0, 0, 50));
//    RectangleShape blackRec(Vector2f((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT));
//    blackRec.setFillColor(Color(0, 0, 0, 255));
//
//    Text txt_title, txt_playerName[2], txt_describe[2];
//
//    txt_title.setFont(font_arial);
//    txt_title.setFillColor(Color::White);
//    txt_title.setCharacterSize(80);
//    txt_title.setStyle(Text::Bold);
//    txt_title.setPosition(Vector2f(50.f, 100.f));
//    txt_title.setString("Enter Players' Name");
//
//    for (int i = 0; i <= 1; i++)
//    {
//        txt_playerName[i].setFont(font_arial);
//        txt_playerName[i].setCharacterSize(40);
//        txt_playerName[i].setString("");
//
//        txt_describe[i].setFont(font_arial);
//        txt_describe[i].setCharacterSize(30);
//        txt_describe[i].setStyle(Text::Bold);
//    }
//
//    txt_playerName[0].setFillColor(Color(255, 255, 255, 255)); txt_playerName[0].setPosition(Vector2f(50.f, 500.f));
//    txt_playerName[1].setFillColor(Color(255, 255, 255, 105)); txt_playerName[1].setPosition(Vector2f(50.f, 650.f));
//
//    txt_describe[0].setString("Player 1: "); 
//    txt_describe[0].setFillColor(Color(255, 255, 255, 255)); txt_describe[0].setPosition(Vector2f(50.f, 450.f));
//    txt_describe[1].setString("Player 2: ");
//    txt_describe[1].setFillColor(Color(255, 255, 255, 105)); txt_describe[1].setPosition(Vector2f(50.f, 600.f));
//
//    // Dimming
//    for (int i = 0; i <= 30; i++)
//    {
//        window.draw(tint);
//        window.display();
//    }
//
//    // Entering
//    int i = 0;
//    while (i < 2)
//    {
//        Event e;
//
//        while (window.pollEvent(e))
//        {
//            if (e.type == Event::Closed)
//            {
//                i = 2; // Exit Entering-Loop
//                exitGame();
//            }
//
//            if (e.type == Event::TextEntered)
//            {
//                switch (e.text.unicode)
//                {
//                case ASCII_BACKSPACE:
//                {
//                    if (playerName[i].length() > 0)
//                    {
//                        playerName[i].pop_back();
//                        txt_playerName[i].setString(playerName[i]);
//                    }
//                    break;
//                }
//                case ASCII_ENTER:
//                {
//                    if (i == 0)
//                        for (int frame = 0; frame < 15; frame++)
//                        {
//                            for (int j = 0; j <= 1; j++)
//                            {
//                                txt_playerName[j].setFillColor(Color(255, 255, 255, txt_playerName[j].getFillColor().a + ((j == 1) ? 10 : -10)));
//                                txt_playerName[j].setPosition(Vector2f(txt_playerName[j].getPosition().x, txt_playerName[j].getPosition().y - 10.f));
//                                txt_describe[j].setFillColor(Color(255, 255, 255, txt_describe[j].getFillColor().a + ((j == 1) ? 10 : -10)));
//                                txt_describe[j].setPosition(Vector2f(txt_describe[j].getPosition().x, txt_describe[j].getPosition().y - 10.f));
//                            }
//                            window.draw(blackRec);
//                            window.draw(txt_title);
//                            window.draw(txt_playerName[0]); window.draw(txt_playerName[1]);
//                            window.draw(txt_describe[0]); window.draw(txt_describe[1]);
//                            window.display();
//                        }
//                    
//                    i++;
//                    break;
//                }
//                default:
//                {
//                    if ((('a' <= e.text.unicode) && (e.text.unicode <= 'z')) || (('A' <= e.text.unicode) && (e.text.unicode <= 'Z')) ||
//                        (('0' <= e.text.unicode) && (e.text.unicode <= '9')))
//                    {
//                        playerName[i] += e.text.unicode;
//                        txt_playerName[i].setString(playerName[i]);
//                    }
//                }
//                }
//            }
//        }
//
//        window.draw(blackRec);
//        window.draw(txt_title);
//        window.draw(txt_playerName[0]); window.draw(txt_playerName[1]);
//        window.draw(txt_describe[0]); window.draw(txt_describe[1]);
//        window.display();
//    }
//
//    // Dimming
//    for (int i = 15; i >= 0; i--)
//    {
//        displayGameScreen();
//        blackRec.setFillColor(Color(0, 0, 0, i * 16)); window.draw(blackRec);
//        window.display();
//    }
//}


void twoPlayers::processKeyPressed(int keyCode)
{
	int x_begin = 0, y_begin = 0, direction = 0;

	if (turn == 1) // X - player could control the game with AWSD and Space buttons
	{
		switch (keyCode)
		{
		case Keyboard::A:
		{
			if (cursorP.y > 0) cursorP.y--;
			break;
		}
		case Keyboard::D:
		{
			if (cursorP.y < BOARD_SIZE - 1) cursorP.y++;
			break;
		}
		case Keyboard::W:
		{
			if (cursorP.x > 0) cursorP.x--;
			break;
		}
		case Keyboard::S:
		{
			if (cursorP.x < BOARD_SIZE - 1) cursorP.x++;
			break;
		}
		case Keyboard::Space:
		{
			if (b.markCell(cursorP.x, cursorP.y, turn))
			{
				if (direction = b.checkBoard(cursorP.x, cursorP.y, x_begin, y_begin))
					isExit = displayWinners(x_begin, y_begin, direction, turn);
				else if (b.getCountX() + b.getCountO() == BOARD_SIZE * BOARD_SIZE)
					isExit = displayWinners(0, 0, 0, 0);
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
			if (b.markCell(cursorP.x, cursorP.y, turn))
			{
				if (direction = b.checkBoard(cursorP.x, cursorP.y, x_begin, y_begin))
					isExit = displayWinners(x_begin, y_begin, direction, turn);
				else if (b.getCountX() + b.getCountO() == BOARD_SIZE * BOARD_SIZE)
					isExit = displayWinners(0, 0, 0, 0);
				else changeTurn();
			}
			break;
		}
		}
	}

	if (keyCode == Keyboard::L) askForSave();
	if (keyCode == Keyboard::T) askForLoad();

	if (keyCode == Keyboard::Escape) isExit = true;
}




bool twoPlayers::displayWinners(int x_begin, int y_begin, int direction, int whoWin)
// Return a value to let us know that whether the players want to exit instead of playing another game.
// True: Stop; False: Play another game
{
	// Draw a line first
	RectangleShape line;
	line.setFillColor(Color::White);
	int length = 0;

	if (whoWin)
	{
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

	// Ask for continue
	Text t;
	switch (whoWin)
	{
	case -1:
	{
		t.setString("O win!\n Press Esc to Exit or Enter to play another game...");
		break;
	}
	case 0:
	{
		t.setString("Draw!\n Press Esc to Exit or Enter to play another game...");
		break;
	}
	case 1:
	{
		t.setString("X win!\n Press Esc to Exit or Enter to play another game...");
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

		if (whoWin) window.draw(line);
		window.draw(t);

		window.display();
	}

	return true;
}