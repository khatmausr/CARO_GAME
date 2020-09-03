#include "common.h"
#include "onePlayer.h"
#include "button.h"

onePlayer::onePlayer(Texture* bgTexture, int level) : Game(bgTexture)
{
	typeGame = level;
}

onePlayer::~onePlayer()
{
}

void onePlayer::askForName()
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
				markWin(x_begin, y_begin, direction);
				isExit = displayLose();
			}
			else if (b.getCountX() + b.getCountO() == BOARD_SIZE * BOARD_SIZE)
				isExit = displayWin(true); // DRAW
			else // Player doesn't win, so it is machine's turn
			{
				// The BOT is thinking
				displayGame(); window.display();
				//sleep(milliseconds(rand() % 501 + 500);

				// Bot's Turn
				Vector2u botMoving = botMove();
				if (b.markCell(botMoving.x, botMoving.y, -1))
				{
					if (direction = b.checkBoard(botMoving.x, botMoving.y, x_begin, y_begin))
					{
						markWin(x_begin, y_begin, direction);
						sleep(milliseconds(1000));
						isExit = displayLose(); // LOSE HERE
					}
					else if (b.getCountX() + b.getCountO() == BOARD_SIZE * BOARD_SIZE)
					{
						sleep(milliseconds(1000));
						isExit = displayWin(true); // DRAW
					}
				}
			}
		}
		break;
	}
	case Keyboard::Escape:
	{
		isExit = true;
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

Vector2u onePlayer::easyBotMove() // Random somewhere nearly player's cell
{
	std::vector <Vector2u> ans;
	
	Vector2u bestMove(-1, -1);

	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			if (!b.getCell(i, j)) // Not marked yet
			{
				Vector2u tempMove(i, j);
				
				if (distance(tempMove, cursorP) < distance(bestMove, cursorP))
				{
					bestMove = tempMove;
					ans.clear(); ans.push_back(bestMove);
				}
				else if (distance(tempMove, cursorP) == distance(bestMove, cursorP)) ans.push_back(tempMove);
			}

	return ans[rand() % ans.size()];
}

Vector2u onePlayer::medBotMove()
{
	for (int k = 4; k >= 2; k--)
	{
		std::vector <Vector2u> ans;

		for (int i = 0; i < BOARD_SIZE; i++)
			for (int j = 0; j < BOARD_SIZE; j++)
				if (b.getCell(i, j))
				{
					int i_begin = 0, j_begin = 0;
					int direction = b.checkBoard(i, j, i_begin, j_begin, k);

					Vector2u head(-1, -1), tail(-1, -1);
					switch (direction)
					{
					case 1:
					{
						head.x = i_begin - 1; head.y = j_begin;
						tail.x = i_begin + k; tail.y = j_begin;
						break;
					}
					case 2:
					{
						head.x = i_begin; head.y = j_begin - 1;
						tail.x = i_begin; tail.y = j_begin + k;
						break;
					}
					case 3:
					{
						head.x = i_begin - 1; head.y = j_begin - 1;
						tail.x = i_begin + k; tail.y = j_begin + k;
						break;
					}
					case 4:
					{
						head.x = i_begin - 1; head.y = j_begin + 1;
						tail.x = i_begin + k; tail.y = j_begin - k;
						break;
					}
					}

					int count_push = 0;
					if ((0 <= head.x) && (head.x < BOARD_SIZE) && (0 <= head.y) && (head.y < BOARD_SIZE) && (!b.getCell(head.x, head.y)))
					{
						ans.push_back(head);
						count_push++;
					}

					if ((0 <= tail.x) && (tail.x < BOARD_SIZE) && (0 <= tail.y) && (tail.y < BOARD_SIZE) && (!b.getCell(tail.x, tail.y)))
					{
						ans.push_back(tail);
						count_push++;
					}

					if (count_push == 2) // There's two point to push, so it's dangerous, must hit them fisrt
						return ((rand() % 2) ? head : tail); // Head or Tail is the same, so randomly return
				}

		if (!ans.empty()) return ans[rand() % ans.size()];
	}

	return easyBotMove();
}

Vector2u onePlayer::hardBotMove()
{
	Vector3i tempMove = alphaBetaPrunning(1, 0, 3);
	
	Vector2u ans(tempMove.x, tempMove.y);
	return ans;
}

Vector3i onePlayer::alphaBetaPrunning(bool isMaximize, int depth, int maxDepth)
{
	Vector3i ans(-1, -1, -1);
	
	if ((depth < maxDepth) && (b.getCountX() + b.getCountO() < BOARD_SIZE * BOARD_SIZE))
	{
		std::vector <Vector3i> move;
		// Getting available moves
		for (int i = 0; i < BOARD_SIZE; i++)
			for (int j = 0; j < BOARD_SIZE; j++)
				if (!b.getCell(i, j))
				{
					// Cut all unnecessary moves
					b.markCell(i, j, (isMaximize)? -1 : 1);

					Vector3i tempMove(i, j, 0);
					int i_begin, j_begin;
					for (int k = 2; k <= 5; k++)
						if (b.checkBoard(i, j, i_begin, j_begin, k)) // Moves have influence are not being cutten
							tempMove.z = ((isMaximize) ? 1 : -1) * k;
					
					Vector3i curseMove = alphaBetaPrunning(!isMaximize, depth + 1, maxDepth);

					if (isMaximize)
					{
						if (tempMove.z < curseMove.z) move.push_back(tempMove);
						else move.push_back(curseMove);
					}
					else
					{
						if (tempMove.z > curseMove.z) move.push_back(tempMove);
						else move.push_back(curseMove);
					}

					b.redoMarkCell(i, j);
				}

		// Alpha Beta (MiniMax)
		if (isMaximize)
		{
			int maxPos = 0;
			for (unsigned int i = 1; i < move.size(); i++)
				if (move[maxPos].z < move[i].z) maxPos = i;
			ans = move[maxPos];
		}
		else
		{
			int minPos = 0;
			for (unsigned int i = 1; i < move.size(); i++)
				if (move[minPos].z > move[i].z) minPos = i;
			ans = move[minPos];
		}
	}

	if (ans.x == -1)
	{
		Vector2u tempMove = medBotMove();
		ans.x = tempMove.x; ans.y = tempMove.y; ans.z = 0;
	}

	return ans;
}

bool onePlayer::displayLose(bool isDraw)
{
	// Init
	Sprite bad;
	Sprite dialogBox;
	RectangleShape cover(Vector2f(1200.0f,700.0f));
	cover.setFillColor(Color(0, 31, 83));

	Text loser("YOU LOSE", font_bebasNeueBold, 50);
	loser.setOrigin(loser.getLocalBounds().width / 2.0f, loser.getLocalBounds().height / 2.0f + 15.0f);
	loser.setScale(0.0f, 0.0f);

	Text loserS(loser);
	loser.setFillColor(Color::White); loserS.setFillColor(Color::Black);
	loser.setPosition(WINDOW_WIDTH / 2.0f, 240.0f); loserS.setPosition(WINDOW_WIDTH / 2.0f + 3.0f, 240.0f);

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
	bad.setTexture(t_bad);
	bad.setOrigin(0.0f, bad.getLocalBounds().height);
	
	dialogBox.setTexture(t_dialogBox);
	dialogBox.setOrigin(dialogBox.getLocalBounds().width / 2.0f, dialogBox.getLocalBounds().height / 2.0f);
	dialogBox.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
	dialogBox.setScale(0.0f, 0.0f);

	Event e;
	bool flag = true;

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
		if (bad.getPosition().y < 190.0f)
		{
			bad.move(0.0f, 7.6f);
			dialogBox.setScale(dialogBox.getScale().x + 0.04f, dialogBox.getScale().y + 0.04f);
			titleS.setScale(titleS.getScale().x + 0.04f, titleS.getScale().y + 0.04f);
			title.setScale(title.getScale().x + 0.04f, title.getScale().y + 0.04f);
			for (int i = 0; i < statTitle.size(); ++i)
				statTitle[i].setScale(statTitle[i].getScale().x + 0.04f, statTitle[i].getScale().y + 0.04f);
			for (int i = 0; i < stats.size(); ++i)
				for (int j = 0; j < stats[i].size(); ++j)
					stats[i][j].setScale(stats[i][j].getScale().x + 0.04f, stats[i][j].getScale().y + 0.04f);
			backMenuBtn.setScale(backMenuBtn.getScale().x + 0.04f, backMenuBtn.getScale().y + 0.04f);
			replayBtn.setScale(replayBtn.getScale().x + 0.04f, replayBtn.getScale().y + 0.04f);
			loser.setScale(loser.getScale().x + 0.04f, loser.getScale().y + 0.04f);
			loserS.setScale(loserS.getScale().x + 0.04f, loserS.getScale().y + 0.04f);
			cover.setFillColor(Color(0, 31, 83, cover.getFillColor().a + 30));
		}

		window.clear();
		window.draw(menuBackground);
		window.draw(bad);
		window.draw(cover);
		window.draw(dialogBox);
		window.draw(titleS);
		window.draw(title);
		for (int i = 0; i < statTitle.size(); ++i)
			window.draw(statTitle[i]);
		for (int i = 0; i < stats.size(); ++i)
			for (int j = 0; j < stats[i].size(); ++j)
				window.draw(stats[i][j]);
		backMenuBtn.draw();
		replayBtn.draw();
		window.draw(loserS);
		window.draw(loser);
		window.display();
	}
	return true;
}
