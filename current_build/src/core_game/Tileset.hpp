#ifndef TILESET_HPP
#define TILESET_HPP

#include <string>
#include <vector>

class Tileset{
private:

	std::string file_name;

	std::string name;
	int tile_width;
	int tile_height;

	int size_x;
	int size_y;

	std::vector<std::string> tileset;

	int solid_threshold;//any number less than this is solid
	int obj_threshold;//any number greater than this threshold represents an empty tile with some gameobject in it

public:
	Tileset(){};
	Tileset(std::string f_p, std::string n_p):file_name(f_p),name(n_p){
		load_from_file();
	}

	void create(std::string f_p, std::string n_p){
		file_name=f_p;
		name=n_p;
		load_from_file();
	}

	std::string get_file_name(){return (file_name+".png");}

	void load_from_file();

	int get_tile_width(){return tile_width;}
	int get_tile_height(){return tile_height;}
	int get_size_x(){return size_x;}
	int get_size_y(){return size_y;}
	int get_obj_threshold(){return obj_threshold;}
	int get_solid_threshold(){return solid_threshold;}
	std::string get_name(){return name;}

	int type_s_to_int(std::string);

	std::string at(int i_p){return tileset.at(i_p);}
	int get_set_size(){return tileset.size();}

};

#endif