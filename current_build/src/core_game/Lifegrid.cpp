#include "Lifegrid.hpp"


void Lifegrid::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform *= getTransform();
	target.draw(vertex_array, states);
}