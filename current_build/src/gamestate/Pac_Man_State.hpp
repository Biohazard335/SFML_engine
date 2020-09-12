#ifndef Pac_Man_State_HPP
#define Pac_Man_State_HPP

#include "Gamestate.hpp"
#include "../core_game/Tile.hpp"
#include "../core_game/Hitbox.hpp"
#include "../core_game/Ghost.hpp"
#include "../core_game/Point.hpp"
#include "../core_game/Pac_man.hpp"
#include "../core_game/Tilemap.hpp"

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

};
*/

class Pac_Man_State :public Gamestate{
private:
	Layer core_layer;

	//Text_Input_Box tib;
	//Animation explosion;
	//std::vector<Audiotest> explosions;
	std::vector<Ghost> ghosts;
	std::vector<Audiokeyholder> explosion_sounds;
	Point ghost_spawn;
	Point pac_spawn;
	Point warp_1;
	Point warp_2;

	Pac_man pac_man;
	Tilemap tilemap;
public:
	void update(Mousey&,Keyblade&,Gamepad&)override;
	void render(sf::RenderWindow& window)override;
	void load_sprites(Imagehandler& imagehandler)override;
	void execute_data(Data_Packet)override;
	void check_keyboard(Keyblade&);
	void check_gamepad(Gamepad&);

	void update_layer_resolutions()override;

	Pac_Man_State(Imagehandler& imagehandler);
	~Pac_Man_State(){}

};

#endif