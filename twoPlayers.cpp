#include "common.h"

twoPlayers::twoPlayers()
{
    x = BOARD_SIZE / 2 - 1; y = BOARD_SIZE / 2 - 1;
    scoreX = scoreO = 0; playerName[0] = ""; playerName[1] = "";
    turn = 0; isExit = false;
}

bool twoPlayers::isContinue()
{
    return turn;
}

void twoPlayers::resetData()
{
    b.resetBoard();
    x = BOARD_SIZE / 2 - 1; y = BOARD_SIZE / 2 - 1;
    turn = 0; isExit = false;
}

void twoPlayers::newGame()
{
    scoreX = scoreO = 0; playerName[0] = ""; playerName[1] = "";
    resetData(); turn = 1; isExit = false;
    askForName();
    runGame();
}

void twoPlayers::continueGame()
{
    isExit = false;
    runGame();
}

void twoPlayers::runGame()
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
        displayGameScreen();
        window.display();
    }

    // Managing musics after exiting the game
    gameMusic.stop();
    if (window.isOpen()) menuMusic.play();
}

void twoPlayers::exitGame()
{
    turn = 0; isExit = true;
    gameMusic.stop(); menuMusic.stop();
    window.close();
}

void twoPlayers::askForName()
{
    menuMusic.stop();

    // Declaire some objects
    RectangleShape tint(Vector2f((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT));
    tint.setFillColor(Color(0, 0, 0, 50));
    RectangleShape blackRec(Vector2f((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT));
    blackRec.setFillColor(Color(0, 0, 0, 255));

    Text txt_title, txt_playerName[2], txt_describe[2];

    txt_title.setFont(font_arial);
    txt_title.setFillColor(Color::White);
    txt_title.setCharacterSize(80);
    txt_title.setStyle(Text::Bold);
    txt_title.setPosition(Vector2f(50.f, 100.f));
    txt_title.setString("Enter Players' Name");

    for (int i = 0; i <= 1; i++)
    {
        txt_playerName[i].setFont(font_arial);
        txt_playerName[i].setCharacterSize(40);
        txt_playerName[i].setString("");

        txt_describe[i].setFont(font_arial);
        txt_describe[i].setCharacterSize(30);
        txt_describe[i].setStyle(Text::Bold);
    }

    txt_playerName[0].setFillColor(Color(255, 255, 255, 255)); txt_playerName[0].setPosition(Vector2f(50.f, 500.f));
    txt_playerName[1].setFillColor(Color(255, 255, 255, 105)); txt_playerName[1].setPosition(Vector2f(50.f, 650.f));

    txt_describe[0].setString("Player 1: "); 
    txt_describe[0].setFillColor(Color(255, 255, 255, 255)); txt_describe[0].setPosition(Vector2f(50.f, 450.f));
    txt_describe[1].setString("Player 2: ");
    txt_describe[1].setFillColor(Color(255, 255, 255, 105)); txt_describe[1].setPosition(Vector2f(50.f, 600.f));

    // Dimming
    for (int i = 0; i <= 30; i++)
    {
        window.draw(tint);
        window.display();
    }

    // Entering
    int i = 0;
    while (i < 2)
    {
        Event e;

        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
            {
                i = 2; // Exit Entering-Loop
                exitGame();
            }

            if (e.type == Event::TextEntered)
            {
                switch (e.text.unicode)
                {
                case ASCII_BACKSPACE:
                {
                    if (playerName[i].length() > 0)
                    {
                        playerName[i].pop_back();
                        txt_playerName[i].setString(playerName[i]);
                    }
                    break;
                }
                case ASCII_ENTER:
                {
                    if (i == 0)
                        for (int frame = 0; frame < 15; frame++)
                        {
                            for (int j = 0; j <= 1; j++)
                            {
                                txt_playerName[j].setFillColor(Color(255, 255, 255, txt_playerName[j].getFillColor().a + ((j == 1) ? 10 : -10)));
                                txt_playerName[j].setPosition(Vector2f(txt_playerName[j].getPosition().x, txt_playerName[j].getPosition().y - 10.f));
                                txt_describe[j].setFillColor(Color(255, 255, 255, txt_describe[j].getFillColor().a + ((j == 1) ? 10 : -10)));
                                txt_describe[j].setPosition(Vector2f(txt_describe[j].getPosition().x, txt_describe[j].getPosition().y - 10.f));
                            }
                            window.draw(blackRec);
                            window.draw(txt_title);
                            window.draw(txt_playerName[0]); window.draw(txt_playerName[1]);
                            window.draw(txt_describe[0]); window.draw(txt_describe[1]);
                            window.display();
                        }
                    
                    i++;
                    break;
                }
                default:
                {
                    if ((('a' <= e.text.unicode) && (e.text.unicode <= 'z')) || (('A' <= e.text.unicode) && (e.text.unicode <= 'Z')) ||
                        (('0' <= e.text.unicode) && (e.text.unicode <= '9')))
                    {
                        playerName[i] += e.text.unicode;
                        txt_playerName[i].setString(playerName[i]);
                    }
                }
                }
            }
        }

        window.draw(blackRec);
        window.draw(txt_title);
        window.draw(txt_playerName[0]); window.draw(txt_playerName[1]);
        window.draw(txt_describe[0]); window.draw(txt_describe[1]);
        window.display();
    }

    // Dimming
    for (int i = 15; i >= 0; i--)
    {
        displayGameScreen();
        blackRec.setFillColor(Color(0, 0, 0, i * 16)); window.draw(blackRec);
        window.display();
    }
}

// Save - Load Game Data Struct - Using for storing data by binary format file
struct saveGameData
{
    int _board[BOARD_SIZE * BOARD_SIZE + 2];
    int _turn;
    int _x, _y;
    int _scoreX, _scoreO;
    bool _isExit;
};

void twoPlayers::askForSave()
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
        displayGameScreen();
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

                        displayGameScreen(); window.draw(tint);
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

        displayGameScreen(); window.draw(tint);
        window.draw(txt_title); window.draw(txt_filename); window.draw(txt_describe);
        window.display();
    }

    // Dimming
    for (int i = 20; i >= 0; i--)
    {
        displayGameScreen();
        tint.setFillColor(Color(0, 0, 0, i * 10)); window.draw(tint);
        window.display();
    }
}

