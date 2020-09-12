#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <vector>
#include <string>
#include "SFML/Graphics.hpp"
#include "Tile.hpp"
#include "Tileset.hpp"
#include <string>
#include <iostream>

class Tilemap: public sf::Drawable, public sf::Transformable{
private:
	static std::vector<Tileset> tilesets;

	Tileset tileset;

	std::vector<Tile> map;

	sf::Texture tile_texture;
	sf::VertexArray vertex_array;

	int tileset_num;

	int length_x=-1;
	int length_y=-1;

	Point position;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:

	Tilemap(){}
	Tilemap(std::string f_p){load_from_file(f_p);}

	void load_from_file(std::string);

	Tile get_tile(int x_p,int y_p){return map.at(x_p+ y_p*length_x);}
	Tile& ref_tile(int x_p,int y_p){return map.at(x_p+ y_p*length_x);}

	Tile get_tile(Point p_p){return map.at(p_p.get_x()+ p_p.get_y()*length_x);}
	Tile& ref_tile(Point p_p){return map.at(p_p.get_x()+ p_p.get_y()*length_x);}

	int get_length_x(){return length_x;}
	void set_length_x(int i_p){length_x=i_p;}
	
	int get_length_y(){return length_y;}
	void set_length_y(int i_p){length_y=i_p;}

	Point get_position(){return position;}
	void set_position(Point p_p){
		position=p_p;
		setPosition(position.get_x(),position.get_y());
		for(int i=0;i<length_x;i++){
			for(int j=0;j<length_y;j++){
				ref_tile(i,j).ref_hitbox().set_position(position.get_x()+tileset.get_tile_width()*i,position.get_y()+tileset.get_tile_height()*j);
			}
		}
	}

	Tileset get_tileset(){return tileset;}

	Point tile_coord_to_position(int x_p, int y_p){
		return Point(x_p*tileset.get_tile_width() +position.get_x(), y_p*tileset.get_tile_height()+position.get_y());
	}
	Point tile_coord_to_position(Point p_p){
		return Point(p_p.get_x()*tileset.get_tile_width() +position.get_x(), p_p.get_y()*tileset.get_tile_height()+position.get_y());
	}

	Point position_to_tile_coord(Point p_p){
		if(p_p.get_x()<position.get_x() || p_p.get_x()>position.get_x()+length_x*tileset.get_tile_width() 
			||p_p.get_y()<position.get_y() || p_p.get_y()>position.get_y()+length_y*tileset.get_tile_height()){
			return Point(-1,-1);
		}else{
			return Point((p_p.get_x()-position.get_x())/tileset.get_tile_width(),(p_p.get_y()-position.get_y())/tileset.get_tile_height());
		}
	}

	void set_tile_type(int,int,int);
	void set_tile_type(Point,std::string);


	static void add_tileset(std::string,std::string);


	std::vector<Point> find_path(Point start, Point end);

};

#endif