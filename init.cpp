#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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

// Font
Font font_arial;
Font font_courierNew;
Font font_bebasNeueBold;

// Menu musics and sounds
Music menuMusic;

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

Texture t_greenButton_pressed;
Texture t_blueButton_pressed;
Texture t_brownButton_pressed;
Texture t_redButton_pressed;
Texture t_yellowButton_pressed;


