#ifndef PAC_MAN_HPP
#define PAC_MAN_HPP

#include "Tilemap_Entity.hpp"

class Pac_man:public Tilemap_Entity{
private:

	Point spawn;

	Point input_dir=Point(0,0);
	Point momentum=Point(-1,0);

	int speed=2;
	bool cherry=false;
	int cherry_timer=0;
	int cherry_timer_max=400;
	int score=0;

	int death_timer=-1;
	int death_timer_max=30;

	bool warping=false;
public:
	Pac_man(){momentum*=speed;movement=momentum;};

	void update(Tilemap&) override;
	void load_animations(Imagehandler&) override;

	Point get_input_dir(){return input_dir;}
	Point& ref_input_dir(){return input_dir;}
	void set_input_dir(Point p_p){input_dir=p_p;}

	Point get_momentum(){return momentum;}
	Point& ref_momentum(){return momentum;}
	void set_momentum(Point p_p){momentum=p_p;}

	int get_speed(){return speed;}
	void set_speed(int i_p){speed=i_p;}

	int get_score(){return score;}
	void add_to_score(int i_p){score+=i_p;}

	bool has_cherry(){return cherry;}

	int get_death_timer(){return death_timer;}

	void set_spawn(Point p_p){spawn=p_p;}

	void die(){
		death_timer=death_timer_max;
		current_animation_int=1;
		animations.at(1).start();
	}

	void respawn();

	bool is_warping(){return warping;}
	void set_warping(bool b_p){warping=b_p;}
};



#endif