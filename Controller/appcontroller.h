#pragma once
#include "../includes.h"

class Controller {
private:
	bool is_operator = false;
	bool is_number = false;
	bool is_equals = false;
public:

	View view_c;
	Model model_c;

	void gui_controller(HWND main_hwnd);

	void window_background_controller(ImGuiWindow* window);

	void sended_command_button(std::string button_text);

	void on_update();

	void check_buttons(std::string button_text);

	std::string get_help_value();

	std::string get_operator_value();

	void reset_buttons_events() {
		is_operator = false;
		is_number = false;
		is_equals = false;
	}

	std::string get_final_value();

};

