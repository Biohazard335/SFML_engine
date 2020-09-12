#include "Path_Node.hpp"
#include <cstdlib>

Path_Node::Path_Node(Point p_p,std::shared_ptr<Path_Node> parent_p,Point end_p){
	coordinates=p_p;
	parent=parent_p;
	compute_h_cost(end_p);
	compute_g_cost();
}

void Path_Node::recreate(Point p_p,std::shared_ptr<Path_Node> parent_p,Point end_p){
	coordinates=p_p;
	parent=parent_p;
	compute_h_cost(end_p);
	compute_g_cost();
}


bool Path_Node::compute_h_cost(Point end_p){
	if(end_p==coordinates){
		return true;
	}else{
		Point distance=end_p-coordinates;
		distance=Point(abs(distance.get_x()),abs(distance.get_y()));
		int non_diagonal=0;

		if(distance.get_x()>distance.get_y()){
			non_diagonal=distance.get_x()-distance.get_y();
			h_cost=(non_diagonal*10)+(distance.get_y()*14);
		}else if(distance.get_x()<distance.get_y()){
			non_diagonal=distance.get_y()-distance.get_x();
			h_cost=(non_diagonal*10)+(distance.get_x()*14);
		}else{
			h_cost=distance.get_x()*14;
		}
	}
	return false;
}

void Path_Node::compute_g_cost(){
	if(parent!=nullptr){
		g_cost=parent->get_g_cost();
		Point distance=parent->get_coordinates()-coordinates;
		if(distance.get_x()+distance.get_y()==1 ||distance.get_x()+distance.get_y()==-1){
			g_cost+=10;
		}else{
			g_cost+=14;
		}
	}else{
		g_cost=0;
	}
}