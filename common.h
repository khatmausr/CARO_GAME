#pragma once

// Libraries
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

// Headers
#include "game.h"
#include "mainMenu.h"
#include "onePlayer.h"
#include "subMenu.h"
#include "twoPlayers.h"
#include "button.h"

// Define constants
#define WINDOW_WIDTH  1200
#define WINDOW_HEIGHT 780

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
extern Font font_bebasNeueBold;

extern Music menuMusic;
extern SoundBuffer s_optionSound;
extern Sound optionSound;

extern int theme;

// Button
extern Texture t_greenButton_default;
extern Texture t_greenButton_mouseOver;
extern Texture t_greenButton_pressed;

extern Texture t_blueButton_default;
extern Texture t_blueButton_mouseOver;
extern Texture t_blueButton_pressed;

extern Texture t_brownButton_default;
extern Texture t_brownButton_mouseOver;
extern Texture t_brownButton_pressed;

extern Texture t_redButton_default;
extern Texture t_redButton_mouseOver;
extern Texture t_redButton_pressed;

extern Texture t_yellowButton_default;
extern Texture t_yellowButton_mouseOver;
extern Texture t_yellowButton_pressed;


// Common methods
class common
{
public:
	static void initGame();
	static void runGame();
};