#ifndef SPRITE_SHEET_HPP
#define SPRITE_SHEET_HPP

#include <SFML/Graphics.hpp>
#include <string>


class Sprite_Sheet{
private:
	sf::Texture texture;

	int	sprite_width;
	int sprite_height;

	int sheet_x_length;
	int sheet_y_length;

	bool button_sheet=false;

	std::string name;

public:
	Sprite_Sheet(){}
	Sprite_Sheet(std::string file_p, int s_w_p, int s_h_p, int x_l_p, int y_l_p, std::string name_p);

	void load(std::string file_p, int s_w_p, int s_h_p, int x_l_p, int y_l_p, std::string name_p);

	void load_sprite(sf::Sprite& sprite, int x_p, int y_p);

	int get_sprite_width(){return sprite_width;}
	int get_sprite_height(){return sprite_height;}
	int get_sheet_x_length(){return sheet_x_length;}
	int get_sheet_y_length(){return sheet_y_length;}
	std::string get_name(){return name;}

	sf::Texture& get_texture(){return texture;}
	void set_texture(std::string file_p){texture.loadFromFile(file_p);}

	void set_button_sheet(bool b_p){button_sheet=b_p;}
	bool is_button_sheet(){return button_sheet;}



};


#endif