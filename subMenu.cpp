#include "common.h"

void subMenu::newGameMenu(game& g)
{
    bool choice = 0;
    bool isexit = false;

    while (!isexit)
    {
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
                case Keyboard::Up: case Keyboard::Down:
                {
                    optionSound.play();
                    choice = !choice;
                    break;
                }
                case Keyboard::Enter:
                {
                    optionSound.play();
                    if (choice) g.startTwoPlayers();
                    isexit = true;
                    break;
                }
                case Keyboard::Escape:
                {
                    optionSound.play();
                    isexit = true;
                    break;
                }
                }
            }
        }

        // Display
        window.clear(Color::White);

        window.draw(menuBackground);
        window.draw(logo);

        RectangleShape line(Vector2f(5.f, 160.f));
        line.setFillColor(Color::Black);
        line.setPosition(Vector2f(980.f, 515.f));
        window.draw(line);

        Text text[2];
        text[0].setString("One Player");
        text[1].setString("Two Players");

        Texture t; t.loadFromFile("image/menu_choosing.png");
        Sprite choosing(t); choosing.setPosition(Vector2f(980.f, 515 + choice * 80.f));
        window.draw(choosing);

        for (int i = 0; i < 2; i++)
        {
            text[i].setFont(font_arial);
            text[i].setCharacterSize(40);
            text[i].setFillColor((i == (int)choice) ? Color::White : Color::Black);
            if (i == (int)choice) text[i].setStyle(Text::Bold);
            text[i].setPosition(Vector2f(1000.f, 530.f + i * 80.f));
            window.draw(text[i]);
        }

        window.display();
    }
}

void subMenu::loadGameMenu(game& g)
{
    bool isexit = false;

    while (!isexit)
    {
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
                case Keyboard::Escape:
                {
                    optionSound.play();
                    isexit = true;
                    break;
                }
                }
            }
        }

        // Display
        window.clear(Color::White);
        window.draw(menuBackground);

        Text text;
        text.setString("LOAD GAME");
        
        text.setFont(font_arial);
        text.setCharacterSize(50);
        text.setFillColor(Color::Black);
        text.setStyle(Text::Bold);
        text.setPosition(Vector2f(800.f, 50.f));
        window.draw(text);

        window.display();
    }
}

void subMenu::highScoreMenu()
{
    bool isexit = false;

    while (!isexit)
    {
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
                case Keyboard::Escape:
                {
                    optionSound.play();
                    isexit = true;
                    break;
                }
                }
            }
        }

        // Display
        window.clear(Color::White);
        window.draw(menuBackground);

        Text text;
        text.setString("HIGH SCORE");

        text.setFont(font_arial);
        text.setCharacterSize(50);
        text.setFillColor(Color::Black);
        text.setStyle(Text::Bold);
        text.setPosition(Vector2f(800.f, 50.f));
        window.draw(text);

        window.display();
    }
}

void subMenu::settingsMenu()
{
    bool isexit = false;

    while (!isexit)
    {
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
                case Keyboard::Escape:
                {
                    optionSound.play();
                    isexit = true;
                    break;
                }
                }
            }
        }

        // Display
        window.clear(Color::White);
        window.draw(menuBackground);

        Text text;
        text.setString("SETTINGS");

        text.setFont(font_arial);
        text.setCharacterSize(50);
        text.setFillColor(Color::Black);
        text.setStyle(Text::Bold);
        text.setPosition(Vector2f(800.f, 50.f));
        window.draw(text);

        window.display();
    }
}

void subMenu::aboutMenu()
{
    bool isexit = false;

    while (!isexit)
    {
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
                case Keyboard::Escape:
                {
                    optionSound.play();
                    isexit = true;
                    break;
                }
                }
            }
        }

        // Display
        window.clear(Color::White);
        window.draw(menuBackground);

        Text title;
        title.setString("ABOUT");

        title.setFont(font_arial);
        title.setCharacterSize(50);
        title.setFillColor(Color::Black);
        title.setStyle(Text::Bold);
        title.setPosition(Vector2f(900.f, 50.f));
        window.draw(title);

        Texture t_logo1; t_logo1.loadFromFile("image/group02_logo.png");
        Sprite logo1(t_logo1); logo1.setPosition(Vector2f(550.f, 150.f));
        window.draw(logo1);        
        
        Texture t_logo2; t_logo2.loadFromFile("image/menu_logo.png");
        t_logo2.setSmooth(true);
        Sprite logo2(t_logo2); logo2.setPosition(Vector2f(780.f, 150.f));
        logo2.setScale(0.65f, 0.65f);
        window.draw(logo2);

        Text text[14];
        text[0].setString(L"    Ho Chi Minh City University of Science    ");
        text[1].setString(L"Viet Nam National University, Ho Chi Minh City");
        text[2].setString(L"                 Đồ án môn học                ");
        text[3].setString(L"     PHƯƠNG PHÁP LẬP TRÌNH HƯỚNG ĐỐI TƯỢNG    ");
        text[4].setString(L"            Game CARO (Version 1.0)           ");
        text[5].setString(L"                   Members                    ");
        text[6].setString(L"Hồ Hữu Viễn                           18127251");
        text[7].setString(L"Phạm Anh Tuấn                         19127084");
        text[8].setString(L"Nguyễn Thanh Tình                     19127292");
        text[9].setString(L"Trần Xuân Sơn                         19127321");
        text[10].setString(L"              Special thanks to               ");
        text[11].setString(L"ThS. Trương Toàn Thịnh    -    Theory Lecturer");
        text[12].setString(L"ThS. Nguyễn Thành An      - Teaching Assistant");
        text[13].setString(L"ThS. Trần Ngọc Đạt Thành  -       LAB Lecturer");
        
        for (int i = 0; i < 14; i++)
        {
            text[i].setFont(font_courierNew);
            text[i].setCharacterSize(30);
            text[i].setFillColor(Color::Black);
            text[i].setPosition(Vector2f(550.f, 450.f + i * 40.f));
            window.draw(text[i]);
        }
        window.display();
    }
}