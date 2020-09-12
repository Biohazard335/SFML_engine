#include "Tilemap.hpp"
#include "Path_Node.hpp"
#include "../communal/Duration_Check.hpp"
#include <fstream>

std::vector<Tileset> Tilemap::tilesets=std::vector<Tileset>();

void Tilemap::add_tileset(std::string file_p,std::string n_p){
	tilesets.push_back(Tileset(file_p,n_p));
}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform *= getTransform();
	states.texture = &tile_texture;
	target.draw(vertex_array, states);
}

void Tilemap::load_from_file(std::string file_p){
	std::ifstream map_stream(file_p);

	int max=100;
	char*raw;
	raw=(char*)malloc(max);

	if(map_stream.is_open()){

		map_stream.get(raw,max,':');
		tileset_num=atoi(raw);
		map_stream.get();

		tileset=tilesets.at(tileset_num);
		tile_texture.loadFromFile(tileset.get_file_name());

		map_stream.get(raw,max,'X');
		length_x=atoi(raw);
		map_stream.get();

		map_stream.get(raw,max,'\n');
		length_y=atoi(raw);
		map_stream.get();

		if(length_y!=-1 && length_x!=-1){
			map.resize(length_x*length_y);

			vertex_array.setPrimitiveType(sf::Quads);
			vertex_array.resize(length_x*length_y*4);

			for(int j=0;j<length_y;j++){
				for(int i=0;i<length_x;i++){

					map_stream.get(raw,max,',');
					map.at(i+j*length_x).load(i,j,tileset,raw);
					map_stream.get();

					sf::Vertex* quad = &vertex_array[(i+(j*length_x))*4];

					int rotation=map.at(i+j*length_x).get_rotation_int();

					quad[(0+4-rotation)%4].position=sf::Vector2f(i* tileset.get_tile_width(),j*tileset.get_tile_height());
					quad[(1+4-rotation)%4].position=sf::Vector2f((i+1)* tileset.get_tile_width(),j*tileset.get_tile_height());
					quad[(2+4-rotation)%4].position=sf::Vector2f((i+1)* tileset.get_tile_width(),(j+1)*tileset.get_tile_height());
					quad[(3+4-rotation)%4].position=sf::Vector2f(i* tileset.get_tile_width(),(j+1)*tileset.get_tile_height());


					int tile_type=map.at(i+j*length_x).get_tile_type();
					if(tile_type>tileset.get_obj_threshold()){
						tile_type=tileset.get_solid_threshold();
					}

					int tu= (tile_type % tileset.get_size_x());
					int tv= (tile_type / tileset.get_size_x());

					quad[0].texCoords=sf::Vector2f(tu*tileset.get_tile_width(),tv*tileset.get_tile_height());
					quad[1].texCoords=sf::Vector2f((tu+1)*tileset.get_tile_width(),tv*tileset.get_tile_height());
					quad[2].texCoords=sf::Vector2f((tu+1)*tileset.get_tile_width(),(tv+1)*tileset.get_tile_height());
					quad[3].texCoords=sf::Vector2f(tu*tileset.get_tile_width(),(tv+1)*tileset.get_tile_height());

				}
				map_stream.get();
			}


		}else{
			std::cout<<"ERROR: map width and height not read!"<<std::endl;
		}

	}else{
		std::cout<<"ERROR: map stream didn't open!"<<std::endl;
	}
}

void Tilemap::set_tile_type(int x_p, int y_p, int tile_type_p){
	map.at(x_p+y_p*length_x).set_tile_type(tile_type_p,tileset.at(tile_type_p));

	if(tile_type_p<tileset.get_solid_threshold()){
		ref_tile(x_p,y_p).set_solid(true);
	}

	if(tile_type_p>tileset.get_obj_threshold()){
		tile_type_p=tileset.get_solid_threshold();;
	}

	sf::Vertex* quad = &vertex_array[(x_p+(y_p*length_x))*4];
	int tu= (tile_type_p % tileset.get_size_x());
	int tv= (tile_type_p / tileset.get_size_x());

	quad[0].texCoords=sf::Vector2f(tu*tileset.get_tile_width(),tv*tileset.get_tile_height());
	quad[1].texCoords=sf::Vector2f((tu+1)*tileset.get_tile_width(),tv*tileset.get_tile_height());
	quad[2].texCoords=sf::Vector2f((tu+1)*tileset.get_tile_width(),(tv+1)*tileset.get_tile_height());
	quad[3].texCoords=sf::Vector2f(tu*tileset.get_tile_width(),(tv+1)*tileset.get_tile_height());

}