void twoPlayers::saveGame(std::string filename)
{
    std::vector <int> dataBoard = b.exportBoard();

    saveGameData data;
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE + 2; i++) data._board[i] = dataBoard[i];
    data._turn = turn;
    data._x = x; data._y = y;
    data._scoreX = scoreX; data._scoreO = scoreO;
    data._isExit = isExit;

    std::fstream fout(filename, std::ios::out | std::ios::binary);
    fout.write((char*)&data, sizeof(saveGameData));
    fout.close();
}

void twoPlayers::askForLoad()
{
    // Declaire some objects
    RectangleShape tint(Vector2f((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT));

    Text txt_title, txt_filename, txt_describe;

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

    // Dimming
    for (int i = 0; i <= 20; i++)
    {
        displayGameScreen();
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

                        displayGameScreen(); window.draw(tint);
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

        displayGameScreen(); window.draw(tint);
        window.draw(txt_title); window.draw(txt_filename); window.draw(txt_describe);
        window.display();
    }

    // Dimming
    for (int i = 20; i >= 0; i--)
    {
        displayGameScreen();
        tint.setFillColor(Color(0, 0, 0, i * 10)); window.draw(tint);
        window.display();
    }
}

void twoPlayers::loadGame(std::string filename)
{
    saveGameData data;

    std::fstream fin(filename, std::ios::in | std::ios::binary);
    fin.read((char*)&data, sizeof(saveGameData));
    fin.close();

    std::vector <int> dataBoard;
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE + 2; i++) dataBoard.push_back(data._board[i]);
    b.importBoard(dataBoard);

    turn = data._turn;
    x = data._x; y = data._y;
    scoreX = data._scoreX; scoreO = data._scoreO;
    isExit = data._isExit;
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
            if (y > 0) y--;
            break;
        }
        case Keyboard::D:
        {
            if (y < BOARD_SIZE - 1) y++;
            break;
        }
        case Keyboard::W:
        {
            if (x > 0) x--;
            break;
        }
        case Keyboard::S:
        {
            if (x < BOARD_SIZE - 1) x++;
            break;
        }
        case Keyboard::Space:
        {
            if (b.markCell(x, y, turn))
            {
                if (direction = b.checkBoard(x, y, x_begin, y_begin))
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
            if (y > 0) y--;
            break;
        }
        case Keyboard::Right:
        {
            if (y < BOARD_SIZE - 1) y++;
            break;
        }
        case Keyboard::Up:
        {
            if (x > 0) x--;
            break;
        }
        case Keyboard::Down:
        {
            if (x < BOARD_SIZE - 1) x++;
            break;
        }
        case Keyboard::Enter:
        {
            if (b.markCell(x, y, turn))
            {
                if (direction = b.checkBoard(x, y, x_begin, y_begin))
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

void twoPlayers::changeTurn()
{
    if (turn == 1) turn = -1; else turn = 1;
}

void twoPlayers::displayGameScreen()
{
    // Loading some statistics
    Text txt_countX, txt_countO, txt_scoreX, txt_scoreO, txt_playerName[2];

    txt_countX.setFont(font_arial);
    txt_countX.setFillColor(Color::White);
    txt_countX.setCharacterSize(30);
    txt_countX.setPosition(Vector2f(20.f, 600.f));

    txt_countO.setFont(font_arial);
    txt_countO.setFillColor(Color::White);
    txt_countO.setCharacterSize(30);
    txt_countO.setPosition(Vector2f(950.f, 600.f));

    txt_scoreX.setFont(font_arial);
    txt_scoreX.setFillColor(Color::White);
    txt_scoreX.setCharacterSize(100);
    txt_scoreX.setPosition(Vector2f(100.f, 50.f));

    txt_scoreO.setFont(font_arial);
    txt_scoreO.setFillColor(Color::White);
    txt_scoreO.setCharacterSize(100);
    txt_scoreO.setPosition(Vector2f(1000.f, 50.f));
    
    for (int i = 0; i <= 1; i++)
    {
        txt_playerName[i].setFont(font_arial);
        txt_playerName[i].setFillColor(Color::White);
        txt_playerName[i].setCharacterSize(30);
        txt_playerName[i].setString(playerName[i]);
    }
    txt_playerName[0].setPosition(Vector2f(50.f, 0.f)); txt_playerName[1].setPosition(Vector2f(1000.f, 0.f));

    window.clear(Color::White);
    window.draw(gameBackground);

    b.displayBoard();

    txt_scoreX.setString(std::to_string(scoreX)); window.draw(txt_scoreX);
    txt_scoreO.setString(std::to_string(scoreO)); window.draw(txt_scoreO);

    txt_countX.setString(std::to_string(b.getCountX())); window.draw(txt_countX);
    txt_countO.setString(std::to_string(b.getCountO())); window.draw(txt_countO);

    window.draw(txt_playerName[0]); window.draw(txt_playerName[1]);

    if (turn == 1)
    {
        x_big.setColor(Color(255, 255, 255, 255)); o_big.setColor(Color(255, 255, 255, 100));
        cursor_X.setPosition(Vector2f(BOARD_LEFT + y * 30, BOARD_TOP + x * 30));
        window.draw(cursor_X);
    }
    else if (turn == -1)
    {
        x_big.setColor(Color(255, 255, 255, 100)); o_big.setColor(Color(255, 255, 255, 255));
        cursor_O.setPosition(Vector2f(BOARD_LEFT + y * 30, BOARD_TOP + x * 30));
        window.draw(cursor_O);
    }

    window.draw(x_big); window.draw(o_big);
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
            displayGameScreen();
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
        displayGameScreen();
       
        if (whoWin) window.draw(line);
        window.draw(t);

        window.display();
    }

    return true;
}