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

// Input - Ouput DateAndTime
std::istream& operator >> (std::istream& in, tm*& ltm)
{
	in >> ltm->tm_hour >> ltm->tm_isdst >> ltm->tm_mday >> ltm->tm_min;
	in >> ltm->tm_mon >> ltm->tm_sec >> ltm->tm_wday >> ltm->tm_yday >> ltm->tm_year;
	return in;
}

std::ostream& operator << (std::ostream& out, tm*& ltm)
{
	out << ltm->tm_hour << " " << ltm->tm_isdst << " " << ltm->tm_mday << " " << ltm->tm_min << " ";
	out << ltm->tm_mon << " " << ltm->tm_sec << " " << ltm->tm_wday << " " << ltm->tm_yday << " " << ltm->tm_year;
	return out;
}

// Save Game Files Manager Struct
struct saveGameManager
{
	std::string _filename;
	int _typeGame;
	std::string _s1, _s2; // 2P game: s1: player 1's name, s2: player 2's name
						// 1P game: s1: player's name, s2: score
	tm* _ltm;
};

std::istream& operator >> (std::istream& in, saveGameManager& temp)
{
	std::getline(in, temp._filename);
	in >> temp._typeGame; in.ignore();
	std::getline(in, temp._s1);
	std::getline(in, temp._s2);
	in >> temp._ltm; in.ignore();
	return in;
}

std::ostream& operator << (std::ostream& out, saveGameManager& temp)
{
	out << temp._filename << std::endl;
	out << temp._typeGame << std::endl;
	out << temp._s1 << std::endl;
	out << temp._s2 << std::endl;
	out << temp._ltm << std::endl;
	return out;
}
