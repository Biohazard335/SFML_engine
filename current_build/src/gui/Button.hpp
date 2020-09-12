#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "../input/Mousey.hpp"
#include "../input/Gamepad.hpp"
#include "../communal/Data_Packet.hpp"

enum BUTTON_TYPE{
	INVALID=0,
	SPRITE_BUTTON=1,
	TEXT_BUTTON=2,
	M_E_B_L=3,
	SLIDER=4
};



class Button{
protected:
	std::string name;
	int x;
	int y;
	int width;
	int height;
	Data_Packet data;
	bool active=true;
	bool visible=true;

	int button_up=-1;
	int button_down=-1;
	int button_left=-1;
	int button_right=-1;

	bool togglable=false;
	INTERACTION_LEVEL interaction_level;
	BUTTON_TYPE type=INVALID;


	bool on=false;
	bool highlighted=false;
	bool move_with_environment=false;
	bool using_gamepad=false;

public:

	Button(){};

	virtual void draw(sf::RenderWindow& window){};

	virtual bool check_clicked(Mousey&);
	virtual bool check_highlighted(Mousey&);

	Data_Packet get_data(){return data;}
	void set_data(Data_Packet data_p){data=data_p;}

	std::string get_name(){return name;}
	int get_x(){return x;}
	int get_y(){return y;}
	BUTTON_TYPE get_type(){return type;}

	void set_active(bool set){active=set;}
	bool is_active(){return active;}

	bool is_on(){return on;}
	virtual void manually_set_on(bool on_p){on=on_p;}
	virtual void manually_set_highlighted(bool h_p){highlighted=h_p;}

	bool is_highlighted(){return highlighted;}
	bool is_togglable(){return togglable;}
	void set_togglable(bool t_p){togglable=t_p;}
	void toggle_on(){on=!on;}
	bool is_using_gamepad(){return using_gamepad;}

	void set_visible(bool set){visible = set;}
	bool is_visible(){return visible;}

	virtual int get_button_up(){return button_up;}
	virtual int get_button_down(){return button_down;}
	virtual int get_button_left(){return button_left;}
	virtual int get_button_right(){return button_right;}

	virtual bool pushed_by_gamepad(Gamepad& gamepad){return true;}
	virtual void update(Gamepad& gamepad){}

	void set_move_with_environment(bool set){move_with_environment=set;}

	INTERACTION_LEVEL get_interaction_level(){return interaction_level;}
};


#endif