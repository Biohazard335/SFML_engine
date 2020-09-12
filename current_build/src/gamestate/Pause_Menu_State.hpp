#ifndef PAUSEMENUSTATE_HPP
#define PAUSEMENUSTATE_HPP

#include "Gamestate.hpp"

class Pause_Menu_State :public Gamestate{
public:
	void update(Mousey&,Keyblade&,Gamepad&);
	void render(sf::RenderWindow& window);
	void load_sprites(Imagehandler& imagehandler);
	void execute_data(Data_Packet);
	Pause_Menu_State(Imagehandler& imagehandler);
	~Pause_Menu_State()=default;
};

#endif