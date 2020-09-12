#include "Sprite_Button.hpp"


Sprite_Button::Sprite_Button(std::string name_p,std::string sheet_p, int s_n_p, int x_p, int y_p, Data_Packet data_p, int l_p,int u_p,int d_p, int r_p){
	button_up=u_p;
	button_down=d_p;
	button_left=l_p;
	button_right=r_p;
	name=name_p;
	sheet_name=sheet_p;
	sheet_number=s_n_p;
	x=x_p;
	y=y_p;
	data=data_p;
	interaction_level=data.get_interaction_level();
	s_off.setPosition(x,y);
	s_on.setPosition(x,y);
	s_highlighted.setPosition(x,y);
	type=SPRITE_BUTTON;
}


void Sprite_Button::load_sprites(Sprite_Sheet& sheet){
	if(sheet.is_button_sheet()){
		width=sheet.get_sprite_width();
		height=sheet.get_sprite_height();

		s_off.setTexture(sheet.get_texture());
		s_off.setTextureRect(sf::IntRect(0,sheet_number*height,width,height));

		s_highlighted.setTexture(sheet.get_texture());
		s_highlighted.setTextureRect(sf::IntRect(width,sheet_number*height,width,height));

		s_on.setTexture(sheet.get_texture());
		s_on.setTextureRect(sf::IntRect(width*2,sheet_number*height,width,height));
	}else{
		std::cout<<"\nerror loading buttons: sprite sheet not button sheet\n";
	}
}


void Sprite_Button::draw(sf::RenderWindow& window){
	if(visible){
		if(!on && !highlighted){
			window.draw(s_off);
		}else if(highlighted /*&& !on*/){
			window.draw(s_highlighted);
		}else{
			window.draw(s_on);
		}
	}
}