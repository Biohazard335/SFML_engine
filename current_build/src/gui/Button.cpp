#include "Button.hpp"


bool Button::check_clicked(Mousey& mouse){
	if(is_active() && mouse.is_layer_valid() && mouse.get_layer_x()>x && mouse.get_layer_x()<x+width && mouse.get_layer_y()>y && mouse.get_layer_y()<y+height && mouse.is_clicked()){
		if(togglable){
			toggle_on();
		}
		return true;
	}else{
		return false;
	}
}
bool Button::check_highlighted(Mousey& mouse){
	if(is_active() && mouse.is_layer_valid() && mouse.get_layer_x()>x && mouse.get_layer_x()<x+width && mouse.get_layer_y()>y && mouse.get_layer_y()<y+height){
		highlighted=true;
		return true;
	}else{
		highlighted=false;
		return false;
	}
}
