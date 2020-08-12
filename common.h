#pragma once

// Libraries
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Headers
#include "game.h"
#include "mainMenu.h"
#include "onePlayer.h"
#include "subMenu.h"
#include "twoPlayers.h"

// Define constants
#define WINDOW_WIDTH  1200
#define WINDOW_HEIGHT 700

#define BOARD_SIZE 20

#define BOARD_LEFT 300.f
#define BOARD_TOP  50.f

#define THEME_MAX 3

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

extern Font font_arial;
extern Font font_courierNew;

extern Music menuMusic;
extern SoundBuffer s_optionSound;
extern Sound optionSound;

extern int theme;

// Common methods
class common
{
public:
	static void initGame();
	static void runGame();
};