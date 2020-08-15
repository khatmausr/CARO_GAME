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
            {
                if (e.key.code == Keyboard::Escape) isexit = true;
                else processKeyPressed(e.key.code);
            }
        }

        // Display
        window.clear(Color::White);
        window.draw(gameBackground);

        b.displayBoard();

        if (turn == 1)
        {
            cursor_X.setPosition(Vector2f(BOARD_LEFT + x * 30, BOARD_TOP + y * 30));
            window.draw(cursor_X);
        }
        else if (turn == -1)
        {
            cursor_O.setPosition(Vector2f(BOARD_LEFT + x * 30, BOARD_TOP + y * 30));
            window.draw(cursor_O);
        }

        window.display();
    }

    // Managing musics after exiting the game
    gameMusic.stop();
    if (this->isContinue()) menuMusic.play();
}

void twoPlayers::processKeyPressed(int keyCode)
{
    if (turn == 1) // X - player could control the game with AWSD and Space buttons
    {
        switch (keyCode)
        {
        case Keyboard::A:
        {
            if (x > 0) x--;
            break;
        }
        case Keyboard::D:
        {
            if (x < BOARD_SIZE - 1) x++;
            break;
        }
        case Keyboard::W:
        {
            if (y > 0) y--;
            break;
        }
        case Keyboard::S:
        {
            if (y < BOARD_SIZE - 1) y++;
            break;
        }
        case Keyboard::Space:
        {
            if (b.markCell(x, y, turn))
            {
                changeTurn();
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
            if (x > 0) x--;
            break;
        }
        case Keyboard::Right:
        {
            if (x < BOARD_SIZE - 1) x++;
            break;
        }
        case Keyboard::Up:
        {
            if (y > 0) y--;
            break;
        }
        case Keyboard::Down:
        {
            if (y < BOARD_SIZE - 1) y++;
            break;
        }
        case Keyboard::Enter:
        {
            if (b.markCell(x, y, turn))
            {
                changeTurn();
            }
            break;
        }
        }
    }
}

void twoPlayers::changeTurn()
{
    if (turn == 1) turn = -1; else turn = 1;
}

void twoPlayers::displayWinners(int whoWin)
{

}