#pragma once
#include "../Main.h"


class View {
private:
	const ImVec2 window_size = { 345, 505 };
public:

	struct fonts_t {
		ImFont* main_font[6];
		ImFont* sup_font;
	};

	struct buttons_calculator_t {
		RECT rectangle = {};
		std::string text = "";

	};

	buttons_calculator_t button_option[16];
	fonts_t fonts;

	bool active = true;

	void init_gui(HWND main_hwnd);
	void background_decoration(ImGuiWindow* window);
	void button_init(int x, int y, ImGuiWindow* window);
};
