#ifndef DATA_PACKET_HPP
#define DATA_PACKET_HPP

#include <vector>
#include <string>
#include <iostream>
#include <initializer_list>

enum INTERACTION_LEVEL{
	LOCAL=0,
	MANAGER=1,
	DRIVER=2
};

class Data_Packet{
public:
	Data_Packet(std::string data_type_p,INTERACTION_LEVEL i_p):data_type(data_type_p),interaction_level(i_p){}
	Data_Packet(){}
	Data_Packet(std::string data_type_p, INTERACTION_LEVEL i_p,std::initializer_list<int> ints_p):data_type(data_type_p),interaction_level(i_p){ints= ints_p;}
	Data_Packet(std::string data_type_p, INTERACTION_LEVEL i_p,std::initializer_list<std::string> strings_p):data_type(data_type_p),interaction_level(i_p){strings=strings_p;}
	Data_Packet(std::string data_type_p, INTERACTION_LEVEL i_p,std::initializer_list<int> ints_p, std::initializer_list<std::string> strings_p):
		data_type(data_type_p),interaction_level(i_p){ints=ints_p;strings=strings_p;}

	std::string get_data_type(){return data_type;}
	INTERACTION_LEVEL get_interaction_level(){return interaction_level;}
	std::vector<std::string> get_strings(){return strings;}
	std::vector<int> get_ints(){return ints;}
	bool check_valid(unsigned int strings_i, unsigned int ints_i){
		bool return_b=true;
		if(strings.size()!=strings_i){
			std::cout<<"\nERROR:invalid strings size of data packet: "<<data_type<<"\n";
			return_b= false;
		}
		if(ints.size()!=ints_i){
			std::cout<<"\nERROR:invalid ints size of data packet: "<<data_type<<"\n";
			return_b= false;
		}
		return return_b;
	}

	void add_string(std::string s_p){strings.push_back(s_p);}
	void add_int(int i_p){ints.push_back(i_p);}

private:
	std::string data_type="empty";
	INTERACTION_LEVEL interaction_level=LOCAL;

	std::vector<std::string> strings;
	std::vector<int> ints;


};

#endif