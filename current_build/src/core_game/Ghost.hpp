#ifndef GHOST_HPP
#define GHOST_HPP

#include "Tilemap_Entity.hpp"
#include <string>

class Ghost:public Tilemap_Entity{

private:
	std::string name;

	int intelligence;
	int speed;
	int afraid_speed=1;
	Point spawn;

	Point momentum=Point(0,0);
	Point desired_dir;

	int respawn_timer_max=60;
	int respawn_timer=0;

	Point pac_tile;
	bool dead=false;
	bool afraid=false;

	bool warping=false;

public:
	Ghost(){}
	Ghost(std::string n_p, int i_p, int s_p);

	int get_speed(){return speed;}
	void set_speed(int s_p){speed=s_p;}

	int get_intelligence(){return intelligence;}
	void set_intelligence(int i_p){intelligence=i_p;}

	int get_respawn_timer(){return respawn_timer;}
	void set_respawn_timer(int r_p){respawn_timer=r_p;}

	void update(Tilemap&) override;
	void load_animations(Imagehandler&) override;
	void set_pac_tile(Point p_p){pac_tile=p_p;}
	void set_spawn(Point p_p){spawn=p_p;}

	void die(){
		dead=true;
		current_animation_int=2;
	}
	bool is_dead(){return dead;}
	void set_afraid(bool b_p){afraid=b_p;}
	void respawn(){
		dead=false;
		afraid=false;
		current_animation_int=0;
	}

	bool is_warping(){return warping;}
	void set_warping(bool b_p){warping=b_p;}

};


#endif