#include "Tileset.hpp"
#include <iostream>
#include <fstream>


void Tileset::load_from_file(){

	std::ifstream map_stream(file_name+".tileset");

	int max=100;
	char*raw;
	raw=(char*)malloc(max);

	if(map_stream.is_open()){
		map_stream.get(raw,max,'X');
		tile_width=atoi(raw);
		map_stream.get();

		map_stream.get(raw,max,'\n');
		tile_height=atoi(raw);
		map_stream.get();

		map_stream.get(raw,max,'X');
		size_x=atoi(raw);
		map_stream.get();

		map_stream.get(raw,max,'\n');
		size_y=atoi(raw);
		map_stream.get();

		map_stream.get(raw,max,'s');
		solid_threshold=atoi(raw);
		map_stream.get();


		map_stream.get(raw,max,'o');
		obj_threshold=atoi(raw);
		map_stream.get();

		map_stream.get();

		while(!map_stream.eof()){
			map_stream.get(raw,max,'\n');
			tileset.push_back(raw);
			map_stream.get();
		}


	}else{
		std::cout<<"ERROR opening file: "<<file_name<<std::endl;
	}

	//std::cout<<"tile size:"<<tile_width<<"X"<<tile_height<<std::endl;
	//std::cout<<"set size:"<<size_x<<"X"<<size_y<<std::endl;
	//std::cout<<"thresholds:"<<solid_threshold<<"s"<<obj_threshold<<"o"<<std::endl;

	//for(int i=0; i<(int)tileset.size();i++){
	//	std::cout<<tileset.at(i)<<std::endl;
	//}

}


int Tileset::type_s_to_int(std::string s_p){
	for(int i=0;i<(int)tileset.size();i++){
		if(tileset.at(i)==s_p){
			return i;
		}
	}
	std::cout<<"ERROR: tile type "<<s_p<<" not found in set "<<name<<std::endl;
	return -1;
}