#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "../gui/Button.hpp"
#include "../image/Imagehandler.hpp"
#include "../input/Keyblade.hpp"
#include "../input/Gamepad.hpp"
#include "../gui/Text_Input_Box.hpp"
#include "../audio/Audiokeyholder.hpp"
#include "../communal/Data_Packet.hpp"
#include "../communal/Duration_Check.hpp"
#include "../image/Layer.hpp"
#include <memory>


class Gamestate{

protected:
	std::string state_name="invalid";
	sf::Sprite background;
	sf::Text title;
	std::vector<std::unique_ptr<Button>> gui_layer_buttons;
	std::string mouse_state;

	bool ignore_user_input=false;

	std::vector<Data_Packet> send_data;

	Layer gui_layer;
	Layer background_layer;

	int timer;
	
public:
	virtual void execute_data(Data_Packet)=0;
	virtual void update(Mousey&, Keyblade&, Gamepad&);
	virtual void load_sprites(Imagehandler& imagehandler)=0;
	virtual void render(sf::RenderWindow& window);
	virtual void update_layer_resolutions();

	void update_gui_layer(Mousey&, Keyblade&, Gamepad&);
	void render_gui_layer(sf::RenderWindow& window);
	void render_background_layer(sf::RenderWindow& window);

	void check_buttons(Mousey& mouse, std::vector<std::unique_ptr<Button>>& buttons);
	void check_buttons(Gamepad& gamepad, std::vector<std::unique_ptr<Button>>& buttons);
	
	Data_Packet get_send_data();
	bool has_send_data(){return(send_data.size()>0);}	

	Gamestate();
	void request_sound(Audiokeyholder&);

	std::string get_mouse_state(){return mouse_state;}
	void set_mouse_state(std::string state_p){mouse_state=state_p;}
	void run_timer(){if(timer<60)timer+=1;else timer =0;}
	std::string get_state_name(){return state_name;}
};

#endif