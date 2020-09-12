#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "Gamestate.hpp"

class Main_Menu_State :public Gamestate{
public:
	void update(Mousey&,Keyblade&,Gamepad&);
	void render(sf::RenderWindow& window);
	void load_sprites(Imagehandler& imagehandler);
	void execute_data(Data_Packet);
	void check_keyboard(Keyblade&);
	void check_gamepad(Gamepad&);
	Main_Menu_State(Imagehandler& imagehandler);
	~Main_Menu_State()=default;
};

#endif