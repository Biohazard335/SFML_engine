#ifndef SLIDER_HPP
#define SLIDER_HPP

#include "Button.hpp"
#include "../image/Sprite_Sheet.hpp"

class Slider :public Button{


private:
	int discrete_gamepad_timer=0;

	double origin_x;
	double origin_y;
	double name_origin;

	double val_x;

	double bar_width=400;
	double bar_height=10;
	double sub_s_width=6;
	double sub_s_height=14;

	double value;
	double max=100;
	double min=0;
	bool discrete=false;
	int subdivisions=0;
	double sub_increment=0;
	double sub_distance=0;
	bool vertical=false;

	bool show_name=true;
	bool align_name=true;
	bool show_value=true;
	bool abs_name_dist=false;

	int display_value_distance=50;
	int display_name_distance=50;

	int absolute_name_distance=300;



	sf::Text display_name;
	sf::Text display_value;

	sf::Color font_color=sf::Color(117,24,15,225);

	sf::Sprite bar_s;
	sf::Sprite subdivision_s;
	sf::Sprite cursor_s;
	sf::Sprite highlighted_s;
	sf::Sprite on_s;

public:
	enum SLIDER_OPTIONS{
		DEFAULT=	0,
		NO_NAME=	0b1,
		ALIGN_BAR=	0b10,
		NO_VALUE=	0b100,
		ABS_NAME_DIST=0b1000,
	};
	Slider(std::string name_p, double x_p, double y_p, Data_Packet data_p, int l_p,int u_p,int d_p, int r_p,int options_p);
	Slider(std::string name_p, double x_p, double y_p, int sub_p, Data_Packet data_p, int l_p,int u_p,int d_p, int r_p,int options_p);
	Slider(std::string name_p, double x_p, double y_p,double min_p, double max_p, Data_Packet data_p, int l_p,int u_p,int d_p, int r_p,int options_p);
	Slider(std::string name_p, double x_p, double y_p, int sub_p, double min_p, double max_p, Data_Packet data_p, int l_p,int u_p,int d_p, int r_p,int options_p);
	void create(std::string name_p, double x_p, double y_p, int sub_p, double min_p, double max_p, Data_Packet data_p, int l_p,int u_p,int d_p, int r_p,int options_p);
	void draw(sf::RenderWindow& window)override;
	void set_font(sf::Font& font);
	void load_sprites(Sprite_Sheet& sheet);
	bool check_clicked(Mousey&) override;
	bool check_highlighted(Mousey& mouse)override;
	bool pushed_by_gamepad(Gamepad& gamepad)override;
	void update(Gamepad& gamepad)override;
	double manually_set_value(double v_p);


	double get_value(){return value;}
};

#endif