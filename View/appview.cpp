#define IMGUI_DEFINE_MATH_OPERATORS

#include "appview.h"
#include "../Controller/appcontroller.h"

extern Controller controller_c;

void View::init_gui(HWND main_hwnd) {

    ImGui::SetNextWindowSize(ImVec2(window_size.x, window_size.y));
    if (ImGui::Begin("CalculatorGui", &active, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize)) {

      

        ImGuiWindow* window = ImGui::GetCurrentWindow();

        auto wp = window->Pos;
        auto ws = window->Size;


        POINT p;
        if (GetCursorPos(&p))
        {
            if ((p.x > wp.x && p.y > wp.y) &&
                (p.x < wp.x + ws.x && p.y < wp.y + ws.y)) {
                SetWindowLongA(main_hwnd, GWL_EXSTYLE, WS_EX_LAYERED);
            }
            else {
                SetWindowLongA(main_hwnd, GWL_EXSTYLE, WS_EX_TRANSPARENT | WS_EX_LAYERED);
            }
        }

        window->DrawList->AddText(ImVec2(wp.x + 20, wp.y + 10),
            ImColor(255, 255, 255), u8"Калькулятор");
        
        window->DrawList->AddText(ImVec2(wp.x + (window_size.x - 20) - ImGui::CalcTextSize(controller_c.get_help_value().c_str()).x, wp.y + 45),
            ImColor(140, 140, 140), controller_c.get_help_value().c_str());

        window->DrawList->AddText(ImVec2(wp.x + (window_size.x - 30) - ImGui::CalcTextSize(controller_c.get_operator_value().c_str()).x, wp.y + 80),
            ImColor(255, 255, 255), controller_c.get_operator_value().c_str());

        window->DrawList->AddText(ImVec2(wp.x + (window_size.x - 20) - ImGui::CalcTextSize(controller_c.get_final_value().c_str()).x, wp.y + 120),
            ImColor(255, 255, 255), controller_c.get_final_value().c_str());



        button_init(wp.x, wp.y, window);
   
    }
    ImGui::End();
}

void View::button_init(int x, int y, ImGuiWindow* window) {
    static int x_space = 0;
    static int y_space = 0;
    static int count_button_x = 0;

    for (int i = 0; i < 16; i++) {
        button_option[i].rectangle = { x + 10 + x_space, y + 200 + y_space, x + 10 + 75 + x_space, y + 270 + y_space };
        x_space += 82;

        count_button_x++;

        if (count_button_x == 4) {
            y_space += 75;
            x_space = 0;
            count_button_x = 0;
        }
    }

    x_space = 0;
    y_space = 0;

    for (int b = 0; b < 16; b++) {

        ImColor default_color = ImColor(50, 50, 50, 255);


        if (ImGui::IsMouseHoveringRect(ImVec2(button_option[b].rectangle.left, button_option[b].rectangle.top),
            ImVec2(button_option[b].rectangle.right, button_option[b].rectangle.bottom),
            true)) {


            if (ImGui::GetIO().MouseClicked[0] || ImGui::GetIO().MouseDown[0]) {
                default_color = ImColor(25, 25, 25, 255);           
           
            }
            else 
                default_color = ImColor(40, 40, 40, 255);

            if (ImGui::GetIO().MouseClicked[0]) {
                controller_c.sended_command_button(button_option[b].text);
            }
        }

     

        window->DrawList->AddRectFilled(ImVec2(button_option[b].rectangle.left, button_option[b].rectangle.top),
            ImVec2(button_option[b].rectangle.right, button_option[b].rectangle.bottom),
            default_color, 7.f);



        window->DrawList->AddText(ImVec2(button_option[b].rectangle.left + (75 / 2) - (ImGui::CalcTextSize(button_option[b].text.c_str()).x / 2), button_option[b].rectangle.top + (70 / 2) - (ImGui::CalcTextSize(button_option[b].text.c_str()).y / 2)),
            ImColor(255, 255, 255), button_option[b].text.c_str());
    }


    button_option[0].text = "7";
    button_option[1].text = "8";
    button_option[2].text = "9";
    button_option[3].text = "x";

    button_option[4].text = "4";
    button_option[5].text = "5";
    button_option[6].text = "6";
    button_option[7].text = "-";

    button_option[8].text  = "1";
    button_option[9].text  = "2";
    button_option[10].text = "3";
    button_option[11].text = "+";

    button_option[12].text = "C";
    button_option[13].text = "0";
    button_option[14].text = "/";
    button_option[15].text = "=";

}

void View::background_decoration(ImGuiWindow* window) {
    auto wp = window->Pos;
    auto ws = window->Size;

    static auto outline = [](ImGuiWindow* wnd, int i, ImColor col, float r) -> void {
        wnd->DrawList->AddRect(wnd->Pos + ImVec2(i, i), wnd->Pos + wnd->Size - ImVec2(i, i), col, r);
        };

    window->DrawList->AddRectFilled(ImVec2(wp.x + 0, wp.y + 0), ImVec2(wp.x + ws.x, wp.y + ws.y), ImColor(34, 34, 34, 255), 10);

    outline(window, 1, ImColor(255, 255, 255), 10.f);
}
