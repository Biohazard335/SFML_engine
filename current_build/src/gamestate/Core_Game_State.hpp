#ifndef Core_game_state_HPP
#define Core_game_state_HPP

#include "Gamestate.hpp"
#include "../core_game/Tilemap.hpp"
#include <vector>
#include "../core_game/Path_Node.hpp"


/*
class Audiotest{
private:
	Animation animation;
	Audiokeyholder keyholder;

public:
	Audiotest(Animation a_p):keyholder("explosion",false){
		animation=a_p;
	}

	Animation& get_animation(){return animation;}
	Audiokeyholder& get_keyholder(){return keyholder;}

};*/


class Core_Game_State :public Gamestate{
private:
	Layer core_layer;
	Tilemap tilemap;

	Point start;
	Point end;


	bool step=false;

	std::vector<Point> path;

	sf::Sprite breach;
	Point breach_position;
	Point breach_coords;
	int path_num=0;

	//Text_Input_Box tib;
	//Animation explosion;
	//std::vector<Audiotest> explosions;
public:
	void update(Mousey&,Keyblade&,Gamepad&)override;
	void render(sf::RenderWindow& window)override;
	void load_sprites(Imagehandler& imagehandler)override;
	void execute_data(Data_Packet)override;
	void check_keyboard(Keyblade&);
	void check_gamepad(Gamepad&);

	void update_layer_resolutions()override;

	Core_Game_State(Imagehandler& imagehandler);
	~Core_Game_State(){}

};

#endif