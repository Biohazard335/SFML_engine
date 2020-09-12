#ifndef Tilemap_Entity_HPP
#define Tilemap_Entity_HPP

#include "Hitbox.hpp"
#include "Point.hpp"
#include "../image/Animation.hpp"
#include <vector>

class Tilemap;
class Imagehandler;

class Tilemap_Entity{
protected:
	Hitbox hitbox;
	Point hitbox_offset=Point(0,0);
	std::vector<Animation> animations;
	int current_animation_int=0;

	Point current_tile=Point(0,0);

	Point position=Point(0,0);

	Point movement=Point(0,0);

	std::vector<Point> tiles_colliding;

	Hitbox projected_hitbox;
	Point hitbox_size_in_tiles=Point(0,0);
	Point tile_size=Point(0,0);

public:
	Tilemap_Entity(){};

	void create(Point p_p, Tilemap);
	void create_hitbox(Point size_p, Point offset_p);

	Animation& ref_current_animation(){return animations.at(current_animation_int);}
	void set_current_animation(int i_p){current_animation_int=i_p;}

	Hitbox get_hitbox(){return hitbox;}
	Hitbox& ref_hitbox(){return hitbox;}


	Point get_movement(){return movement;}
	Point& ref_movement(){return movement;}
	void set_movement(Point p_p){movement=p_p;}

	Point get_current_tile(){return current_tile;}

	void set_position(Point p_p);
	Point get_position(){return position;}

	virtual void update(Tilemap&);
	virtual void move();
	virtual void tilemap_collide_physics(Tilemap&);
	virtual bool check_tilemap_collision(Tilemap& tilemap);
	virtual void load_animations(Imagehandler&)=0;

};

#endif