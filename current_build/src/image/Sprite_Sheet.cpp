#include "Sprite_Sheet.hpp"

Sprite_Sheet::Sprite_Sheet(std::string file_p, int s_w_p, int s_h_p, int x_l_p, int y_l_p, std::string name_p){
	load(file_p, s_w_p, s_h_p, x_l_p, y_l_p, name_p);
}

void Sprite_Sheet::load(std::string file_p, int s_w_p, int s_h_p, int x_l_p, int y_l_p, std::string name_p){
	sprite_width=s_w_p;
	sprite_height=s_h_p;
	sheet_x_length=x_l_p;
	sheet_y_length=y_l_p;
	name=name_p;

	texture.loadFromFile(file_p);
	texture.setSmooth(true);
}


void Sprite_Sheet::load_sprite(sf::Sprite& sprite, int x_p, int y_p){
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect((sprite_width*x_p),(sprite_height*y_p),sprite_width,sprite_height));
}
