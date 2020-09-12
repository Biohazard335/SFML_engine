#include "Pac_man.hpp"
#include "Tilemap.hpp"
#include "../image/Imagehandler.hpp"

void Pac_man::update(Tilemap& tilemap){
	if(death_timer==-1){
		if(cherry_timer!=0){
			cherry_timer--;
		}else{
			cherry=false;
		}

		if(input_dir!=Point(0,0)){
			movement=input_dir*speed;
			tilemap_collide_physics(tilemap);
		}
		if(movement!=input_dir*speed){
			movement=momentum;
			tilemap_collide_physics(tilemap);
		}
		momentum=movement;
		if(movement!=Point(0,0)){
			animations.at(0).set_rotation(Cardinal::to_degrees(movement/speed));
		}

		if(tilemap.get_tile(current_tile).get_type_s()=="pellet"){
			tilemap.set_tile_type(current_tile.get_x(),current_tile.get_y(),tilemap.get_tileset().type_s_to_int("empty"));
			score+=1;
		}
		if(tilemap.get_tile(current_tile).get_type_s()=="cherry"){
			tilemap.set_tile_type(current_tile.get_x(),current_tile.get_y(),tilemap.get_tileset().type_s_to_int("empty"));
			cherry=true;
			cherry_timer=cherry_timer_max;
		}
	}else{
		death_timer--;
		movement=Point(0,0);
	}


}


void Pac_man::load_animations(Imagehandler& imagehandler){
	animations.push_back(Animation());
	animations.push_back(Animation());
	imagehandler.load_animation(animations.at(0),"pac-man");
	animations.at(0).set_looping(true);
	imagehandler.load_animation(animations.at(1),"pac-man_dies");
}


void Pac_man::respawn(){
	death_timer=-1;
	cherry_timer=-1;
	current_animation_int=0;
	input_dir=Point(-1,0);
	momentum=Point(-1*speed,0);
	movement=Point(-1*speed,0);
}