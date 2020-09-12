#include "Core_Game_State.hpp"

#include <fstream>


Core_Game_State::Core_Game_State(Imagehandler& imagehandler):core_layer("core_layer"){
	tilemap.load_from_file("../assets/core_game/maps/path_map0.map");
	tilemap.set_position(Point((Layer::get_default_res_x()/2)-(tilemap.get_tileset().get_tile_width()*tilemap.get_length_x()/2), 
		(Layer::get_default_res_y()/2)-(tilemap.get_tileset().get_tile_height()*tilemap.get_length_y()/2)));

	for(int i=0;i<tilemap.get_length_x();i++){
		for(int j=0;j<tilemap.get_length_y();j++){

			if(tilemap.get_tile(i,j).get_type_s()=="start"){
				start=Point(i,j);
			}
			if(tilemap.get_tile(i,j).get_type_s()=="end"){
				end=Point(i,j);
			}
		}
	}
	load_sprites(imagehandler);
	//tib.create(458,556);
	//explosions.reserve(800);
	state_name="core_game";
	//core_layer.set_original_size(683,384);



	breach_coords=start;
	breach_position=tilemap.tile_coord_to_position(breach_coords);
	breach.setPosition(breach_position.get_x(),breach_position.get_y());

	//path=tilemap.find_path(start,end);

}

void Core_Game_State::update_layer_resolutions(){
	Gamestate::update_layer_resolutions();
	core_layer.resolve_new_resolution();
}



void Core_Game_State::load_sprites(Imagehandler& imagehandler){
	imagehandler.load_sprite(background,"core_game_background");
	imagehandler.load_sprite(breach,"breach");
	//imagehandler.load_text_input_box(tib);
	//imagehandler.load_animation(explosion,"explosion");
}


void Core_Game_State::update(Mousey& mouse, Keyblade& keyboard, Gamepad& gamepad){
	Duration_Check::start("CG update");
	Gamestate::update_gui_layer(mouse,keyboard,gamepad);

	/*
	GUI
	 single list of active buttons, multiple lists of possible buttons. when a new set of buttons is required (video options) the active list becomes a copy of the desired list
		pros: single list of buttons to check, easy to switch between lists, efficient
		cons: ugly, buttons will just dissapear and new ones show up (add fade out?), requires designated gui layer
	*/
	mouse.set_layer(core_layer);


	check_gamepad(gamepad);
	//tib.update(mouse,keyboard);
	check_keyboard(keyboard);
	if(mouse.is_clicked()){
		step=true;
	}



	if(step){
		step=false;
		if(path_num<(int)path.size()){
			breach_coords+=path.at(path_num);
			breach_position=tilemap.tile_coord_to_position(breach_coords);
			breach.setPosition(breach_position.get_x(),breach_position.get_y());
			path_num++;
		}
	}

/*	if(mouse.is_clicked()&& !tib.is_active()){
		explosions.push_back(Audiotest(explosion));
		request_sound(explosions.at(explosions.size()-1).get_keyholder());
		explosions.at(explosions.size()-1).get_animation().start();
		explosions.at(explosions.size()-1).get_animation().set_position(mouse.get_layer_x(), mouse.get_layer_y());
	}
	

	
	//set mouse to layer
	//this checks if the mouse is already locked by previous layers, if not sets mouse's layer coords
	//ex: layer 2 is the runescape inventory which covers a portion of layer 1
	//		 when the mouse is in the bounds of layer 2 layer 1 will be locked, otherwise layer 2 clickables are ignored
	//ex: layer 2 is the minecraft inventory which covers only a portion of layer 1 but locks out layer 1 when active

	//iterate through all objects in layer, for each object do all interactions with all other applicable objects in this layer.
	//if object is clickable check if mouse is in/can currently use layer, if so run is_clicked()/when_clicked()

	/*object types:
	
	moving (moves relative to player without player interaction)
	physical (collides with other physical objects to stop motion/cause effects)
	clickable (self explanatory)
	autonomous (interacts with other objects without the player)

	ex:
	wall=non-moving, physical, non-clickable, non-autonomous 			:: only requires interaction with moving+physical objects
	crafting table= non-moving, physical, clickable, non-autonomous 	:: requires interaction with moving+physical objects and the mouse
	minecraft animal= moving, physical, non-clickable, non-autonomous	:: requires interaction with all physical objects
	minecraft zombie=moving,physical,non-clickable,autonomous 			:: requires interaction with al physicakl objects and all other objects it can interact with (villagers)


		UPDATE TOP LAYER AND DESCEND, RENDER BOTTOM LAYER AND ASCEND

		ALWAYS SET MOUSE TO BACKGROUND LAYER LAST
	*/

	mouse.set_layer(background_layer);

	Duration_Check::stop("CG update");
}

void Core_Game_State::render(sf::RenderWindow& window){
	Duration_Check::start("CG render");
	Gamestate::render_background_layer(window);
	window.setView(core_layer);
	window.draw(tilemap);
	window.draw(breach);
	
/*	tib.draw(window);
	if(explosions.size()!=0){
		for(auto it=explosions.begin(); it!= explosions.end();it++){
			if(!it->get_animation().is_finished()){
				window.draw(it->get_animation().animate());
			}else{
				explosions.erase(it--);
			}
		}
	}*/
	


	Gamestate::render_gui_layer(window);
	Duration_Check::stop("CG render");
}
void Core_Game_State:: execute_data(Data_Packet data){
}

void Core_Game_State::check_keyboard(Keyblade& keyboard){
	if(keyboard.get_key('E').was_just_pressed()){
		send_data.push_back(Data_Packet("set_state",MANAGER,{"pause_menu"}));
	}

	if(keyboard.get_key('w').is_pressed()){
		//pac_man.set_input_dir(Cardinal::North);
	}else if(keyboard.get_key('s').is_pressed()){
		//pac_man.set_input_dir(Cardinal::South);
	}else if(keyboard.get_key('a').is_pressed()){
		//pac_man.set_input_dir(Cardinal::West);
	}else if(keyboard.get_key('d').is_pressed()){
		//pac_man.set_input_dir(Cardinal::East);
	}
}

void Core_Game_State::check_gamepad(Gamepad& gamepad){
	if(gamepad.was_just_pressed(GAMEPAD_START)){
		send_data.push_back(Data_Packet("set_state",MANAGER,{"pause_menu"}));
	}

	if(gamepad.was_just_pressed(GAMEPAD_A)){
		//explosion_sounds.push_back(Audiokeyholder("explosion",false));
		//request_sound(explosion_sounds.at(explosion_sounds.size()-1));
		step=true;
	}




	if(gamepad.get_left_stick_y()>0){
		//pac_man.set_input_dir(Cardinal::South);
	}else if(gamepad.get_left_stick_y()<0 ){
		//pac_man.set_input_dir(Cardinal::North);
	}else if(gamepad.get_left_stick_x()<0 ){
		//pac_man.set_input_dir(Cardinal::West);
	}else if(gamepad.get_left_stick_x()>0 ){
		//pac_man.set_input_dir(Cardinal::East);
	}
}
