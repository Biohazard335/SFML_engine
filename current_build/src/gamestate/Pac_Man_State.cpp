#include "Pac_Man_State.hpp"

#include <fstream>


Pac_Man_State::Pac_Man_State(Imagehandler& imagehandler):core_layer("core_layer"){
	tilemap.load_from_file("../assets/core_game/maps/map1.map");
	tilemap.set_position(Point((Layer::get_default_res_x()/2)-(tilemap.get_tileset().get_tile_width()*tilemap.get_length_x()/2), 
		(Layer::get_default_res_y()/2)-(tilemap.get_tileset().get_tile_height()*tilemap.get_length_y()/2)));


	for(int i=0;i<tilemap.get_length_x();i++){
		for(int j=0;j<tilemap.get_length_y();j++){
			std::string type_s=tilemap.get_tile(i,j).get_type_s();
			if(type_s=="pac_spawn"){
				pac_spawn=Point(i,j);
			}else if(type_s=="ghost_spawn"){
				ghost_spawn=Point(i,j);
			}else if(type_s=="warp_1"){
				warp_1=Point(i,j);
			}else if(type_s=="warp_2"){
				warp_2=Point(i,j);
			}
		}
	}

	ghosts.push_back(Ghost("red",70,2));
	ghosts.push_back(Ghost("green",60,2));
	ghosts.push_back(Ghost("orange",50,2));
	ghosts.push_back(Ghost("purple",40,2));

	load_sprites(imagehandler);
	//tib.create(458,556);
	//explosions.reserve(800);
	explosion_sounds.reserve(800);
	state_name="pac_man";
	for(int i=0;i<(int)ghosts.size();i++){
		ghosts.at(i).create(tilemap.tile_coord_to_position(ghost_spawn),tilemap);
		ghosts.at(i).set_respawn_timer(30*i);
		ghosts.at(i).set_spawn(ghost_spawn);
	}
	pac_man.create(tilemap.tile_coord_to_position(pac_spawn),tilemap);
	pac_man.set_spawn(pac_spawn);
	core_layer.set_original_size(1920,1080);
}

void Pac_Man_State::update_layer_resolutions(){
	Gamestate::update_layer_resolutions();
	core_layer.resolve_new_resolution();
}



void Pac_Man_State::load_sprites(Imagehandler& imagehandler){
	imagehandler.load_sprite(background,"core_game_background");
	//imagehandler.load_text_input_box(tib);
	//imagehandler.load_animation(explosion,"explosion");
	for(int i=0;i<(int)ghosts.size();i++){
		ghosts.at(i).load_animations(imagehandler);
		//imagehandler.load_animation(ghosts.at(i).ref_animation(),"ghost_"+std::to_string(i));
	}

	pac_man.load_animations(imagehandler);
	//imagehandler.load_animation(pac_man.ref_animation(),"pac-man");
}


