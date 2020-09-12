#include "Imagehandler.hpp"
#include "../core_game/Tilemap.hpp"
#include <iostream>

Imagehandler::Imagehandler(){
	load();
}

void Imagehandler::load(){
	default_texture.loadFromFile("../assets/default_texture.png");
	default_texture.setSmooth(true);
	default_animation_texture.loadFromFile("../assets/default_animation.png");
	default_animation.load("../assets/default_animation.png",100,100,6,0,"explosion");
	loading.loadFromFile("../assets/Loading.png");

	sheet0.load("../assets/sprite_sheet_0.png",100,100,4,5,"sheet0");
	buttons0.load("../assets/main_menu/main_menu_buttons.png",150,40,3,4,"main_menu_buttons");
	buttons0.set_button_sheet(true);
	buttons1.load("../assets/pause_menu/pause_menu_buttons.png",150,40,3,5,"pause_menu_buttons");
	buttons1.set_button_sheet(true);

	pac_man.load("../assets/core_game/animations/pac-man.png",32,32,2,1,"pac-man");
	ghosts.load("../assets/core_game/animations/ghosts.png",32,32,2,6,"ghosts");
	pac_man_dies.load("../assets/core_game/animations/pac-man_dies.png",32,32,6,1,"pac-man_dies");

	breach.loadFromFile("../assets/core_game/System_Breach_assets/breach_new.png");
	breach.setSmooth(true);

	main_menu_background.loadFromFile("../assets/main_menu/Main_Menu.png");
	main_menu_background.setSmooth(true);
	pause_menu_background.loadFromFile("../assets/pause_menu/Pause_Menu.png");
	pause_menu_background.setSmooth(true);
	options_menu_background.loadFromFile("../assets/main_menu/Options_Menu.png");
	options_menu_background.setSmooth(true);
	core_game_background.loadFromFile("../assets/core_game/Core_Game.png");
	core_game_background.setSmooth(true);

	text_input_box.loadFromFile("../assets/gui/text_input_box.png");
	text_input_box.setSmooth(true);
	text_input_cursor.loadFromFile("../assets/gui/text_input_cursor.png");
	text_input_cursor.setSmooth(true);

	slider_sheet.load("../assets/gui/slider_sheet.png",-1,-1,-1,-1,"slider_sheet");

	text_buttons.load("../assets/gui/text_buttons.png",150,40,2,1,"text_buttons");
	checkbox.load("../assets/gui/checkbox.png",40,40,3,1,"checkbox");
	checkbox.set_button_sheet(true);

	if(!font.loadFromFile("../assets/font/System_Breach_wide.ttf")){
		std::cout<<"ERROR! failed to load font";
	}else{
		/*cout<<"!: l,   t,  w,  h,  a";
		for(int i=97;i<123;i++){
			sf::Glyph g=font.getGlyph(i,30,false,0);
			cout<<"\n"<<char(i)<<": "<<g.bounds.left<<", "<<g.bounds.top<<", "<<g.bounds.width<<", "<<g.bounds.height<<", "<<g.advance;
		}*/
	}

	Tilemap::add_tileset("../assets/core_game/tilesets/pac_man_tiles","pac_man_tiles");
	Tilemap::add_tileset("../assets/core_game/tilesets/path_tiles","path_tiles");
}

void Imagehandler::load_text_input_box(Text_Input_Box& tib){
	tib.set_font(font);
	tib.set_box_texture(text_input_box);
	tib.set_cursor_texture(text_input_cursor);
}



void Imagehandler::load_sprite(sf::Sprite& sprite, std::string name_p){
	if(name_p=="sprite 0"){
		sheet0.load_sprite(sprite,0,0);
	}else if(name_p=="main_menu_background"){
		sprite.setTexture(main_menu_background,true);
	}else if(name_p=="pause_menu_background"){
		sprite.setTexture(pause_menu_background,true);
	}else if(name_p=="core_game_background"){
		sprite.setTexture(core_game_background,true);
	}else if(name_p=="options_menu_background"){
		sprite.setTexture(options_menu_background,true);
	}else if(name_p=="breach"){
		sprite.setTexture(breach,true);
	}
	else{
		std::cout<<"\nERROR: sprite not found: "<<name_p<<std::endl;
	}
}

void Imagehandler::load_animation(Animation& animation, std::string name_p){
	if(name_p=="explosion"){
		default_animation.load_animation(animation,0);
	}else if(name_p=="pac-man"){
		pac_man.load_animation(animation,0);
	}else if(name_p=="pac-man_dies"){
		pac_man_dies.load_animation(animation,0);
		animation.set_looping(false);
	}else if(name_p=="ghost_red"){
		ghosts.load_animation(animation,0);
	}else if(name_p=="ghost_green"){
		ghosts.load_animation(animation,1);
	}else if(name_p=="ghost_orange"){
		ghosts.load_animation(animation,2);
	}else if(name_p=="ghost_purple"){
		ghosts.load_animation(animation,3);
	}else if(name_p=="ghost_afraid"){
		ghosts.load_animation(animation,4);
	}else if(name_p=="ghost_dead"){
		ghosts.load_animation(animation,5);
	}else{
		std::cout<<"\nERROR: animation not found: "<<name_p<<"\n";
	}
}

void Imagehandler::load_sprite_button(Sprite_Button& button){
	if(button.get_sheet_name()=="main_menu_buttons"){
		button.load_sprites(buttons0);
	}else if(button.get_sheet_name()=="pause_menu_buttons"){
		button.load_sprites(buttons1);
	}else if(button.get_sheet_name()=="checkbox"){
		button.load_sprites(checkbox);
	}else{
		std::cout<<"\nERROR: button_sheet not found: "<<button.get_sheet_name()<<"\n";
	}
}

void Imagehandler::load_text_button(Text_Button& button){
	button.set_font(font);
	button.load_sprites(text_buttons);
}
void Imagehandler::load_slider(Slider& button){
	button.set_font(font);
	button.load_sprites(slider_sheet);
}


void Imagehandler::load_MEBL(MEBL& mebl){
	for(unsigned int i=0;i<mebl.get_list().size();i++){
		load_button(mebl.get_list().at(i).get());
	}
}

void Imagehandler::load_button(Button* button){
	if(button->get_type()==SPRITE_BUTTON){
		load_sprite_button(*static_cast<Sprite_Button*>(button));
	}else if(button->get_type()==TEXT_BUTTON){
		load_text_button(*static_cast<Text_Button*>(button));
	}else if(button->get_type()==M_E_B_L){
		load_MEBL(*static_cast<MEBL*>(button));
	}else if(button->get_type()==SLIDER){
		load_slider(*static_cast<Slider*>(button));
	}else{
		std::cout<<"ERROR: attempt to load invalid button type for: "<<button->get_data().get_data_type()<<std::endl;
	}
}

void Imagehandler::load_sf_text(sf::Text& text){
	text.setFont(font);
}