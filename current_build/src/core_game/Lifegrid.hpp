#ifndef LIFEGRID_HPP
#define LIFEGRID_HPP

#include "Point.hpp"
#include <vector>
#include "SFML/Graphics.hpp"


class Lifegrid: public sf::Drawable, public sf::Transformable{

private:
	sf::VertexArray vertex_array;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;



	int starting_life=40;
	int length_x;
	int length_y;
	std::vector<bool> current_state;
	std::vector<bool> next_state;

public:

	Lifegrid(){}
	Lifegrid(int x_p, int y_p){length_x=x_p;length_y=y_p;}
	


};

#endif