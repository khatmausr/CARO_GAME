#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;

RenderWindow window;

// Image
Texture t_menuBackground;
Sprite menuBackground;

Texture t_gameBackground;
Sprite gameBackground;

Texture t_logo;
Sprite logo;

Texture t_button_X, t_button_O;
Sprite button_X, button_O;

Texture t_cursor_X, t_cursor_O;
Sprite cursor_X, cursor_O;

Texture t_x_big, t_o_big;
Sprite x_big, o_big;

// Font
Font font_arial;
Font font_courierNew;
Font font_bebasNeueBold;
Font font_robotoMonoBold;

// Menu musics and sounds
Music menuMusic;
Music gameMusic;

SoundBuffer s_optionSound;
Sound optionSound;

// Theme
int theme;

// Button
Texture t_greenButton_default;
Texture t_blueButton_default;
Texture t_brownButton_default;
Texture t_redButton_default;
Texture t_yellowButton_default;

Texture t_greenButton_mouseOver;
Texture t_blueButton_mouseOver;
Texture t_brownButton_mouseOver;
Texture t_redButton_mouseOver;
Texture t_yellowButton_mouseOver;

// Name Input

Texture t_dialogBox;
Texture t_textPlaceholder;
Texture t_navBack;
Texture t_navOk;
