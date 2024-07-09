#pragma once
#include "../Main.h"

enum calculation_e {
	FIRST_VALUE,
	SECOND_VALUE
};

class Model {
public:
	int final_value = 0;
	std::string store_first_value = "";
	std::string store_second_value = "";
	std::string current_operator = "";

	int current_value_mod = FIRST_VALUE;

	void get_numbers(std::string numbers_in_text);

	void calculate_operations();

	bool second_value_empty();


	void reset() {

		final_value = 0;
		current_value_mod = FIRST_VALUE;
		store_first_value = "";
		current_operator = "";
		store_second_value = "";

	}


};