#include "Audiokeyholder.hpp"
#include <iostream>


const int Audiokeyhandler::keys_length;
std::shared_ptr<int> Audiokeyhandler::keys[kl];

Audiokeyhandler::Audiokeyhandler(){	
	for(int i=0;i<keys_length;i++){
		keys[i]=nullptr;
	}
}
void Audiokeyhandler::give_new_key(Audiokeyholder& holder){
	for(int i=0;i<keys_length;i++){
		if(keys[i]==nullptr){
			*holder.get_key()=i;
			keys[i]=holder.get_key();
			return;
		}
	}
	*holder.get_key()=-1;
}
bool Audiokeyhandler::is_used(int i_p){
	return !(keys[i_p]==nullptr);
}
void Audiokeyhandler::free(int i_p){
	*keys[i_p]=-1;
	keys[i_p]=nullptr;
}