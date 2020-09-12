#include "Gamepad.hpp"
#include <iostream>

Gamepad::Gamepad(){

}

void Gamepad::event_update(sf::Event& event){
	if(event.type==sf::Event::JoystickButtonPressed){
		//std::cout<<"Button "<<event.joystickButton.button<<" pressed"<<std::endl;
		update_button(button_int_to_GAMEPAD_BIT(event.joystickButton.button),true);
	}else if(event.type==sf::Event::JoystickButtonReleased){
		update_button(button_int_to_GAMEPAD_BIT(event.joystickButton.button),false);
		//std::cout<<"Button "<<event.joystickButton.button<<" released"<<std::endl;
	}else if(event.type==sf::Event::JoystickConnected){
		connected=true;
		//std::cout<<"Joystick "<<event.joystickConnect.joystickId<<" connected!"<<std::endl;
	}else if(event.type==sf::Event::JoystickDisconnected){
		connected=false;
		//std::cout<<"Joystick "<<event.joystickConnect.joystickId<<" disconnected!"<<std::endl;
	}else if(event.type==sf::Event::JoystickMoved){
		float temp=event.joystickMove.position;
		if(!(temp>dead_zone || temp<-dead_zone)){
			temp=0;
		}
		//(std::cout<<"Axis "<<event.joystickMove.axis<<" moved to "<<event.joystickMove.position<<std::endl);
		switch(event.joystickMove.axis){
			case 0: left_stick_x=temp; break;
			case 1: left_stick_y=temp; break;
			case 2: left_trigger=temp; break;
			case 3: right_trigger=temp; break;
			case 4: right_stick_x=temp; break;
			case 5: right_stick_y=temp; break;
			case 6: {
				 if((int)temp<0){
					buttons_just_pressed |=GAMEPAD_LEFT;
				}else{
					buttons_just_pressed |=GAMEPAD_RIGHT;
				}
				break;
			}
			case 7: {
				if((int)temp<0){
					buttons_just_pressed |=GAMEPAD_UP;
				}else{
					buttons_just_pressed |=GAMEPAD_DOWN;
				}
				break;
			}
		}
	}
}

void Gamepad::update_button(GAMEPAD_BIT gpb_p, bool pressed_p){
	if(pressed_p){
		if(!(buttons_pressed & gpb_p)){
			buttons_just_pressed |=gpb_p;
			buttons_pressed|=gpb_p;
		}
	}else{
		buttons_pressed ^=gpb_p;
	}
}
void Gamepad::update_jps(){
	buttons_just_pressed=0;
}

bool Gamepad::is_pressed(GAMEPAD_BIT gpb_p){
	return (buttons_pressed & gpb_p);

}
bool Gamepad::was_just_pressed(GAMEPAD_BIT gpb_p){
	return (buttons_just_pressed & gpb_p);
}
bool Gamepad::is_pressed(unsigned int i_p){
	return (buttons_pressed & button_int_to_GAMEPAD_BIT(i_p));

}
bool Gamepad::was_just_pressed(unsigned int i_p){
	return (buttons_just_pressed & button_int_to_GAMEPAD_BIT(i_p));
}


unsigned int GAMEPAD_BIT_to_button_int(GAMEPAD_BIT b_p){
	switch(b_p){
		case GAMEPAD_A:  	 return 0;
		case GAMEPAD_B: 	 return 1;
		case GAMEPAD_X: 	 return 2;
		case GAMEPAD_Y: 	 return 3;
		case GAMEPAD_LB:	 return 4;
		case GAMEPAD_RB:	 return 5;
		case GAMEPAD_SELECT: return 6;
		case GAMEPAD_START:  return 7;
		case GAMEPAD_MIDDLE: return 8;
		case GAMEPAD_LS: 	 return 9;
		case GAMEPAD_RS:  	 return 10;
		case GAMEPAD_LEFT:   return 11;
		case GAMEPAD_RIGHT:  return 12;
		case GAMEPAD_UP:     return 13;
		case GAMEPAD_DOWN:   return 14;
		default:std::cout<<"invalid gamepad bit cannot be converted"<<std::endl;return 0;
	}
}
GAMEPAD_BIT button_int_to_GAMEPAD_BIT(unsigned int i_p){
	switch(i_p){
		case 0: return GAMEPAD_A;
		case 1: return GAMEPAD_B;
		case 2: return GAMEPAD_X;
		case 3: return GAMEPAD_Y;
		case 4: return GAMEPAD_LB;
		case 5: return GAMEPAD_RB;
		case 6: return GAMEPAD_SELECT;
		case 7: return GAMEPAD_START;
		case 8: return GAMEPAD_MIDDLE;
		case 9: return GAMEPAD_LS;
		case 10:return GAMEPAD_RS;
		case 11:return GAMEPAD_LEFT;
		case 12:return GAMEPAD_RIGHT;
		case 13:return GAMEPAD_UP;
		case 14:return GAMEPAD_DOWN;
		default:std::cout<<"invalid int cannot be converted to gamepad bit"<<std::endl;return INVALID_BIT;
	}
}