void Pac_Man_State::update(Mousey& mouse, Keyblade& keyboard, Gamepad& gamepad){
	Duration_Check::start("CG update");
	Gamestate::update_gui_layer(mouse,keyboard,gamepad);

	/*
	GUI
	 single list of active buttons, multiple lists of possible buttons. when a new set of buttons is required (video options) the active list becomes a copy of the desired list
		pros: single list of buttons to check, easy to switch between lists, efficient
		cons: ugly, buttons will just dissapear and new ones show up (add fade out?), requires designated gui layer
	*/
	mouse.set_layer(core_layer);


	pac_man.set_input_dir(Point(0,0));
	check_gamepad(gamepad);
	//tib.update(mouse,keyboard);
	check_keyboard(keyboard);

	pac_man.update(tilemap);
	pac_man.move();

	if(pac_man.get_current_tile()==warp_1){
		if(!pac_man.is_warping()){
			pac_man.set_warping(true);
			pac_man.set_position(tilemap.tile_coord_to_position(warp_2));
		}
	}else if(pac_man.get_current_tile()==warp_2){
		if(!pac_man.is_warping()){
			pac_man.set_warping(true);
			pac_man.set_position(tilemap.tile_coord_to_position(warp_1));
		}
	}else{
		pac_man.set_warping(false);
	}

	if(pac_man.get_death_timer()==-1){
		for(int i=0;i<(int)ghosts.size();i++){
			ghosts.at(i).set_afraid(pac_man.has_cherry());
			ghosts.at(i).set_pac_tile(pac_man.get_current_tile());
			ghosts.at(i).update(tilemap);
			ghosts.at(i).move();
			if(pac_man.get_hitbox().is_colliding(ghosts.at(i).get_hitbox())){
				if(!ghosts.at(i).is_dead()){
					if(!pac_man.has_cherry()){
						pac_man.die();
						break;
					}else{
						ghosts.at(i).die();
					}
				}
			}

			if(ghosts.at(i).get_current_tile()==warp_1){
				if(!ghosts.at(i).is_warping()){
					ghosts.at(i).set_warping(true);
					ghosts.at(i).set_position(tilemap.tile_coord_to_position(warp_2));
				}
			}else if(ghosts.at(i).get_current_tile()==warp_2){
				if(!ghosts.at(i).is_warping()){
					ghosts.at(i).set_warping(true);
					ghosts.at(i).set_position(tilemap.tile_coord_to_position(warp_1));
				}
			}else{
				ghosts.at(i).set_warping(false);
			}
		}
	}else if(pac_man.get_death_timer()==0){
		pac_man.set_position(tilemap.tile_coord_to_position(pac_spawn));
		pac_man.respawn();

		for(int j=0;j<(int)ghosts.size();j++){
			ghosts.at(j).set_position(tilemap.tile_coord_to_position(ghost_spawn));
			ghosts.at(j).set_respawn_timer(30*j);
			ghosts.at(j).respawn();
		}

	}





	/*

	if(mouse.is_clicked()&& !tib.is_active()){
		explosions.push_back(Audiotest(explosion));
		request_sound(explosions.at(explosions.size()-1).get_keyholder());
		explosions.at(explosions.size()-1).get_animation().start();
		explosions.at(explosions.size()-1).get_animation().set_position(mouse.get_layer_x()-50, mouse.get_layer_y()-50);
	}
	*/

	
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



void Pac_Man_State::render(sf::RenderWindow& window){
	Duration_Check::start("CG render");
	Gamestate::render_background_layer(window);
	/*
	tib.draw(window);
	if(explosions.size()!=0){
		for(auto it=explosions.begin(); it!= explosions.end();it++){
			if(!it->get_animation().is_finished()){
				window.draw(it->get_animation().animate());
			}else{
				explosions.erase(it--);
			}
		}
	}
	*/
	window.setView(core_layer);

	window.draw(tilemap);


	window.draw(pac_man.ref_current_animation().animate());

	for(unsigned int i=0;i<ghosts.size();i++){
		window.draw(ghosts.at(i).ref_current_animation().animate());
	}



	Gamestate::render_gui_layer(window);
	Duration_Check::stop("CG render");
}
void Pac_Man_State:: execute_data(Data_Packet data){
}

void Pac_Man_State::check_keyboard(Keyblade& keyboard){
	if(keyboard.get_key('E').was_just_pressed()){
		send_data.push_back(Data_Packet("set_state",MANAGER,{"pause_menu"}));
	}

	if(keyboard.get_key('w').is_pressed()){
		pac_man.set_input_dir(Cardinal::North);
	}else if(keyboard.get_key('s').is_pressed()){
		pac_man.set_input_dir(Cardinal::South);
	}else if(keyboard.get_key('a').is_pressed()){
		pac_man.set_input_dir(Cardinal::West);
	}else if(keyboard.get_key('d').is_pressed()){
		pac_man.set_input_dir(Cardinal::East);
	}
}

void Pac_Man_State::check_gamepad(Gamepad& gamepad){
	if(gamepad.was_just_pressed(GAMEPAD_START)){
		send_data.push_back(Data_Packet("set_state",MANAGER,{"pause_menu"}));
	}

	if(gamepad.was_just_pressed(GAMEPAD_A)){
		explosion_sounds.push_back(Audiokeyholder("explosion",false));
		request_sound(explosion_sounds.at(explosion_sounds.size()-1));
	}




	if(gamepad.get_left_stick_y()>0){
		pac_man.set_input_dir(Cardinal::South);
	}else if(gamepad.get_left_stick_y()<0 ){
		pac_man.set_input_dir(Cardinal::North);
	}else if(gamepad.get_left_stick_x()<0 ){
		pac_man.set_input_dir(Cardinal::West);
	}else if(gamepad.get_left_stick_x()>0 ){
		pac_man.set_input_dir(Cardinal::East);
	}
}
