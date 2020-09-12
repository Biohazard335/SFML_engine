#ifndef TEXT_INPUT_BOX_HPP
#define TEXT_INPUT_BOX_HPP

#include "../input/Mousey.hpp"
#include "../input/Keyblade.hpp"
#include "../communal/Data_Packet.hpp"

class Text_Input_Box{
private:

	int x;
	int y;
	int width=450;
	int height=40;

	int char_size=32;

	unsigned int max_chars_x=16;
	int max_chars_y=1;
	int current_line=0;


	int bs_wait=0;
	int cursor_blink=0;

	std::string input;
	std::string output; 

	bool enter_is_return=true;

	bool visible=true;
	bool usable=true;

	bool active=false;

	sf::Sprite box;
	sf::Sprite cursor;

	int cursor_x=0;
	int cursor_y=0;

	sf::Text display_text;

public:
	Text_Input_Box();

	void create(int x_p, int y_p);
	void draw(sf::RenderWindow&);

	bool is_active(){return active;}
	bool is_visible(){return visible;}
	bool is_usable(){return usable;}

	void set_font(sf::Font& font);
	void set_box_texture(sf::Texture& texture);
	void set_cursor_texture(sf::Texture& texture);

	sf::Sprite get_box(){return box;}
	sf::Sprite get_cursor(){return cursor;}
	sf::Text get_display_text(){return display_text;}

	std::string get_input(){return input;}
	std::string get_output(){return output;}

	void update(Mousey& mouse,Keyblade& keyboard);



};



#endif