#include "Slider.hpp"
#include <cstdlib>

Slider::Slider(std::string name_p, double x_p, double y_p, Data_Packet data_p, int l_p,int u_p,int d_p, int r_p, int options_p){
	create(name_p,x_p,y_p,subdivisions,min,max,data_p,l_p,u_p,d_p,r_p,options_p);
}
Slider::Slider(std::string name_p, double x_p, double y_p, int sub_p, Data_Packet data_p, int l_p,int u_p,int d_p, int r_p, int options_p){
	create(name_p,x_p,y_p,sub_p,min,max,data_p,l_p,u_p,d_p,r_p,options_p);
}
Slider::Slider(std::string name_p, double x_p, double y_p, double min_p, double max_p,Data_Packet data_p, int l_p,int u_p,int d_p, int r_p, int options_p) {
	create(name_p,x_p,y_p,subdivisions,min_p, max_p,data_p,l_p,u_p,d_p,r_p,options_p);
}
Slider::Slider(std::string name_p, double x_p, double y_p, int sub_p, double min_p, double max_p,Data_Packet data_p, int l_p,int u_p,int d_p, int r_p, int options_p){
	create(name_p,x_p,y_p,sub_p,min_p, max_p,data_p,l_p,u_p,d_p,r_p,options_p);
}


void Slider::create(std::string name_p, double x_p, double y_p, int sub_p, double min_p, double max_p, Data_Packet data_p, int l_p,int u_p,int d_p, int r_p, int options_p){
	button_up=u_p;
	button_down=d_p;
	button_left=l_p;
	button_right=r_p;
	name=name_p;
	origin_x=x_p;
	origin_y=y_p;
	subdivisions=sub_p;
	sub_distance=bar_width/(subdivisions+1);
	min=min_p;
	max=max_p;
	value=max;
	data=data_p;
	interaction_level=data.get_interaction_level();
	width=10;
	height=20;
	togglable=true;
	if(subdivisions>0){
		discrete=true;
		sub_increment=(max-min)/(subdivisions+1);
		x=origin_x+(((subdivisions+1)*sub_increment)/(max-min))*bar_width-(width/2);
	}else{
		x=origin_x+bar_width-(width/2);
	}

	show_name=!(options_p & NO_NAME);
	show_value=!(options_p & NO_VALUE);
	align_name=!(options_p & ALIGN_BAR);
	abs_name_dist=(options_p & ABS_NAME_DIST);

	y=origin_y-((height-bar_height)/2);
	type=SLIDER;

	data=Data_Packet(data.get_data_type(),data.get_interaction_level(),{(int)value});
}

void Slider::set_font(sf::Font& font){
	display_name.setFont(font);
	display_value.setFont(font);

	display_name.setString(name);
	display_name.setFillColor(font_color);
	display_name.setOutlineColor(sf::Color::Black);
	display_name.setOutlineThickness(1.0f);
	display_name.setCharacterSize(23);

	if(align_name){
		name_origin=origin_x;
		origin_x=name_origin+(display_name.getLocalBounds().width+display_name_distance);
		if(discrete){
			x=origin_x+(((subdivisions+1)*sub_increment)/(max-min))*bar_width-(width/2);
		}else{
			x=origin_x+bar_width-(width/2);
		}
	}else if(abs_name_dist){
		name_origin=origin_x-absolute_name_distance;
	}else{
		name_origin=origin_x-(display_name.getLocalBounds().width+display_name_distance);
	}

	display_name.setPosition(name_origin,origin_y-11);

	display_value.setString(std::to_string((int)value));
	display_value.setFillColor(font_color);
	display_value.setOutlineColor(sf::Color::Black);
	display_value.setOutlineThickness(1.0f);
	display_value.setCharacterSize(23);
	display_value.setPosition(origin_x+bar_width+display_value_distance,origin_y-11);
}


