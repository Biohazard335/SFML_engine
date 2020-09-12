#include "Animation.hpp"

void Animation::load(sf::Texture& texture, int width_p, int height_p, int sprites_length_p, int rect_y_p){
	frame_width=width_p;
	frame_height=height_p;
	sprites_length=sprites_length_p;
	rect_y=rect_y_p;


	for(int i=0;i<sprites_length;i++){
		sprites.push_back(sf::Sprite());
		sprites[i].setTexture(texture,false);
		sprites[i].setTextureRect(sf::IntRect((i*frame_width),rect_y,frame_width,frame_height));
		sprites[i].setOrigin(frame_width/2,frame_height/2);
	}

}

void Animation::set_position(int x_p, int y_p){
	for(int i=0;i<sprites_length;i++){
		sprites[i].setPosition(x_p,y_p);
	}
}
void Animation::move(int x_p, int y_p){
	for(int i=0;i<sprites_length;i++){
		sprites[i].move(x_p,y_p);
	}
}

void Animation::move(Point p_p){
	for(int i=0;i<sprites_length;i++){
		sprites[i].move(p_p.get_x(),p_p.get_y());
	}
}
sf::Sprite Animation::animate(){
	if(!finished){
		if(fps_timer==fps_timer_max){
			current_frame++;
			fps_timer=0;
		}else{
			fps_timer++;
		}

		if(current_frame==sprites_length-1){
			if(!loop){
				finished=true;
			}
		}
		if(current_frame>=sprites_length){
			current_frame=0;
		}
		return sprites[current_frame];
	}else{
		return sf::Sprite();
	}

}