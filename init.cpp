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
Image icon;

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

SoundBuffer s_moveSound;
Sound moveSound;

SoundBuffer s_winSound;
Sound winSound;
SoundBuffer s_loseSound;
Sound loseSound;

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
Texture t_board;
Texture t_textPlaceholder;
Texture t_navReset;

// Animation
Texture t_cloudLeft;
Texture t_cloudRight;
Texture t_star;
Texture t_smallStar;
Texture t_shine;
Texture t_smallShine;
Texture t_bad;

// About us
Music aboutUsMusic;

Texture t_artBg;
Texture t_artObj;
Texture t_zoom;

Texture t_group;
Texture t_fit;
Texture t_sLogo;
