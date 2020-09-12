#ifndef DURATION_CHECK_HPP
#define DURATION_CHECK_HPP

#include <chrono>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

struct Breakpoint{
	chrono::high_resolution_clock::time_point start_t;
	string name="";
	int total=0;
	int num_tries=0;
	int max=-1;
	int min=-1;

};


class Duration_Check{

private:
	static std::vector<Breakpoint> breakpoints;
	static unsigned int max_string_size;
	static bool killd;

public:
	Duration_Check(){
	}

	static void start(string name_p);
	static void stop_i(int i);
	static void stop(string name_p);
	static void kill(){killd=true;};

	static void stop_start(string name_1, string name_2){
		stop(name_1);
		start(name_2);
	}

	static void print_breakpoints();
};



#endif