void Tilemap::set_tile_type(Point p_p, std::string s_p){
	set_tile_type(p_p.get_x(),p_p.get_y(),tileset.type_s_to_int(s_p));
}



std::vector<Point> Tilemap::find_path(Point start, Point end){
	Duration_Check::start("--pathfinding");

	std::vector<std::shared_ptr<Path_Node>> open;
	std::vector<std::shared_ptr<Path_Node>> closed;
	std::vector<Point> path;

	std::shared_ptr<Path_Node> current;
	Point neighbor;
	bool neighbor_closed;
	bool neighbor_already_open;
	Path_Node temp;

	bool path_found=false;



	open.push_back(std::make_shared<Path_Node>(start,nullptr,end));
	current=open.at(0);

	while(!path_found){

		if((int)open.size()>0){

			current=open.at(0);
			for(int i=0;i<(int)open.size();i++){
				if(current->get_h_cost()>open.at(i)->get_h_cost() || (current->get_h_cost()==open.at(i)->get_h_cost()&&current->get_h_cost()>open.at(i)->get_h_cost())){
					current=open.at(i);
				}
			}


			if(current->get_coordinates()!=end){

				closed.push_back(current);

				for(auto it=open.begin();it!=open.end();){
					if((*it)->get_coordinates()==current->get_coordinates()){
						open.erase(it);
					}else{
						++it;
					}
				}

				//std::cout<<current->get_coordinates().get_x()<<","<<current->get_coordinates().get_y()<<std::endl;

				for(int i=-1;i<=1;i++){
					for(int j=-1;j<=1;j++){
						neighbor=current->get_coordinates()+Point(i,j);
	//diagonals				if(neighbor.get_x()>=0 && neighbor.get_y()>=0 && neighbor.get_x()<tilemap.get_length_x() && neighbor.get_y()<tilemap.get_length_y() &&!(i==0 && j==0)){
						if(neighbor.get_x()>=0 && neighbor.get_y()>=0 && neighbor.get_x()<get_length_x() && neighbor.get_y()<get_length_y() &&(i==0 || j==0) &&!(i==0 && j==0)){//cardinal	
							if(!get_tile(neighbor).is_solid()){
								neighbor_closed=false;
								for(int c=0;c<(int)closed.size();c++){
									if(closed.at(c)->get_coordinates()==neighbor){
										neighbor_closed=true;
										break;
									}
								}

								if(!neighbor_closed){
									neighbor_already_open=false;
									for(int o=0;o<(int)open.size();o++){
										if(open.at(o)->get_coordinates()==neighbor){
											neighbor_already_open=true;
											temp.recreate(neighbor,current,end);
											if(temp.get_g_cost()<open.at(o)->get_g_cost()){
												open.at(o)->recreate(neighbor,current,end);
											}
											break;
										}
									}

									if(!neighbor_already_open){
										open.push_back(std::make_shared<Path_Node>(neighbor,current,end));
									}

								}
							}
						}
					}
				}

			}else{
				std::shared_ptr<Path_Node> parent=current->get_parent();
				while(parent!=nullptr){
					path.emplace(path.begin(),Point(current->get_coordinates()-parent->get_coordinates()));
					current=parent;
					parent=current->get_parent();
				}

				for(int i=0;i<(int)path.size();i++){
					//std::cout<<path.at(i).get_x()<<","<<path.at(i).get_y()<<std::endl;
				}
				path_found=true;
			}
		


		}else{
			path_found=true;
			std::cout<<"unable to find path!"<<std::endl;
		}
	}

	Duration_Check::stop("--pathfinding");
	return path;
}