#include "Animation_Sheet.hpp"

Animation_Sheet::Animation_Sheet(std::string file_p, int f_w_p, int f_h_p, int a_l_p, int y_l_p, std::string name_p){
	load(file_p, f_w_p, f_h_p, a_l_p, y_l_p, name_p);
}

void Animation_Sheet::load(std::string file_p, int f_w_p, int f_h_p, int a_l_p, int y_l_p, std::string name_p){
	frame_width=f_w_p;
	frame_height=f_h_p;
	animation_length=a_l_p;
	sheet_y_length=y_l_p;
	name=name_p;

	texture.loadFromFile(file_p);
	texture.setSmooth(true);
}


void Animation_Sheet::load_animation(Animation& animation, int y_p){
	animation.load(texture,frame_width,frame_height,animation_length,(y_p*(frame_height)));
}