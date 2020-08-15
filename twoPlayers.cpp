#include "common.h"

twoPlayers::twoPlayers()
{
    x = BOARD_SIZE / 2 - 1; y = BOARD_SIZE / 2 - 1;
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

        if (turn == 1)
        {
            cursor_X.setPosition(Vector2f(BOARD_LEFT + y * 30, BOARD_TOP + x * 30));
            window.draw(cursor_X);
        }
        else if (turn == -1)
        {
            cursor_O.setPosition(Vector2f(BOARD_LEFT + y * 30, BOARD_TOP + x * 30));
            window.draw(cursor_O);
        }

        window.display();
    }

    // Managing musics after exiting the game
    gameMusic.stop();
    if (window.isOpen()) menuMusic.play();
}

void twoPlayers::processKeyPressed(int keyCode, bool& isexit)
{
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
                if (b.checkBoard(x, y)) isexit = displayWinners(turn);
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
                if (b.checkBoard(x, y)) isexit = displayWinners(turn);
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

bool twoPlayers::displayWinners(int whoWin)
// Return a value to show whether the players want to exit instead of play another game.
// True: Stop; False: Play another game
{
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
        window.draw(t);

        window.display();
    }

    return true;
}