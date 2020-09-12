#include "gamestate/Gamestate_Manager.hpp"
#include "communal/Communal.hpp"
#include "communal/Duration_Check.hpp"
#include <thread>



int main(){
	chrono::milliseconds sleep_time(17);// add options

	Data_Packet data;

	seed();

	int incorrect_window_size_counter=0;
	int iws_counter_max=30;



	sf::VideoMode videomode= sf::VideoMode::getFullscreenModes().at(0);
	sf::VideoMode(sf::VideoMode::getFullscreenModes().at(0).width, sf::VideoMode::getFullscreenModes().at(0).height, sf::VideoMode::getFullscreenModes().at(0).bitsPerPixel);
	
	sf::RenderWindow window(videomode,"Core Engine", sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true); 
	window.setMouseCursorVisible(true);
	window.setKeyRepeatEnabled(false);


	Gamestate_Manager gamestate_manager;
	Layer::set_new_resolution(window.getSize().x,window.getSize().y);
	gamestate_manager.update_layer_resolutions();


	while (window.isOpen()){

		if(incorrect_window_size_counter==0){
			if(Layer::get_current_res_x()!=window.getSize().x ||Layer::get_current_res_y()!=window.getSize().y){
				//std::cout<<"Incorrect window size detected!"<<std::endl;
				Layer::set_new_resolution(window.getSize().x,window.getSize().y);
				gamestate_manager.update_layer_resolutions();
				gamestate_manager.resolution_error(true);
			}
			incorrect_window_size_counter=iws_counter_max;
		}else{
			incorrect_window_size_counter--;
		}

    	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
    	Duration_Check::start("total");


			
		window.clear();

		gamestate_manager.update(window);
		gamestate_manager.render(window);
		while(gamestate_manager.has_send_data()){
			data= gamestate_manager.get_send_data();
			if(data.get_data_type()!="empty"){
				//std::cout<<"driver got data: "+data.get_data_type()<<"\n";
			}
			if(data.get_data_type()=="close"){
				Duration_Check::kill();
				window.close();
			}
			if(data.get_data_type()=="hide_mouse"){
				window.setMouseCursorVisible(false);
			}
			if(data.get_data_type()=="unhide_mouse"){
				window.setMouseCursorVisible(true);
			}
			if(data.get_data_type()=="recreate_window"){
				videomode= sf::VideoMode(Layer::get_current_res_x(), Layer::get_current_res_y(), sf::VideoMode::getFullscreenModes().at(0).bitsPerPixel);
				Duration_Check::start("changing resolution");
				if(!Layer::is_fullscreen()){
					window.create(videomode, "Core Engine", sf::Style::Close);
					window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width/2)-(videomode.width/2),(sf::VideoMode::getDesktopMode().height/2)-(videomode.height/2)));
				}else{
					window.create(videomode, "Core Engine", sf::Style::Fullscreen);
				}
				incorrect_window_size_counter=iws_counter_max;
				gamestate_manager.update_layer_resolutions();
				gamestate_manager.resolution_error(false);
				Duration_Check::stop("changing resolution");
			}
		}

		window.display();

    	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
   	 	chrono::milliseconds duration = chrono::duration_cast<chrono::milliseconds>( (t2 - t1) );
   	 	chrono::microseconds duration2 = chrono::duration_cast<chrono::microseconds>( (t2 - t1) );
		Duration_Check::stop("total");
		//this_thread::sleep_for(sleep_time-duration);
		
	}
	Duration_Check::print_breakpoints();
	return 0;
}
