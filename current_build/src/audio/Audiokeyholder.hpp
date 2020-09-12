#ifndef AUDIOKEYHOLDER_HPP
#define AUDIOKEYHOLDER_HPP

#include <memory>
#include <string>
#include "Audiokeyhandler.hpp"
#include <iostream>

class Audiokeyholder{
	private:
		std::shared_ptr<int> key=std::make_shared<int>((-1));
		std::string name;
		bool looping=false;
	public:
		Audiokeyholder(){};
		Audiokeyholder(std::string name_p, bool l_p){
			name=name_p;
			looping=l_p;
		}
		std::shared_ptr<int> get_key(){return key;}
		int get_key_contents(){return *key;}
		void set_name(std::string name_p){name=name_p;}
		void set_looping(bool l_p){looping=l_p;}

		std::string get_name(){return name;}
		bool is_looping(){return looping;}
};


#endif