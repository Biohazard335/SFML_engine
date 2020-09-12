#ifndef AUDIOHANDLER_HPP
#define AUDIOHANDLER_HPP

#include <SFML/Audio.hpp>
#include <map>
#include <string>

class Audiohandler{
private:
	float global_volume_scale=1.0f;
	float music_volume=100.0f;
	float sfx_volume=100.0f;
	bool volume_update=false;
	sf::Music background_music;
	sf::SoundBuffer boom;
	sf::SoundBuffer default_sound;

	std::map<int,sf::Sound> sfx_map;
public:
	Audiohandler(){load();};
	void load();
	void load_sound(sf::Sound&, std::string);
	void add_sfx(int,std::string,bool);
	void stop_sfx(int);
	void pause_sfx(int);
	void update_sfx();
	void set_background_music(std::string);
};

#endif