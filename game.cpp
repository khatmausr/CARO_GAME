#include "common.h"

void game::startTwoPlayers()
{
    menuMusic.stop();
    
    Music gameMusic;
    gameMusic.openFromFile("sound/game_music.ogg");
    gameMusic.setLoop(true);
    gameMusic.play();

    // Loading display objects
    Texture t1, t2, t3, t4, t5;
    t2.loadFromFile("image/x.png"); t2.setSmooth(true);
    t3.loadFromFile("image/o.png"); t3.setSmooth(true);
    t4.loadFromFile("image/x_cursor.png"); t4.setSmooth(true);
    t5.loadFromFile("image/o_cursor.png"); t5.setSmooth(true);

    Sprite button_X(t2), button_O(t3), pointer_X(t4), pointer_O(t5);

    // Some variable
    int arr[20][20] = { 0 };
    int dx = 0, dy = 0;
    bool turn = 1; //1: X's turn    0: O's turn

    // Window
    bool isexit = false;
    while (!isexit)
    {
        // Event
        Event e;

        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
            {
                isexit = true;
                window.close();
            }

            if (e.type == Event::KeyPressed)
            {
                switch (e.key.code)
                {
                case Keyboard::Left:
                {
                    if (dx > 0) dx--;
                    break;
                }
                case Keyboard::Right:
                {
                    if (dx < BOARD_SIZE - 1) dx++;
                    break;
                }
                case Keyboard::Up:
                {
                    if (dy > 0) dy--;
                    break;
                }
                case Keyboard::Down:
                {
                    if (dy < BOARD_SIZE - 1) dy++;
                    break;
                }
                case Keyboard::Enter:
                {
                    if (!arr[dx][dy])
                    {
                        arr[dx][dy] = (turn) ? 1 : -1;
                        turn = !turn;
                    }
                    break;
                }
                case Keyboard::Escape:
                {
                    isexit = true;
                    break;
                }
                }
            }
        }

        // Display
        window.clear(Color::White);
        window.draw(gameBackground);

        for (int i = 0; i < BOARD_SIZE; ++i)
            for (int j = 0; j < BOARD_SIZE; ++j)
                if (arr[i][j] == 1)
                {
                    button_X.setPosition(Vector2f(BOARD_LEFT + i * 40, BOARD_TOP + j * 40));
                    window.draw(button_X);
                }
                else if (arr[i][j] == -1)
                {
                    button_O.setPosition(Vector2f(BOARD_LEFT + i * 40, BOARD_TOP + j * 40));
                    window.draw(button_O);
                }

        if (turn)
        {
            pointer_X.setPosition(Vector2f(BOARD_LEFT + dx * 40, BOARD_TOP + dy * 40));
            window.draw(pointer_X);
        }
        else
        {
            pointer_O.setPosition(Vector2f(BOARD_LEFT + dx * 40, BOARD_TOP + dy * 40));
            window.draw(pointer_O);
        }

        window.display();
    }

    gameMusic.stop();
    menuMusic.play();
}