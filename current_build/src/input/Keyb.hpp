#ifndef KEY_HPP
#define KEY_HPP
#include <SFML/Window/Keyboard.hpp>

class Keyb{
private:
	char key_c;
	sf::Keyboard::Key key_k;
	bool just_pressed=false;
	bool pressed=false;
	bool held=false;
public:
	Keyb(){}
	Keyb(char c_p, sf::Keyboard::Key k_p){key_c=c_p;key_k=k_p;}
	void update(bool b_p){
		pressed=b_p;
		just_pressed=b_p;
	}
	void update_jp(){
		just_pressed=false;
	}
	bool was_just_pressed(){return just_pressed;}
	bool is_pressed(){return pressed;}
	char get_key_c(){return key_c;}
	sf::Keyboard::Key get_key_k(){return key_k;}

};

#endif