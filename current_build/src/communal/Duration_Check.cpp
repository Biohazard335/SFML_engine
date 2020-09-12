#include "Duration_Check.hpp"


std::vector<Breakpoint> Duration_Check::breakpoints={};
unsigned int Duration_Check::max_string_size=0;
bool Duration_Check::killd=false;

void Duration_Check::start(string name_p){
	if(!killd){
		for(unsigned int i=0;i<breakpoints.size();i++){
			if(breakpoints.at(i).name==name_p){
				breakpoints.at(i).start_t=chrono::high_resolution_clock::now();
				return;
			}
		}
		Breakpoint b;
		b.name=name_p;
		b.start_t=chrono::high_resolution_clock::now();
		breakpoints.push_back(b);
		if(name_p.size()>max_string_size){
			max_string_size=name_p.size();
		}
	}
}

void Duration_Check::stop_i(int i){
	if(!killd){
		int duration=chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - breakpoints.at(i).start_t).count();
		breakpoints.at(i).total+=duration;
		if(breakpoints.at(i).min==-1 || breakpoints.at(i).min>duration){
			breakpoints.at(i).min=duration;
		}
		if(breakpoints.at(i).max==-1 || breakpoints.at(i).max<duration){
			breakpoints.at(i).max=duration;
		}
		breakpoints.at(i).num_tries++;	
	}
}
void Duration_Check::stop(string name_p){
	if(!killd){
		for(unsigned int i=0;i<breakpoints.size();i++){
			if(breakpoints.at(i).name==name_p){
				stop_i(i);
				return;
			}
		}
		std::cout<<"\nERROR: no breakpoint named "<<name_p<<"\n";
	}
}
void Duration_Check::print_breakpoints(){
	std::cout<<"\n";
	for(unsigned int i=0;i<breakpoints.size();i++){
		int num_tabs=(max_string_size/8-breakpoints.at(i).name.size()/8);
		std::cout<<breakpoints.at(i).name<<"\t";
		for(int j=0;j<num_tabs;j++){
			std::cout<<"\t";
		}
		std::cout<<breakpoints.at(i).min<<"\t"<<(breakpoints.at(i).total/breakpoints.at(i).num_tries)<<"\t"<<breakpoints.at(i).max<<"\n";
	}
	std::cout<<"\n";
}