#ifndef HITBOX_HPP
#define HITBOX_HPP

#include "Point.hpp"

class Hitbox{

private:
	int x;
	int y;
	int width;
	int height;
	int center_x;
	int center_y;
public:
	Hitbox(){};
	Hitbox(int x_p, int y_p, int w_p, int h_p):x(x_p),y(y_p),width(w_p),height(h_p){};

	int get_x(){return x;}
	int get_y(){return y;}
	int get_width(){return width;}
	int get_height(){return height;}
	int get_center_x(){return center_x;}
	int get_center_y(){return center_y;}

	void set_x(int x_p){x=x_p;}
	void set_y(int y_p){y=y_p;}
	void set_width(int w_p){width=w_p;}
	void set_height(int h_p){height=h_p;}

	void create(int x_p, int y_p, int w_p, int h_p){
		x=x_p;
		y=y_p;
		width=w_p;
		height=h_p;
		recenter();
	}

	void move(int mx_p, int my_p){
		x+=mx_p;
		y+=my_p;
		recenter();
	}
	void move(Point p_p){
		x+=p_p.get_x();
		y+=p_p.get_y();
		recenter();
	}

	void recenter(){
		center_x=x+width/2;
		center_y=y+height/2;
	}


	void set_position(int x_p, int y_p){
		x=x_p;
		y=y_p;
	}

	bool is_colliding(Hitbox h){
		bool check_x=false;
		bool check_y=false;

		if(x+width> h.get_x() && x<h.get_x()+h.get_width()){
			check_x=true;
		}else if(h.get_x()+h.get_width()>x && h.get_x()<x+width){
			check_x=true;
		}

		if(y+height>h.get_y() && y<h.get_y()+h.get_height()){
			check_y=true;
		}else if(h.get_y()+h.get_height()>y && h.get_y()<y+height){
			check_y=true;
		}

		return (check_y && check_x);
	}


};


#endif