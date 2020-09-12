#include "Text_Input_Box.hpp"


Text_Input_Box::Text_Input_Box(){
}

void Text_Input_Box::create(int x_p, int y_p){
	x=x_p;
	y=y_p;
	display_text.setCharacterSize(char_size);
	display_text.setFillColor(sf::Color::Red);
	display_text.setOutlineColor(sf::Color::Black);
	//display_text.setOutlineThickness(3.0f);
	box.setPosition(x,y);
	cursor.setPosition(x+4,y+4);
	cursor.setColor(sf::Color::Transparent);
	display_text.setPosition(x+4,y-1);
}

void Text_Input_Box::draw(sf::RenderWindow& window){
	window.draw(box);
	window.draw(display_text);
	window.draw(cursor);
}

void Text_Input_Box::set_font(sf::Font& font){
	display_text.setFont(font);
}
void Text_Input_Box::set_box_texture(sf::Texture& texture){
	box.setTexture(texture);
}
void Text_Input_Box::set_cursor_texture(sf::Texture& texture){
	cursor.setTexture(texture);
}

void Text_Input_Box::update(Mousey& mouse,Keyblade& keyboard){
	if(active){
		if(keyboard.get_key('B').is_pressed()){
			if(input.length()>=1){
				if(bs_wait==0){
					input.pop_back();
					cursor_x-=1;
					bs_wait=7;
				}else{
					bs_wait--;
				}
			}
		}
		if(keyboard.get_key('\n').was_just_pressed()){
			output=input;
			input="";
			cursor_x=0;
		}
		for(int  i=0;i<keyboard.get_num_keys();i++){
			if(keyboard.get_index(i).was_just_pressed()){
				char c=keyboard.get_index(i).get_key_c();
				if(c=='B'){
					bs_wait=0;
				}else if(c!='E' && c!='\n'){
					if(input.length()<max_chars_x){
						input.push_back(c);
						cursor_x+=1;
					}
				}
			}
		}
		display_text.setString(input);
		cursor_blink++;
		if(cursor_blink==20 || input.length()==max_chars_x){
			cursor.setColor(sf::Color::Transparent);
		}else if(cursor_blink>40){
			cursor.setColor(sf::Color::White);
			cursor_blink=0;
		}
		cursor.setPosition(x+display_text.getLocalBounds().width+((cursor_x>0)?14:4),y+4);
	}
	if(mouse.is_clicked()){
		if(mouse.get_layer_x()>x && mouse.get_layer_x()<x+width && mouse.get_layer_y()>y && mouse.get_layer_y()<y+height){
			active=true;
			cursor.setColor(sf::Color::White);
		}else{
			active=false;
			cursor.setColor(sf::Color::Transparent);
		}
	}
}