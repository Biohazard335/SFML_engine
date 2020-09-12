#ifndef MUTUALLY_EXCLUSIVE_BUTTON_LIST_HPP
#define MUTUALLY_EXCLUSIVE_BUTTON_LIST_HPP

#include "Button.hpp"
#include <memory>

class MEBL: public Button{

private:
	std::vector<std::unique_ptr<Button>> list;
	int selected=0;
	int gamestate_buttons_number=-1;
public:
	MEBL(int gbn_p,std::initializer_list<std::shared_ptr<Button>> list_p, int l_p,int u_p,int d_p, int r_p);
	void draw(sf::RenderWindow& window);
	bool check_clicked(Mousey&) override;
	bool check_highlighted(Mousey&) override;
	void manually_set_highlighted(bool) override;
	void manually_set_on(bool) override;
	int get_button_up()override;
	int get_button_down()override;
	int get_button_left()override;
	int get_button_right()override;
	int get_button_all(int);

	bool pushed_by_gamepad(Gamepad& gamepad)override;

	std::vector<std::unique_ptr<Button>>& get_list(){return list;}

};


#endif