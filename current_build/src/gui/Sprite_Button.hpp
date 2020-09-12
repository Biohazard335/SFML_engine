#ifndef SPRITE_BUTTON_HPP
#define SPRITE_BUTTON_HPP

#include "Button.hpp"
#include "../image/Sprite_Sheet.hpp"

class Sprite_Button: public Button{
private:
	std::string sheet_name;
	int sheet_number;

	sf::Sprite s_off;
	sf::Sprite s_highlighted;
	sf::Sprite s_on;
public:
	Sprite_Button(std::string name_p,std::string sheet_p, int s_n_p, int x_p, int y_p, Data_Packet data_p, int l_p,int u_p,int d_p, int r_p);

	void draw(sf::RenderWindow& window) override;

	std::string get_sheet_name(){return sheet_name;}
	int get_sheet_number(){return sheet_number;}

	void load_sprites(Sprite_Sheet& sheet);
};

#endif