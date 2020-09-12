#ifndef IMAGEHANDLER_HPP
#define IMAGEHANDLER_HPP

#include "Animation.hpp"
#include "Sprite_Sheet.hpp"
#include "Animation_Sheet.hpp"
#include "../gui/Sprite_Button.hpp"
#include "../gui/Text_Button.hpp"
#include "../gui/MEBL.hpp"
#include "../gui/Text_Input_Box.hpp"
#include "../gui/Slider.hpp"


class Imagehandler{
private:
	sf::Texture default_texture;
	sf::Texture default_animation_texture;
	Animation_Sheet default_animation;
	sf::Texture loading;

	Sprite_Sheet sheet0;
	Sprite_Sheet buttons0;
	Sprite_Sheet buttons1;


	Animation_Sheet pac_man;
	Animation_Sheet ghosts;
	Animation_Sheet pac_man_dies;

	sf::Texture breach;

	sf::Texture main_menu_background;
	sf::Texture pause_menu_background;
	sf::Texture core_game_background;
	sf::Texture options_menu_background;


	sf::Texture text_input_box;
	sf::Texture text_input_cursor;

	Sprite_Sheet slider_sheet;

	Sprite_Sheet text_buttons;
	Sprite_Sheet checkbox;

	sf::Font font;


public:
	Imagehandler();
	void load();
	~Imagehandler(){
	}

	void load_sprite(sf::Sprite& sprite,std::string name_p);
	void load_text_button(Text_Button& button);
	void load_sprite_button(Sprite_Button& button);
	void load_MEBL(MEBL& button);
	void load_slider(Slider& button);
	void load_animation(Animation& animation, std::string name_p);
	void load_text_input_box(Text_Input_Box& tib);
	void load_button(Button* button);
	void load_sf_text(sf::Text& text);


};

#endif