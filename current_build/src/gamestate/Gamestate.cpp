#include "Gamestate.hpp"


Gamestate::Gamestate(): gui_layer("gui"),background_layer("background"){
	mouse_state="normal";
	background_layer.set_behavior(Layer::TRANSPARENT);
}

void Gamestate::check_buttons(Mousey& mouse, std::vector<std::unique_ptr<Button>>& buttons){
	mouse.set_layer(gui_layer);
	for(unsigned int i=0;i<buttons.size();i++){
		buttons[i]->check_highlighted(mouse);
		if(buttons[i]->check_clicked(mouse)){
			if(buttons[i]->get_interaction_level()==LOCAL){
				execute_data(buttons[i]->get_data());
			}else{
				send_data.push_back(buttons[i]->get_data());
			}
		}
	}
}


void Gamestate::update_gui_layer(Mousey& mouse, Keyblade& keyboard, Gamepad& gamepad){
	if(gui_layer_buttons.size()>0){
		if(mouse.is_active()){
			check_buttons(mouse, gui_layer_buttons);
		}
		if(gamepad.is_active()){
			if(gamepad.get_button_mode() && gamepad.get_current_layer()==gui_layer.get_layer_name()){
				check_buttons(gamepad, gui_layer_buttons);
			}
		}
	}
}

void Gamestate::update(Mousey& mouse, Keyblade& keyboard, Gamepad& gamepad){
	update_gui_layer(mouse,keyboard,gamepad);
	mouse.set_layer(background_layer);
}

void Gamestate::render_gui_layer(sf::RenderWindow& window){
	window.setView(gui_layer);
	if(gui_layer_buttons.size()>0){
		for(unsigned int i=0;i<gui_layer_buttons.size();i++){
			gui_layer_buttons[i]->draw(window);
		}
	}
}

void Gamestate::render_background_layer(sf::RenderWindow& window){
	window.setView(background_layer);
	window.draw(background);
	if(title.getString()!=""){
		window.draw(title);
	}
}

void Gamestate::render(sf::RenderWindow& window){
	render_background_layer(window);
	render_gui_layer(window);
}

void Gamestate::update_layer_resolutions(){
	gui_layer.resolve_new_resolution();
	background_layer.resolve_new_resolution();
}

void Gamestate::check_buttons(Gamepad& gamepad, std::vector<std::unique_ptr<Button>>& buttons){
	int current_highlighted=gamepad.get_button_selected();
	buttons[current_highlighted]->manually_set_highlighted(true);

	if(gamepad.was_just_pressed(GAMEPAD_A)){
		if(buttons[current_highlighted]->is_togglable()){
			buttons[current_highlighted]->toggle_on();
		}
		if(buttons[current_highlighted]->pushed_by_gamepad(gamepad)){
			if(buttons[current_highlighted]->get_interaction_level()==LOCAL){
				execute_data(buttons[current_highlighted]->get_data());
			}else{
				send_data.push_back(buttons[current_highlighted]->get_data());
			}
			buttons[current_highlighted]->manually_set_highlighted(false);
		}	
	}
	if(buttons[current_highlighted]->get_type()==SLIDER && buttons[current_highlighted]->is_on()){
		//std::cout<<"sending data"<<std::endl;
		if(buttons[current_highlighted]->get_interaction_level()==LOCAL){
			execute_data(buttons[current_highlighted]->get_data());
		}else{
			send_data.push_back(buttons[current_highlighted]->get_data());
		}
	}
	if(buttons[current_highlighted]->is_using_gamepad()){
		buttons[current_highlighted]->update(gamepad);
	}else if((gamepad.get_left_stick_x()!=0 || gamepad.get_left_stick_y()!=0) && !gamepad.get_button_mode_pause()){
		int temp=-1;
		if(gamepad.get_left_stick_y()>0){
			temp=buttons[current_highlighted]->get_button_down();
		}else if(gamepad.get_left_stick_y()<0 ){
			temp=buttons[current_highlighted]->get_button_up();
		}else if(gamepad.get_left_stick_x()<0 ){
			temp=buttons[current_highlighted]->get_button_left();
		}else if(gamepad.get_left_stick_x()>0 ){
			temp=buttons[current_highlighted]->get_button_right();
		}
		if(temp>=0 && buttons[temp]->is_active()){
			gamepad.set_button_selected(temp);
			gamepad.set_button_mode_pause(true);
			buttons[current_highlighted]->manually_set_highlighted(false);
			//std::cout<<"gs "<<gamepad.get_button_selected()<<std::endl;
		}
	}else if(gamepad.get_left_stick_x()==0 && gamepad.get_left_stick_y()==0 && gamepad.get_button_mode_pause()){
		gamepad.set_button_mode_pause(false);
	}

}

Data_Packet Gamestate::get_send_data(){
	if(send_data.size()>0){
		Data_Packet tmp=send_data.at(0);
		send_data.erase(send_data.begin());
		return tmp;
	}else{
		return Data_Packet();
	}
}

void Gamestate::request_sound(Audiokeyholder& key_holder){
	Audiokeyhandler::give_new_key(key_holder);
	if(key_holder.get_key_contents()!=-1){
		send_data.push_back(Data_Packet("sound_create_request",MANAGER,{key_holder.get_key_contents(),key_holder.is_looping()},{key_holder.get_name()}));
	}
}