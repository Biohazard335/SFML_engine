#include "Tilemap_Entity.hpp"
#include "Tilemap.hpp"
#include <iostream>


void Tilemap_Entity::create(Point p_p, Tilemap t_p){
	hitbox.create(0,0,animations.at(0).get_frame_width(),animations.at(0).get_frame_height());
	tile_size= Point(t_p.get_tileset().get_tile_width(),t_p.get_tileset().get_tile_height());
	set_position(p_p);
}


void Tilemap_Entity::create_hitbox(Point size_p, Point offset_p){
	hitbox_offset=offset_p;
	hitbox_size_in_tiles=Point(size_p.get_x()/(tile_size.get_x()+1),size_p.get_y()/(tile_size.get_y()+1));//+1 ensures that same size as frame
	hitbox.create(position.get_x()+hitbox_offset.get_x(),position.get_y()+hitbox_offset.get_y(),size_p.get_x(),size_p.get_y());
}


void Tilemap_Entity::move(){
	position+=movement;
	for(int i=0;i<(int)animations.size();i++){
		animations.at(i).move(movement);
	}
	hitbox.move(movement);
}

void Tilemap_Entity::set_position(Point p_p){
	position=p_p;
	hitbox.set_position(position.get_x()+hitbox_offset.get_x(),position.get_y()+hitbox_offset.get_y());

	for(int i=0;i<(int)animations.size();i++){
		animations.at(i).set_position(position.get_x()+animations.at(0).get_frame_width()/2,position.get_y()+animations.at(0).get_frame_height()/2);
	}
}


void Tilemap_Entity::update(Tilemap& tilemap){
	tilemap_collide_physics(tilemap);
}

void Tilemap_Entity::tilemap_collide_physics(Tilemap& tilemap){
	current_tile=tilemap.position_to_tile_coord(Point(hitbox.get_x()+hitbox.get_width()/2,hitbox.get_y()+hitbox.get_height()/2));
	Tile check_tile;

	for(int i=-1-hitbox_size_in_tiles.get_x();i<=hitbox_size_in_tiles.get_x()+1;i++){
		for(int j=-1-hitbox_size_in_tiles.get_y();j<=hitbox_size_in_tiles.get_y()+1;j++){

			if(current_tile.get_x()+i>=0 && current_tile.get_x()+i<tilemap.get_length_x() && current_tile.get_y()+j>=0 && current_tile.get_y()+j<tilemap.get_length_y()){
				check_tile=tilemap.get_tile(current_tile+Point(i,j));
				projected_hitbox=hitbox;

				if(check_tile.is_solid()){
					//std::cout<<Point(current_tile+Point(i,j)).get_x()<<","<<Point(current_tile+Point(i,j)).get_y()<<"|";
					projected_hitbox.move(0,movement.get_y());

					//std::cout<<projected_hitbox.get_x()<<","<<projected_hitbox.get_y()<<":"<<projected_hitbox.get_width()<<"X"<<projected_hitbox.get_height()<<"VS";
					//std::cout<<check_tile.get_map_x()<<","<<check_tile.get_map_y()<<"@";
					//std::cout<<check_tile.get_hitbox().get_x()<<","<<check_tile.get_hitbox().get_y()<<":";
					//std::cout<<check_tile.get_hitbox().get_width()<<"X"<<check_tile.get_hitbox().get_height()<<std::endl;
					if(projected_hitbox.is_colliding(check_tile.get_hitbox())){
						movement.set_y(0);
						if(check_tile.get_hitbox().get_y()>hitbox.get_y()){
							set_position(Point(position.get_x(),check_tile.get_hitbox().get_y()-hitbox.get_height()+hitbox_offset.get_y()));
						}else{
							set_position(Point(position.get_x(),check_tile.get_hitbox().get_y()+check_tile.get_hitbox().get_height()+hitbox_offset.get_y()));
						}
					}
					projected_hitbox=hitbox;
					projected_hitbox.move(movement.get_x(),0);

					if(projected_hitbox.is_colliding(check_tile.get_hitbox())){
						movement.set_x(0);
						if(check_tile.get_hitbox().get_x()>hitbox.get_x()){
							set_position(Point(check_tile.get_hitbox().get_x()-hitbox.get_width()+hitbox_offset.get_x(),position.get_y()));
						}else{
							set_position(Point(check_tile.get_hitbox().get_x()+check_tile.get_hitbox().get_width()+hitbox_offset.get_x(),position.get_y()));
						}
					}
				}


			}


		}
	}

	//must check for solid tiles first otherwise collisions may be incorrect
	tiles_colliding.clear();

	for(int i=-1-hitbox_size_in_tiles.get_x();i<=hitbox_size_in_tiles.get_x()+1;i++){
		for(int j=-1-hitbox_size_in_tiles.get_y();i<=hitbox_size_in_tiles.get_y()+1;i++){

			if(i>=0 && i<tilemap.get_length_x() && j>=0 && j<tilemap.get_length_y()){
				check_tile=tilemap.get_tile(i,j);
				projected_hitbox=hitbox;

				projected_hitbox.move(movement);
				if(projected_hitbox.is_colliding(check_tile.get_hitbox())){
					tiles_colliding.push_back(Point(i,j));
				}
				

				//if specific tiles do things on collision put it here
			}


		}
	}
	current_tile=tilemap.position_to_tile_coord(Point(hitbox.get_x()+hitbox.get_width()/2,hitbox.get_y()+hitbox.get_height()/2));
}
bool Tilemap_Entity::check_tilemap_collision(Tilemap& tilemap){
	current_tile=tilemap.position_to_tile_coord(Point(hitbox.get_x()+hitbox.get_width()/2,hitbox.get_y()+hitbox.get_height()/2));
	Tile check_tile;

	for(int i=-1-hitbox_size_in_tiles.get_x();i<=hitbox_size_in_tiles.get_x()+1;i++){
		for(int j=-1-hitbox_size_in_tiles.get_y();j<=hitbox_size_in_tiles.get_y()+1;j++){

			if(current_tile.get_x()+i>=0 && current_tile.get_x()+i<tilemap.get_length_x() && current_tile.get_y()+j>=0 && current_tile.get_y()+j<tilemap.get_length_y()){
				check_tile=tilemap.get_tile(current_tile+Point(i,j));
				projected_hitbox=hitbox;

				if(check_tile.is_solid()){  //if you want to check for something other than solidity put it here
					projected_hitbox.move(0,movement.get_y());

					if(projected_hitbox.is_colliding(check_tile.get_hitbox())){
						return true;
					}
					projected_hitbox=hitbox;
					projected_hitbox.move(movement.get_x(),0);

					if(projected_hitbox.is_colliding(check_tile.get_hitbox())){
						return true;
					}
					projected_hitbox=hitbox;
					projected_hitbox.move(movement);

					if(projected_hitbox.is_colliding(check_tile.get_hitbox())){
						return true;
					}
				}
			}
		}
	}
	return false;

}

