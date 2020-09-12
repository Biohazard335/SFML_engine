#include "Text_Button.hpp"


Text_Button::Text_Button(std::string name_p, int x_p, int y_p, Data_Packet data_p, int l_p,int u_p,int d_p, int r_p){
	button_up=u_p;
	button_down=d_p;
	button_left=l_p;
	button_right=r_p;
	name=name_p;
	x=x_p;
	y=y_p;
	data=data_p;
	interaction_level=data.get_interaction_level();

	display_text.setCharacterSize(23);
	display_text.setFillColor(text_off_color);
	display_text.setOutlineColor(sf::Color::Black);
	display_text.setOutlineThickness(1.0f);
	display_text.setString(name);

	s_off.setPosition(x,y);
	s_highlighted.setPosition(x,y);
	type=TEXT_BUTTON;
}

void Text_Button::draw(sf::RenderWindow& window){
	if(visible){
		if(on){
			display_text.setFillColor(text_on_color);
		}else{
			if(highlighted){
				display_text.setFillColor(text_highlighted_color);
			}else{
				display_text.setFillColor(text_off_color);
			}
		}
		if(highlighted){
			window.draw(s_highlighted);
		}else{
			window.draw(s_off);
		}
		window.draw(display_text);
	}
}
void Text_Button::load_sprites(Sprite_Sheet& sheet){

	width=sheet.get_sprite_width();
	height=sheet.get_sprite_height();
	display_text.setPosition(x+(width/2)-(int)(display_text.getLocalBounds().width/2)-2,y+(height/2)-(int)(display_text.getLocalBounds().height/2)-6);

	s_off.setTexture(sheet.get_texture());
	s_off.setTextureRect(sf::IntRect(0,0,width,height));

	s_highlighted.setTexture(sheet.get_texture());
	s_highlighted.setTextureRect(sf::IntRect(width,0,width,height));
}