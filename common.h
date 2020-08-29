#pragma once

// Libraries
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <ctime>

// Define constants
#define WINDOW_WIDTH  1200
#define WINDOW_HEIGHT 700

#define MENU_TOP 250.0f
#define MENU_BUTTON_SPACING 75.0f
#define MENU_LINE_SPACING 40.0f

#define BOARD_LEFT 300.f
#define BOARD_TOP  50.f

#define THEME_MAX 3

#define ASCII_BACKSPACE 8
#define ASCII_ENTER     13
#define ASCII_ESC       27

// Namespace
using namespace sf;

// Environment Variables
extern RenderWindow window;

extern Texture t_menuBackground;
extern Sprite menuBackground;

extern Texture t_gameBackground;
extern Sprite gameBackground;

extern Texture t_logo;
extern Sprite logo;

extern Texture t_button_X, t_button_O;
extern Sprite button_X, button_O;

extern Texture t_cursor_X, t_cursor_O;
extern Sprite cursor_X, cursor_O;

extern Texture t_x_big, t_o_big;
extern Sprite x_big, o_big;

extern Font font_arial;
extern Font font_courierNew;
extern Font font_bebasNeueBold;
extern Font font_robotoMonoBold;

extern Music menuMusic;
extern Music gameMusic;
extern SoundBuffer s_optionSound;
extern Sound optionSound;

extern int theme;

// Button
extern Texture t_blueButton_default;
extern Texture t_blueButton_mouseOver;

extern Texture t_brownButton_default;
extern Texture t_brownButton_mouseOver;

extern Texture t_greenButton_default;
extern Texture t_greenButton_mouseOver;

extern Texture t_redButton_default;
extern Texture t_redButton_mouseOver;

extern Texture t_yellowButton_default;
extern Texture t_yellowButton_mouseOver;

// Name Input
extern Texture t_dialogBox;
extern Texture t_textPlaceholder;
extern Texture t_navBack;
extern Texture t_navOk;


// Input - Ouput DateAndTime
extern std::istream& operator >> (std::istream& in, tm*& ltm);
extern std::ostream& operator << (std::ostream& out, tm*& ltm);

// Save Game Files Manager Struct
struct saveGameManager
{
	std::string _filename;
	int _typeGame;
	std::string _s1, _s2; // 2P game: s1: player 1's name, s2: player 2's name
						// 1P game: s1: player's name, s2: score
	tm* _ltm;
};

extern std::istream& operator >> (std::istream& in, saveGameManager& temp);
extern std::ostream& operator << (std::ostream& out, saveGameManager& temp);


// Common methods
class common
{
public:
	static void initGame();
	static void runGame();
	static void aboutMenu();
};