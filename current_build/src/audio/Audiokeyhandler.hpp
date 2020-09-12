#ifndef AUDIOKEYHANDLER_HPP
#define AUDIOKEYHANDLER_HPP

const int kl=256;
class Audiokeyholder;

#include <memory>
class Audiokeyholder;

class Audiokeyhandler{
private:
	static const int keys_length=kl;
	static std::shared_ptr<int> keys[kl];
public:
	Audiokeyhandler();
	static void give_new_key(Audiokeyholder& holder);
	static bool is_used(int);
	static void free(int);
	static int get_length(){return keys_length;}
};


#endif