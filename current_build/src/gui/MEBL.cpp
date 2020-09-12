#include "MEBL.hpp"
#include "Sprite_Button.hpp"
#include "Text_Button.hpp"


MEBL::MEBL(int gbn_p,std::initializer_list<std::shared_ptr<Button>> list_p, int l_p,int u_p,int d_p, int r_p){
	gamestate_buttons_number=gbn_p;
	button_up=u_p;
	button_down=d_p;
	button_left=l_p;
	button_right=r_p;
	for(auto it=list_p.begin(); it<list_p.end();it++){
		if(it->get()->get_type()==SPRITE_BUTTON){
			list.push_back(std::make_unique<Sprite_Button>(*static_cast<Sprite_Button*>(it->get())));
		}else if(it->get()->get_type()==TEXT_BUTTON){
			list.push_back(std::make_unique<Text_Button>(*static_cast<Text_Button*>(it->get())));
		}else{
			std::cout<<"Invlaid button type in MEBL initialization!"<<std::endl;
		}
	}
	for(unsigned int i=0;i<list_p.size();i++){
		list.at(i).get()->set_togglable(true);
	}
	type=M_E_B_L;
}
void MEBL::draw(sf::RenderWindow& window){
	for(unsigned int i=0;i<list.size();i++){
		list.at(i)->draw(window);
	}
}
bool MEBL::check_clicked(Mousey& mouse){
	for(unsigned int i=0;i<list.size();i++){
		if(list.at(i)->check_clicked(mouse)){
			if(list.at(i)->is_on()){
				for(unsigned int j=0; j<list.size();j++){
					if(j!=i){
						list.at(j)->manually_set_on(false);
					}
				}
			}
			data=list.at(i)->get_data();
			interaction_level=data.get_interaction_level();
			return true;
		}
	}
	return false;
}
bool MEBL::check_highlighted(Mousey& mouse){
	bool check=false;
	for(unsigned int i=0;i<list.size();i++){
		if(list.at(i)->check_highlighted(mouse)){
			check=true;
			selected=i;
		}
	}
	return check;
}

void MEBL::manually_set_on(bool b_p){
	list.at(selected)->manually_set_on(b_p);
}
void MEBL::manually_set_highlighted(bool b_p){
	list.at(selected)->manually_set_highlighted(b_p);
}


int MEBL::get_button_left(){
	int temp=get_button_all(0);
	if(temp==-1){
		return button_left;
	} 
	return gamestate_buttons_number;
}
int MEBL::get_button_up(){
	int temp=get_button_all(1);
	if(temp==-1){
		return button_up;
	} 
	return gamestate_buttons_number;
}
int MEBL::get_button_down(){
	int temp=get_button_all(2);
	if(temp==-1){
		return button_down;
	} 
	return gamestate_buttons_number;
}
int MEBL::get_button_right(){
	int temp=get_button_all(3);
	if(temp==-1){
		return button_right;
	} 
	return gamestate_buttons_number;
}

int MEBL::get_button_all(int i_p){
	int temp=-1;
	if(i_p==0){
		temp=list.at(selected)->get_button_left();
	}else if(i_p==1){
		temp=list.at(selected)->get_button_up();
	}else if(i_p==2){
		temp=list.at(selected)->get_button_down();
	}else if(i_p==3){
		temp=list.at(selected)->get_button_right();
	}

	if(temp!=-1){
		list.at(selected)->manually_set_highlighted(false);
		selected=temp;
		data=list.at(selected)->get_data();
		interaction_level=data.get_interaction_level();
		list.at(selected)->manually_set_highlighted(true);
		return gamestate_buttons_number;
	}else{
		list.at(selected)->manually_set_highlighted(false);
		selected=0;
		data=list.at(0)->get_data();
		return -1;
	}
	return -1;
}

bool MEBL::pushed_by_gamepad(Gamepad& gamepad){
	list.at(selected)->toggle_on();
	if(list.at(selected)->is_on()){
		for(unsigned int j=0; j<list.size();j++){
			if(j!=(unsigned int)selected){
				list.at(j)->manually_set_on(false);
			}
		}
	}
	data=list.at(selected)->get_data();
	interaction_level=data.get_interaction_level();
	return true;
}