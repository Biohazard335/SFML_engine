#include "Gamestate_Manager.hpp"
#include "../communal/Duration_Check.hpp"


void Gamestate_Manager::update_layer_resolutions(){
	pac_man_state->update_layer_resolutions();
	core_game_state->update_layer_resolutions();
	main_menu_state->update_layer_resolutions();
	pause_menu_state->update_layer_resolutions();
	options_menu_state->update_layer_resolutions();
}

bool Gamestate_Manager::set_state(Data_Packet data){
	std::string state=data.get_strings().at(0);
	if(state==""){
		return false;
	}else{
		if(state=="core_game"){
			gamepad.set_button_mode(false);
			gamepad.set_current_layer("core_layer");
			current_state =core_game_state;
		}else if(state=="pac_man"){
			gamepad.set_button_mode(false);
			gamepad.set_current_layer("core_layer");
			current_state=pac_man_state;
		}else if(state=="main_menu"){
			gamepad.set_button_mode(true);
			gamepad.set_current_layer("gui");
			current_state=main_menu_state;
		}else if(state=="pause_menu"){
			gamepad.set_button_mode(true);
			gamepad.set_current_layer("gui");
			current_state=pause_menu_state;
		}else if(state=="options_menu"){
			gamepad.set_button_mode(true);
			gamepad.set_current_layer("gui");
			options_menu_state->set_previous_state(current_state->get_state_name());
			current_state=options_menu_state;
		}else{
			std::cout<<"\nError loading state ["<<state<<"]"<<std::endl;
			return false;
		}
		return true;
	}
}

void Gamestate_Manager::receive_data(Data_Packet data_p){
	if(data_p.get_data_type()!="empty"){
		if(data_p.get_interaction_level()==DRIVER){
			send_data.push_back(data_p);
		}else if(data_p.get_interaction_level()==MANAGER){
			if(data_p.get_data_type()=="set_state"){
				set_state(data_p);
			}else if(data_p.get_data_type()=="sound_create_request"){
				audiohandler.add_sfx(data_p.get_ints().at(0),data_p.get_strings().at(0),data_p.get_ints().at(1));
			}else if(data_p.get_data_type()=="sound_stop_request"){
				audiohandler.stop_sfx(data_p.get_ints().at(0));
			}else{
				std::cout<<"ERROR: manager recieved invalid data: "<<data_p.get_data_type()<<std::endl;
			}
		}else{
			std::cout<<"\nERROR: manager recieved local data: "<<data_p.get_data_type()<<std::endl;
		}
	}else{
		std::cout<<"ERROR: manager recieved empty data!"<<std::endl;
	}
}



void Gamestate_Manager::render(sf::RenderWindow& window){
	Duration_Check::start("GM render");
	current_state->render(window);
	Duration_Check::stop("GM render");
}

void Gamestate_Manager::update(sf::RenderWindow& window){
	Duration_Check::start("GM update");
	keyboard.update_jps();
	gamepad.update_jps();
	mouse.update_jp();
	Duration_Check::start("-poll events");
	sf::Event event;

	while(window.pollEvent(event)){
		if(event.type==sf::Event::KeyPressed ||event.type==sf::Event::KeyReleased){
			keyboard.event_update(event);
		}else if(event.type==sf::Event::JoystickButtonPressed||event.type==sf::Event::JoystickButtonReleased
				||event.type==sf::Event::JoystickDisconnected||event.type==sf::Event::JoystickConnected||event.type==sf::Event::JoystickMoved){
			gamepad.event_update(event);
			if(!gamepad.is_active()){
				gamepad.set_active(true);
				mouse.set_active(false);
				send_data.push_back(Data_Packet("hide_mouse",DRIVER));
			}
		}else if(event.type==sf::Event::MouseMoved||event.type==sf::Event::MouseButtonPressed||event.type==sf::Event::MouseButtonReleased){
			if(!mouse.is_active()){
				gamepad.set_active(false);
				mouse.set_active(true);
				send_data.push_back(Data_Packet("unhide_mouse",DRIVER));
			}
			mouse.update(window);
		}
	}
	Duration_Check::stop("-poll events");
	while(current_state->has_send_data()){
		receive_data(current_state->get_send_data());
	}
	current_state->run_timer();
	current_state->update(mouse, keyboard,gamepad);
	audiohandler.update_sfx();
	Duration_Check::stop("GM update");
}


Gamestate_Manager::Gamestate_Manager(){
	main_menu_state = new Main_Menu_State(imagehandler);
	pac_man_state = new Pac_Man_State(imagehandler);
	core_game_state = new Core_Game_State(imagehandler);
	pause_menu_state = new Pause_Menu_State(imagehandler);
	options_menu_state= new Options_Menu_State(imagehandler);
	
	gamepad.set_button_mode(true);
	gamepad.set_current_layer("gui");
	current_state=main_menu_state;

	if(sf::Joystick::isConnected(0)){
		gamepad.set_active(true);
		gamepad.set_connected(true);
		mouse.set_active(false);
		send_data.push_back(Data_Packet("hide_mouse",DRIVER));
	}else{
		gamepad.set_active(false);
		mouse.set_active(true);
	}
}