#include <stdlib.h>  
#include <time.h>
#include <math.h>
#include "Communal.hpp" 


#define PI 3.14159265



int random(int min_p, int max_p){
	return rand()%(max_p-min_p+1)+min_p;
}

void seed(){
	srand(time(NULL));
}
void set_seed(int s_p){
	srand(s_p);
}

double sin_degrees(double theta){
	return sin(theta*PI/180);
}