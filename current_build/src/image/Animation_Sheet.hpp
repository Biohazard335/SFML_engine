#ifndef ANIMATION_SHEET_HPP
#define ANIMATION_SHEET_HPP

#include "Animation.hpp"

class Animation_Sheet{
private:
	sf::Texture texture;

	int	frame_width;
	int frame_height;

	int animation_length;
	int sheet_y_length;

	std::string name;

public:
	Animation_Sheet(){}
	Animation_Sheet(std::string file_p, int f_w_p, int f_h_p, int a_l_p, int y_l_p, std::string name_p);

	void load(std::string file_p, int f_w_p, int f_h_p, int a_l_p, int y_l_p, std::string name_p);

	void load_animation(Animation& animation, int y_p);

	int get_frame_width(){return frame_width;}
	int get_frame_height(){return frame_height;}
	int get_animation_length(){return animation_length;}
	int get_sheet_y_length(){return sheet_y_length;}
	std::string get_name(){return name;}

	sf::Texture get_texture(){return texture;}
	void set_texture(std::string file_p){texture.loadFromFile(file_p);}



};



#endif
