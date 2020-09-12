#include "Mousey.hpp"
//#include <iostream>


void Mousey::update(sf::RenderWindow& window){
	pressed=isButtonPressed(Mouse::Left);

	window_x=getPosition(window).x;
	window_y=getPosition(window).y;
}

void Mousey::update_jp(){
	if(just_pressed){
		just_pressed=false;
		held=true;
	}
	if(pressed && !held){
		just_pressed=true;
	}
	if(!pressed){
		held=false;
	}
}

void Mousey::set_layer(Layer& layer){
	layer_x=layer.window_to_layer_x(window_x);
	layer_y=layer.window_to_layer_y(window_y);
	current_layer=layer.get_layer_name();

	if(current_layer=="background"){
		locked_by_layer="none";
	}

	if(locked_by_layer=="none"){
		if(layer.window_point_in_viewport(window_x,window_y)){
			layer_valid=true;
			if(layer.get_behavior()==Layer::SOLID){
				locked_by_layer=current_layer;
			}
		}else{
			layer_valid=false;
			//std::cout<<current_layer<<": mouse not in viewport"<<std::endl;
		}

		if(layer.get_behavior()==Layer::LOCKOUT){
			locked_by_layer=current_layer;
		}

	}else{
		layer_valid=false;
		//std::cout<<current_layer<<" locked by "<<locked_by_layer<<std::endl;
	}

}