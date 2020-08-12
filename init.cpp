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

// Font
Font font_arial;
Font font_courierNew;

// Menu musics and sounds
Music menuMusic;

SoundBuffer s_optionSound;
Sound optionSound;

// Theme
int theme;