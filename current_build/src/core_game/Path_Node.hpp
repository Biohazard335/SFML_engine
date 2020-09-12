#ifndef PATH_NODE_HPP
#define PATH_NODE_HPP

#include "Point.hpp"
#include <memory>

class Path_Node{
private:
	int g_cost=0;
	int h_cost=0;
	Point coordinates=Point(0,0);
	std::shared_ptr<Path_Node> parent=nullptr;
public:
	Path_Node(){}
	Path_Node(Point p_p,std::shared_ptr<Path_Node> parent_p,Point end_p);


	void recreate(Point p_p,std::shared_ptr<Path_Node> parent_p,Point end_p);
	bool compute_h_cost(Point end_p);
	void compute_g_cost();
	void set_parent(std::shared_ptr<Path_Node> parent_p){parent=parent_p;compute_g_cost();}
	void set_coordinates(Point p_p){coordinates=p_p;}
	int get_h_cost(){return h_cost;}
	int get_g_cost(){return g_cost;}
	int get_f_cost(){return (h_cost+g_cost);}
	Point get_coordinates(){return coordinates;}
	std::shared_ptr<Path_Node> get_parent(){return parent;}

};

#endif