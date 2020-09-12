#ifndef POINT_HPP
#define POINT_HPP

class Point{
private:
	int x;
	int y;
public:
	Point(){};
	Point(int x_p, int y_p):x(x_p),y(y_p){}

	Point operator +(Point p_p){return Point(x+p_p.get_x(),y+p_p.get_y());}
	Point operator -(Point p_p){return Point(x-p_p.get_x(),y-p_p.get_y());}
	Point operator *(int i_p){return Point(x*i_p,y*i_p);}
	Point operator /(int i_p){return Point(x/i_p,y/i_p);}
	Point operator *=(int d_p){x*=d_p;y*=d_p;}
	Point operator +=(Point p_p){x+=p_p.get_x();y+=p_p.get_y();}
	Point operator =(Point p_p){x=p_p.get_x();y=p_p.get_y();}

	Point operator -(){return Point(-x,-y);}
	bool operator ==(Point p_p){
		if(p_p.get_x()==x && p_p.get_y()==y)return true;
		else return false;
	}
	bool operator !=(Point p_p){
		if(p_p.get_x()!=x || p_p.get_y()!=y)return true;
		else return false;
	}

	int get_x(){return x;}
	int get_y(){return y;}
	void set_x(int x_p){x=x_p;}
	void set_y(int y_p){y=y_p;}
	void set_point(int x_p, int y_p){set_x(x_p);set_y(y_p);}
	void set_point(Point new_p){set_x(new_p.get_x());set_y(new_p.get_y());}
};

namespace Cardinal{
	const Point North=Point(0,-1);
	const Point South=Point(0,1);
	const Point East=Point(1,0);
	const Point West=Point(-1,0);
	const Point none=Point(0,0);

	static int to_degrees(Point p_p){
		if(p_p==North)return 270;
		else if(p_p==West)return 180;
		else if(p_p==South)return 90;
		else return 0;
	}
	static Point orthogonal(Point p_p){
		if(p_p.get_x()==0){
			return Point(1,0);
		}else{
			return Point(0,1);
		}
	}
}
#endif