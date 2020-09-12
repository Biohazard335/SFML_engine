#ifndef MOUSEY_HPP
#define MOUSEY_HPP

#include <SFML/Graphics.hpp>
#include "../image/Layer.hpp"

class Mousey: public sf::Mouse{
private:
	bool just_pressed= false;
	bool pressed=false;
	bool held=false;

	bool active=true;

	int window_x;
	int window_y;

	std::string current_layer="none";
	bool layer_valid=true;
	int layer_x;
	int layer_y;
	std::string locked_by_layer="none";

	
public:

	int get_window_x(){
		return window_x;
	}
	int get_window_y(){
		return window_y;
	}
	int get_layer_x(){
		return layer_x;
	}
	int get_layer_y(){
		return layer_y;
	}
	bool is_active(){return active;}
	void set_active(bool b_p){active=b_p;}

	void set_layer(Layer&);
	bool is_layer_valid(){return layer_valid;}

	bool is_clicked(){return just_pressed;}
	bool is_pressed(){return pressed;}
	void update(sf::RenderWindow& window);
	void update_jp();

};



#endif