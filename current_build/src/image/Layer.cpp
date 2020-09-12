#include "Layer.hpp"
#include <iostream>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~STATIC MEMBERS AND FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~

double Layer::default_res_x=1366;
double Layer::default_res_y=768;
double Layer::current_res_x=Layer::default_res_x;
double Layer::current_res_y=Layer::default_res_y;
Layer::DISPLAY_TYPE Layer::display_type=STRETCH_TO_FIT;
bool Layer::fullscreen=true;


void Layer::set_new_resolution(double x_p, double y_p){
	current_res_x=x_p;
	current_res_y=y_p;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~NON_STATIC FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


Layer::Layer(std::string n_p){
	layer_name=n_p;
	I_s_o=0;
	I_l_o=1;
	J_s_o=0;
	J_l_o=1;
	original_size_x=default_res_x;
	original_size_y=default_res_y;
	original_center_x=original_size_x/2;
	original_center_y=original_size_y/2;
	setSize(original_size_x,original_size_y);
	setCenter(original_center_x,original_center_y);
	setViewport(sf::FloatRect(I_s_o, J_s_o,I_l_o,J_l_o));
}


double Layer::window_to_layer_x(double x_p){
	if(display_type==STRETCH_TO_FIT){
		return (x_p/Xs)+(getCenter().x-original_center_x);
	}else if(display_type==SMART_SCALE){
		if(Xs>Ys){
			return ((x_p-black_bar_size_x)/Ys)+(getCenter().x-original_center_x);
		}else{
			return (x_p/Xs)+(getCenter().x-original_center_x);
		}
	}else{
		return (x_p-black_bar_size_x);
	}
}

double Layer::window_to_layer_y(double y_p){
	if(display_type==STRETCH_TO_FIT){
		return (y_p/Ys)+(getCenter().y-original_center_y);
	}else if(display_type==SMART_SCALE){
		if(Ys>Xs){
			return ((y_p-black_bar_size_y)/Xs)+(getCenter().y-original_center_y);
		}else{
			return (y_p/Ys)+(getCenter().y-original_center_y);
		}
	}else{
		return (y_p-black_bar_size_y);
	}
}


void Layer::set_original_size(int x_p, int y_p){
	original_size_x=x_p;
	original_size_y=y_p;
	setSize(original_size_x,original_size_y);
}
void Layer::set_original_center(int x_p, int y_p){
	original_center_x=x_p;
	original_center_y=y_p;
	setCenter(original_center_x,original_center_y);
}
void Layer::set_original_viewport(double Is_p, double Js_p, double Il_p, double Jl_p){
	I_s_o=Is_p;
	J_s_o=Js_p;
	J_l_o=Jl_p;
	I_l_o=Il_p;
	setViewport(sf::FloatRect(I_s_o, J_s_o,I_l_o,J_l_o));
}

void Layer::resolve_new_resolution(){
	Xs=current_res_x/default_res_x;
	Ys=current_res_y/default_res_y;

	black_bar_size_x=0;
	black_bar_size_y=0;
	I_s=0;
	J_s=0;
	I_l=1;
	J_l=1;

	//std::cout<<"Xs="<<Xs<<std::endl;
	//std::cout<<"Ys="<<Ys<<std::endl;

	if(!display_type==STRETCH_TO_FIT){
		if(current_res_x>default_res_x && current_res_y> default_res_y){
			if(display_type==SMART_SCALE){
				if(Xs<Ys){
					black_bar_size_y=0;
					black_bar_size_x=((current_res_x-(default_res_x*Ys))/2);
					J_s=J_s_o;
					I_s=(((I_s_o*default_res_x*Ys)+black_bar_size_x)/current_res_x);
					J_l=J_l_o;
					I_l=(((I_l_o*default_res_x)*Ys)/current_res_x);
				}else if(Ys<Xs){
					black_bar_size_x=0;
					black_bar_size_y=((current_res_y-(default_res_y*Xs))/2);
					//std::cout<<"bbsY="<<black_bar_size_y<<std::endl;
					I_s=I_s_o;
					J_s=(((J_s_o*default_res_y*Xs)+black_bar_size_y)/current_res_y);
					I_l=I_l_o;
					J_l=(((J_l_o*default_res_y)*Xs)/current_res_y);
				}
			}else{
				black_bar_size_x=((current_res_x-default_res_x)/2);
				black_bar_size_y=((current_res_y-default_res_y)/2);
				I_s=(((I_s_o*default_res_x)+black_bar_size_x)/current_res_x);
				J_s=(((J_s_o*default_res_y)+black_bar_size_y)/current_res_y);
				I_l=((I_l_o*default_res_x)/current_res_x);
				J_l=((J_l_o*default_res_y)/current_res_y);
			}
		}else{
			if(display_type==SMART_SCALE){
				if(Xs>Ys){
					black_bar_size_y=0;
					black_bar_size_x=((current_res_x-(default_res_x*Ys))/2);
					J_s=J_s_o;
					I_s=(((I_s_o*default_res_x*Ys)+black_bar_size_x)/current_res_x);
					J_l=J_l_o;
					I_l=(((I_l_o*default_res_x)*Ys)/current_res_x);
				}else if(Ys>Xs){
					black_bar_size_x=0;
					black_bar_size_y=((current_res_y-(default_res_y*Xs))/2);
					I_s=I_s_o;
					J_s=(((J_s_o*default_res_y*Xs)+black_bar_size_y)/current_res_y);
					I_l=I_l_o;
					J_l=(((J_l_o*default_res_y)*Xs)/current_res_y);
				}
			}else{
				display_type=STRETCH_TO_FIT;
			}
		}
	}

	setViewport(sf::FloatRect(I_s,J_s,I_l,J_l));
	setSize(original_size_x,original_size_y);
}

bool Layer::window_point_in_viewport(double x_p, double y_p){
	double P_I=x_p/current_res_x;
	double P_J=y_p/current_res_y;
	if(P_I>=I_s && (P_I<=(I_s+I_l))){
		return true;
	}else{
		return false;
	}
}