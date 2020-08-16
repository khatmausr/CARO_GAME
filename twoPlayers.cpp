#include "common.h"

twoPlayers::twoPlayers()
{
    x = BOARD_SIZE / 2 - 1; y = BOARD_SIZE / 2 - 1;
    scoreX = scoreO = 0;
    turn = 0;
}

bool twoPlayers::isContinue()
{
    return turn;
}

void twoPlayers::resetData()
{
    b.resetBoard();
    x = BOARD_SIZE / 2 - 1; y = BOARD_SIZE / 2 - 1;
    turn = 0;
}

void twoPlayers::newGame()
{
    turn = 1;
    scoreX = scoreO = 0;
    runGame();
}

void twoPlayers::continueGame()
{
    runGame();
}

void twoPlayers::runGame()
{
    // Managing musics
    menuMusic.stop();

    Music gameMusic;
    gameMusic.openFromFile("sound/game_music.ogg");
    gameMusic.setLoop(true); gameMusic.play();

    // Loading cursor - objects
    Texture t1, t2;
    t1.loadFromFile("image/x_cursor.png"); t1.setSmooth(true);
    t2.loadFromFile("image/o_cursor.png"); t2.setSmooth(true);
    Sprite cursor_X(t1), cursor_O(t2);

    Texture t_x_big, t_o_big;
    t_x_big.loadFromFile("image/x_big.png"); t_x_big.setSmooth(true);
    t_o_big.loadFromFile("image/o_big.png"); t_o_big.setSmooth(true);
    Sprite x_big(t_x_big), o_big(t_o_big);
    x_big.setPosition(Vector2f(0.f, 200.f));
    o_big.setPosition(Vector2f(900.f, 200.f));

    // Loading statistic variables
    Text txt_countX, txt_countO, txt_scoreX, txt_scoreO;

    txt_scoreX.setFont(font_arial);
    txt_scoreX.setFillColor(Color::White);
    txt_scoreX.setCharacterSize(100);
    txt_scoreX.setPosition(Vector2f(100.f, 50.f));

    txt_scoreO.setFont(font_arial);
    txt_scoreO.setFillColor(Color::White);
    txt_scoreO.setCharacterSize(100);
    txt_scoreO.setPosition(Vector2f(1000.f, 50.f));

    txt_countX.setFont(font_arial);
    txt_countX.setFillColor(Color::White);
    txt_countX.setCharacterSize(30);
    txt_countX.setPosition(Vector2f(20.f, 600.f));

    txt_countO.setFont(font_arial);
    txt_countO.setFillColor(Color::White);
    txt_countO.setCharacterSize(30);
    txt_countO.setPosition(Vector2f(950.f, 600.f));

    // Game Window
    bool isexit = false;
    while (!isexit)
    {
        // Event
        Event e;

        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
            {
                turn = 0;
                isexit = true;
                window.close();
            }

            if (e.type == Event::KeyPressed)
                processKeyPressed(e.key.code, isexit);
        }

        // Display
        window.clear(Color::White);
        window.draw(gameBackground);

        b.displayBoard();
        
        txt_scoreX.setString(std::to_string(scoreX)); window.draw(txt_scoreX);
        txt_scoreO.setString(std::to_string(scoreO)); window.draw(txt_scoreO);

        txt_countX.setString("Number of ticking:\n" + std::to_string(b.getCountX())); window.draw(txt_countX);
        txt_countO.setString("Number of ticking:\n" + std::to_string(b.getCountO())); window.draw(txt_countO);

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

        window.display();
    }

    // Managing musics after exiting the game
    gameMusic.stop();
    if (window.isOpen()) menuMusic.play();
}

void twoPlayers::processKeyPressed(int keyCode, bool& isexit)
{
    int x_begin, y_begin, direction;
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
                    isexit = displayWinners(x_begin, y_begin, direction, turn);
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
                isexit = displayWinners(x_begin, y_begin, direction, turn);
                else changeTurn();
            }
            break;
        }
        }
    }

    if (keyCode == Keyboard::Escape) isexit = true;
}

void twoPlayers::changeTurn()
{
    if (turn == 1) turn = -1; else turn = 1;
}

bool twoPlayers::displayWinners(int x_begin, int y_begin, int direction, int whoWin)
// Return a value to show whether the players want to exit instead of play another game.
// True: Stop; False: Play another game
{
    // Draw a line first
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
        window.clear(Color::Black);

        window.draw(gameBackground);
        b.displayBoard();

        line.setSize(Vector2f((float)i, 5.f));
        window.draw(line);

        window.display();
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

    if (whoWin == 1) scoreX++; else scoreO++;

    bool isexit = false;
    while (!isexit)
    {
        // Event
        Event e;

        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
            {
                turn = 0;
                isexit = true;
                window.close();
            }

            if (e.type == Event::KeyPressed)
            {
                switch (e.key.code)
                {
                case Keyboard::Escape:
                {
                    isexit = true;
                    resetData();
                    return true;
                    break;
                }
                case Keyboard::Enter:
                {
                    isexit = true;
                    resetData();
                    turn = 1;
                    return false;
                    break;
                }
                }
            }
        }

        // Display
        window.clear(Color::White);
        
        window.draw(gameBackground); 
        b.displayBoard();
        
        window.draw(line);
        window.draw(t);

        window.display();
    }

    return true;
}