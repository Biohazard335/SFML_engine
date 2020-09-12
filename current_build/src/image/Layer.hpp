#ifndef Layer_HPP
#define Layer_HPP
#include <SFML/Graphics/View.hpp>
#include <string>

class Layer:public sf::View{

public:
	
enum DISPLAY_TYPE{
	STRETCH_TO_FIT=0,
	SMART_SCALE=1,
	PIXEL_PERFECT=2
};

enum BEHAVIOR{
	TRANSPARENT=0, //doesn't steal clicks, may cause things to happen on lower layer that are covered by current!
	SOLID=1, 		//steals clicks from everything directly covered by this layer 
	LOCKOUT=2		//steals all clicks from all lower layers
};

private:
	static double default_res_x;
	static double default_res_y;
	static double current_res_x;
	static double current_res_y;
	static DISPLAY_TYPE display_type;
	static bool fullscreen;

	double I_s_o=0;
	double I_l_o=1;
	double J_s_o=0;
	double J_l_o=1;
	double I_s=0;
	double I_l=1;
	double J_s=0;
	double J_l=1;
	double Xs;
	double Ys;
	int original_size_x;
	int original_size_y;
	int original_center_x;
	int original_center_y;
	double black_bar_size_x=0;
	double black_bar_size_y=0;

	std::string layer_name; 

	BEHAVIOR behavior=LOCKOUT;

	bool active=true;
public:
	Layer(std::string n_p);
	void set_original_viewport(double,double,double,double);
	void set_original_size(int,int);
	void set_original_center(int,int);
	void resolve_new_resolution();

	double window_to_layer_x(double);
	double window_to_layer_y(double);

	bool is_active(){return active;}
	void set_active(bool b_p){active=b_p;}

	void set_behavior(BEHAVIOR b_p){behavior=b_p;}
	BEHAVIOR get_behavior(){return behavior;}

	std::string get_layer_name(){return layer_name;}
	void set_layer_name(std::string n_p){layer_name=n_p;}

	bool window_point_in_viewport(double x_p, double y_p);

	static void set_new_resolution(double x_p, double y_p);

	static double get_current_res_x(){
		return current_res_x;
	}
	static double get_current_res_y(){
		return current_res_y;
	}
	static double get_default_res_x(){
		return default_res_x;
	}
	static double get_default_res_y(){
		return default_res_y;
	}

	static void set_display_type(DISPLAY_TYPE d_p){display_type=d_p;}
	static DISPLAY_TYPE get_display_type(){return display_type;}
	static bool is_fullscreen(){return fullscreen;}
	static void set_fullscreen(bool b_p){fullscreen=b_p;}
};


#endif