void Slider::draw(sf::RenderWindow& window){
	window.draw(bar_s);
	if(discrete){
		for(int i=0;i<subdivisions;i++){
			subdivision_s.setPosition(origin_x+((i+1)*sub_distance)-(sub_s_width/2),origin_y-((sub_s_height-bar_height)/2));
			window.draw(subdivision_s);
		}
	}
	if(highlighted){
		window.draw(highlighted_s);
	}else{
		window.draw(cursor_s);
	}
	if(show_name){
		window.draw(display_name);
	}
	if(show_value){
		window.draw(display_value);
	}


}
void Slider::load_sprites(Sprite_Sheet& sheet){
	bar_s.setTexture(sheet.get_texture());
	subdivision_s.setTexture(sheet.get_texture());
	cursor_s.setTexture(sheet.get_texture());
	highlighted_s.setTexture(sheet.get_texture());

	bar_s.setTextureRect(sf::IntRect(0,0,bar_width,bar_height));
	subdivision_s.setTextureRect(sf::IntRect(24,20,sub_s_width,sub_s_height));
	cursor_s.setTextureRect(sf::IntRect(0,20,width,height));
	highlighted_s.setTextureRect(sf::IntRect(12,20,width,height));

	bar_s.setPosition(origin_x,origin_y);

	cursor_s.setPosition(x,y);
	highlighted_s.setPosition(x,y);
}
bool Slider::check_clicked(Mousey& mouse){
	if(!on){
		if(is_active() &&mouse.get_layer_x()>x &&mouse.get_layer_x()<x+width &&mouse.get_layer_y()>y &&mouse.get_layer_y()<y+height && mouse.is_clicked()){
			on=true;
			return true;
		}else{
			return false;
		}
	}else{
		if(!mouse.is_pressed()){
			on=false;
			cursor_s.setPosition(x,y);
			return false;
		}else{
			val_x=mouse.get_layer_x();
			value=(((val_x-origin_x)/(bar_width))*(max-min))+min;
			if(value>max){
				value=max;
				val_x=origin_x+bar_width;
			}else if(value<min){
				value=min;
				val_x=origin_x;
			}

			if(discrete){
				int min_distance=bar_width;
				int index=0;
				for(int i=0;i<=subdivisions+1;i++){
					int check=std::abs((int)(val_x-(origin_x+sub_distance*i)));
					if(min_distance>check){
						min_distance=check;
						index=i;
					}
				}
				val_x=origin_x+((index*sub_increment)/(max-min))*bar_width;
				value=sub_increment*index+min;
			}
			x=val_x-(width/2);
			highlighted_s.setPosition(x,y);
			display_value.setString(std::to_string((int)value));
			data=Data_Packet(data.get_data_type(),data.get_interaction_level(),{(int)value});
			interaction_level=data.get_interaction_level();
			return true;
		}
	}
}

bool Slider::check_highlighted(Mousey& mouse){
	if(!on){
		if(is_active() &&mouse.get_layer_x()>x &&mouse.get_layer_x()<x+width &&mouse.get_layer_y()>y &&mouse.get_layer_y()<y+height){
			highlighted=true;
			return true;
		}else{
			highlighted=false;
			return false;
		}
	}else{
		highlighted=true;
		return true;
	}
}


bool Slider::pushed_by_gamepad(Gamepad& gamepad){
	using_gamepad=!using_gamepad;
	discrete_gamepad_timer=0;
	if(!using_gamepad){
		cursor_s.setPosition(x,y);
	}
	return !using_gamepad;
}

void Slider::update(Gamepad& gamepad){
	if(discrete){
		if(discrete_gamepad_timer!=0){
			discrete_gamepad_timer--;
		}else{
			if(gamepad.get_left_stick_x()>0){
				value+=sub_increment;
			}else if(gamepad.get_left_stick_x()<0){
				value-=sub_increment;
			}
			discrete_gamepad_timer=10;
		}
		if(gamepad.get_left_stick_x()==0){
			discrete_gamepad_timer=0;
		}
	}else{
		//std::cout<<(max-min)<<"*"<<gamepad.get_left_stick_x()<<"="<<((max-min)*gamepad.get_left_stick_x())<<"/50000="<<(((max-min)*gamepad.get_left_stick_x())/5000.0)<<std::endl;
		value+=((max-min)*gamepad.get_left_stick_x())/5000.0;
	}

	if(value>max){
		value=max;
	}else if(value<min){
		value=min;
	}

	x=((value/(max-min))*bar_width)-(width/2)+origin_x;
	highlighted_s.setPosition(x,y);
	display_value.setString(std::to_string((int)value));
	data=Data_Packet(data.get_data_type(),data.get_interaction_level(),{(int)value});
	interaction_level=data.get_interaction_level();
}


double Slider::manually_set_value(double v_p){
	value=v_p;

	x=((value/(max-min))*bar_width)-(width/2)+origin_x;
	highlighted_s.setPosition(x,y);
	cursor_s.setPosition(x,y);
}