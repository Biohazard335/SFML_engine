#ifndef KEYBLADE_HPP
#define KEYBLADE_HPP
#include "Keyb.hpp"

#include <SFML/Window/Event.hpp>


class Keyblade{
private:
	Keyb* keys;
	int num_keys=40;


public:
	Keyblade();
	~Keyblade(){delete[] keys;}

	Keyb get_key(char c_p);
	Keyb get_index(int i_p);
	int get_num_keys(){return num_keys;}
	void event_update(sf::Event& event);
	void update_jps();


};

#endif