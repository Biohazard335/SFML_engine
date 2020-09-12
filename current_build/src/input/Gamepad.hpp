#ifndef GAMEPAD_HPP
#define GAMEPAD_HPP

#include <SFML/Window/Event.hpp>

enum GAMEPAD_BIT{
	INVALID_BIT=0,
	GAMEPAD_A=		0b1,
	GAMEPAD_B=		0b10,
	GAMEPAD_X=		0b100,
	GAMEPAD_Y=		0b1000,
	GAMEPAD_LB=		0b10000,
	GAMEPAD_RB=		0b100000,
	GAMEPAD_SELECT=	0b1000000,
	GAMEPAD_START=	0b10000000,
	GAMEPAD_MIDDLE= 0b100000000,
	GAMEPAD_LS=		0b1000000000,
	GAMEPAD_RS=		0b10000000000,
	GAMEPAD_LEFT=	0b100000000000,
	GAMEPAD_RIGHT=	0b1000000000000,
	GAMEPAD_UP=		0b10000000000000,
	GAMEPAD_DOWN=	0b100000000000000
};



class Gamepad{

private:
	int button_selected=0;
	bool button_mode=true;
	bool button_mode_pause=false;

	bool connected=false;
	bool active=false;

	unsigned int joystick_number=0;

	unsigned int buttons_pressed=0;
	unsigned int buttons_just_pressed=0;

	double dead_zone=20;

	double left_stick_x=0;
	double left_stick_y=0;
	double right_stick_x=0;
	double right_stick_y=0;
	double left_trigger=0;
	double right_trigger=0;

	std:: string current_layer;


public:

	Gamepad();

	void event_update(sf::Event& event);
	void update_button(GAMEPAD_BIT, bool);

	bool is_pressed(GAMEPAD_BIT);
	bool was_just_pressed(GAMEPAD_BIT);
	bool is_pressed(unsigned int);
	bool was_just_pressed(unsigned int);
	bool is_active(){return active;}
	bool is_connected(){return connected;}

	void set_active(bool b_p){active=b_p;}
	void set_connected(bool b_p){connected=b_p;}

	void update_jps();

	int get_button_selected(){return button_selected;}
	bool get_button_mode(){return button_mode;}
	bool get_button_mode_pause(){return button_mode_pause;}
	void set_button_selected(int i_p){button_selected=i_p;}
	void set_button_mode(bool b_p){button_mode=b_p; button_selected=0;}
	void set_button_mode_pause(bool b_p){button_mode_pause=b_p;}
	void set_current_layer(std::string l_p){current_layer=l_p;}

	double get_left_stick_x(){return left_stick_x;}
	double get_left_stick_y(){return left_stick_y;}
	double get_right_stick_x(){return right_stick_x;}
	double get_right_stick_y(){return right_stick_y;}
	double get_left_trigger(){return left_trigger;}
	double get_right_trigger(){return right_trigger;}
	std::string get_current_layer(){return current_layer;}


};

unsigned int GAMEPAD_BIT_to_button_int(GAMEPAD_BIT);
GAMEPAD_BIT button_int_to_GAMEPAD_BIT(unsigned int);

#endif