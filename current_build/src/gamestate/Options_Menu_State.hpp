#ifndef OPTIONSMENUSTATE_HPP
#define OPTIONSMENUSTATE_HPP

#include "Gamestate.hpp"

class Options_Menu_State :public Gamestate{

private: 
	sf::Text fullscreen;
	sf::Text display_type;
	sf::Text resolution_text;
	int display_type_i=0;
	bool full=true;
	int current_res_index=0;
	bool display_type_i0=0;
	bool full0=true;
	int cri0=0;
	std::vector<Point> fullscreen_resolutions;
	std::vector<Point> windowed_resolutions;
	std::unique_ptr<Button> res_slider_swap;
	//std::unique_ptr<Button> display_type_swap;
	std::string previous_state;

	sf::Text res_error_text;
	Layer res_error_layer;

	//std::vector<std::unique_ptr<Button>> res_error_layer_buttons;
	Text_Button res_error_okay;
	sf::Sprite res_error_grey;


public:
	void update(Mousey&,Keyblade&,Gamepad&);
	void render(sf::RenderWindow& window);
	void load_sprites(Imagehandler& imagehandler);
	void execute_data(Data_Packet);
	void populate_fullscreen_resolutions();
	void populate_windowed_resolutions();

	void update_layer_resolutions()override{
		Gamestate::update_layer_resolutions();
		res_error_layer.resolve_new_resolution();
	}

	void resolution_error(bool);
	Options_Menu_State(Imagehandler& imagehandler);
	~Options_Menu_State()=default;

	void set_previous_state(std::string s_p){previous_state=s_p;}
};

#endif