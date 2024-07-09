#include "appmodel.h"
#include <string>

void Model::get_numbers(std::string numbers_in_text) {

	if (current_value_mod == SECOND_VALUE) {
		store_second_value += numbers_in_text;
	}
	else if (current_value_mod == FIRST_VALUE) {
		store_first_value += numbers_in_text;
	}
}

void Model::calculate_operations() {
	if (current_operator == "+") {
		final_value = std::stoi(store_first_value) + std::stoi(store_second_value);
	}
	else if (current_operator == "-") {
		final_value = std::stoi(store_first_value) - std::stoi(store_second_value);
	}
	else if (current_operator == "/") {
		final_value = std::stoi(store_first_value) / std::stoi(store_second_value);
	}
	else if (current_operator == "x") {
		final_value = std::stoi(store_first_value) * std::stoi(store_second_value);
	}
}

bool Model::second_value_empty() {
	if (store_second_value == "")
		return true;

	return false;
}