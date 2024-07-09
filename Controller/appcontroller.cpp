#include "appcontroller.h"
#include <string>

void Controller::gui_controller(HWND main_hwnd) {
    view_c.init_gui(main_hwnd);
}

void Controller::window_background_controller(ImGuiWindow* window) {
    view_c.background_decoration(window);
}

void Controller::sended_command_button(std::string button_text) {
    check_buttons(button_text);

    if (is_operator) {
        model_c.current_operator = button_text;
        model_c.current_value_mod = SECOND_VALUE;
    }

    if (is_equals) {
        if (button_text == "C")
            model_c.reset();
    }

    if ((model_c.current_value_mod == SECOND_VALUE) && is_equals && !model_c.second_value_empty()) {
        model_c.calculate_operations();
    }

    if ((model_c.current_value_mod == SECOND_VALUE) && (model_c.final_value != 0) && is_number) {
        
        model_c.reset();
    }

    if ((model_c.current_value_mod == SECOND_VALUE) && (model_c.final_value != 0) && is_operator) {

        model_c.current_operator = button_text;

        model_c.store_first_value = std::to_string(model_c.final_value);

        model_c.store_second_value = "";

        model_c.final_value = 0;

    }

    if (is_number)
        model_c.get_numbers(button_text);
}



void Controller::on_update() {
    reset_buttons_events();
}

void Controller::check_buttons(std::string button_text) {
    if (button_text.find("0") != std::string::npos) { is_number = true; return; }
    else if (button_text.find("1") != std::string::npos) { is_number = true; return; }
    else if (button_text.find("2") != std::string::npos) { is_number = true; return; }
    else if (button_text.find("3") != std::string::npos) { is_number = true; return; }
    else if (button_text.find("4") != std::string::npos) { is_number = true; return; }
    else if (button_text.find("5") != std::string::npos) { is_number = true; return; }
    else if (button_text.find("6") != std::string::npos) { is_number = true; return; }
    else if (button_text.find("7") != std::string::npos) { is_number = true; return; }
    else if (button_text.find("8") != std::string::npos) { is_number = true; return; }
    else if (button_text.find("9") != std::string::npos) { is_number = true; return; }
    else if (button_text.find("+") != std::string::npos) { is_operator = true; return; }
    else if (button_text.find("-") != std::string::npos) { is_operator = true; return; }
    else if (button_text.find("x") != std::string::npos) { is_operator = true; return; }
    else if (button_text.find("/") != std::string::npos) { is_operator = true; return; }
    else if (button_text.find("=") != std::string::npos) { is_equals = true;   return; }
    else if (button_text.find("C") != std::string::npos) { is_equals = true;   return; }
}

std::string Controller::get_help_value() {

    if (model_c.final_value != 0) 
        return "";

    if (model_c.current_value_mod == SECOND_VALUE) {
        return model_c.store_first_value;
    }

    return "";
}

std::string Controller::get_operator_value() {

    if (model_c.final_value != 0) 
        return "";
    

    if (model_c.current_value_mod == SECOND_VALUE) {
        return model_c.current_operator;
    }

    return "";
}

std::string Controller::get_final_value() {

    if (model_c.final_value != 0)
        return std::to_string(model_c.final_value);

    if (model_c.current_value_mod == FIRST_VALUE) {
        return model_c.store_first_value;
    }
    else if (model_c.current_value_mod == SECOND_VALUE) {
        return model_c.store_second_value;
    }
}

