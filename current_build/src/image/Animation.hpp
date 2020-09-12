#ifndef ANIMATION_HPP
#define ANIMATION_HPP


#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "../core_game/Point.hpp"


class Animation{
private:


	int frame_width=0;
	int frame_height=0;
	int rect_x=0;
	int rect_y=0;

	int rotation=0;

	bool loop=false;
	bool finished=false;

	int fps_timer=0;
	int fps_timer_max=5;

	int current_frame=0;

	std::vector<sf::Sprite> sprites;
	int sprites_length=1;


public:
	Animation(){;}
	void load(sf::Texture&,int, int, int,int);

	void set_position(int,int);
	void move(int,int);

	void move(Point p_p);

	int get_frame_width(){return frame_width;}
	int get_frame_height(){return frame_height;}

	bool is_finished(){return finished;}
	void start(){finished=false;current_frame=0;}

	void set_looping(bool l_p){loop=l_p;}

	void set_rotation(int r_p){
		rotation=r_p;
		for(int i=0;i<sprites_length;i++){
			sprites[i].setRotation(rotation);
		}
	}

	sf::Sprite animate();
};

#endif