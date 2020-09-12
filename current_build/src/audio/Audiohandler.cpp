#include "Audiohandler.hpp"
#include "Audiokeyhandler.hpp" 
#include <iterator>
#include <iostream>



void Audiohandler::load(){
	boom.loadFromFile("../assets/explosion.wav");
	default_sound.loadFromFile("../assets/explosion.wav");
	background_music.openFromFile("../assets/music/Ethans_song.wav");
	//background_music.play();
}
void Audiohandler::load_sound(sf::Sound& s, std::string name_p){
	if(name_p=="explosion"){
		s.setBuffer(boom);
	}else{
		s.setBuffer(default_sound);
		std::cout<<"ERROR: invalid sound name: "<<name_p<<std::endl;
	}

}
void Audiohandler::add_sfx(int key_p,std::string name_p,bool loop_p){
	if(key_p>=0){
		sf::Sound s;
		load_sound(s,name_p);
		s.setLoop(loop_p);
		sfx_map.insert(std::pair<int, sf::Sound>(key_p,s));
		sfx_map.at(key_p).play();
	}else{
		std::cout<<"ERROR: invalid key for sound: "<<name_p<<std::endl;
	}
}
void Audiohandler::stop_sfx(int key_p){
	sfx_map.at(key_p).stop();
}
void Audiohandler::pause_sfx(int key_p){
	sfx_map.at(key_p).pause();
}
void Audiohandler::update_sfx(){
	auto i=sfx_map.begin();
	while(i!=sfx_map.end()){
		if(i->second.getStatus()==sf::SoundSource::Stopped){
			Audiokeyhandler::free(i->first);
			i=sfx_map.erase(i);
		}else if(volume_update){
			i->second.setVolume(sfx_volume*global_volume_scale);
		}else {
			i++;
		}
	}
	volume_update=false;
}		


void Audiohandler::set_background_music(std::string name_p){
	if(name_p=="ethan"){
		background_music.openFromFile("../assets/music/Ethans_song.wav");
	}else{
		std::cout<<"ERROR: invalid music name: "<<name_p<<std::endl;
	}
}