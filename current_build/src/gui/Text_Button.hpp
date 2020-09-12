#ifndef TEXT_BUTTON_HPP
#define TEXT_BUTTON_HPP
#include "Button.hpp"
#include "../image/Sprite_Sheet.hpp"

class Text_Button: public Button{
private:
	unsigned int max_chars_x=17;
	unsigned int max_lines_y=1;

	sf::Text display_text;

	sf::Sprite s_off;
	sf::Sprite s_highlighted; 

	sf::Color text_on_color=sf::Color::Green;
	sf::Color text_off_color=sf::Color(117,24,15,225);
	sf::Color text_highlighted_color=sf::Color(242,30,10,225);
public:

	void draw(sf::RenderWindow& window)override;
	Text_Button(std::string name_p, int x_p, int y_p, Data_Packet data_p, int l_p,int u_p,int d_p, int r_p);

	void set_on_color(sf::Color c){text_on_color=c;}
	void set_off_color(sf::Color c){text_off_color=c;}
	void set_font(sf::Font& font){display_text.setFont(font);}
	void load_sprites(Sprite_Sheet& sheet);
};

#endif