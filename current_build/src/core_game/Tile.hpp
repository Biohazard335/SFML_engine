#ifndef TILE_HPP
#define TILE_HPP
#include "Point.hpp"
#include "Hitbox.hpp"
#include <string>

class Tileset;


class Tile{
private:
	int map_x=0;
	int map_y=0;
	bool solid=false;
	int tile_type=-1;
	int rotation_int=0; //number of clockwise 90* turns
	std::string type_s;
	Hitbox hitbox;
public:
	Tile(){}
	Tile(int x_p, int y_p, bool s_p, int t_p, std::string ts_p): map_x(x_p),map_y(y_p),solid(s_p),tile_type(t_p),type_s(ts_p){}

	void load(int,int,Tileset,std::string);

	int get_map_x(){return map_x;}
	int get_map_y(){return map_y;}
	bool is_solid(){return solid;}
	int get_tile_type(){return tile_type;}
	std::string get_type_s(){return type_s;}
	int get_rotation_int(){return rotation_int;}

	void set_map_x(int x_p){map_x=x_p;}
	void set_map_y(int y_p){map_y=y_p;}
	void set_solid(bool b_p){solid=b_p;}
	void set_tile_type(int i_p,std::string s_p){tile_type=i_p;type_s=s_p;}


	Hitbox get_hitbox(){return hitbox;}
	Hitbox& ref_hitbox(){return hitbox;}

};

#endif