#define _CRT_SECURE_NO_WARNINGS

#include "Main.h"
#include <d3dx9tex.h>
#pragma comment(lib, "d3dx9.lib")
//#include "image_dop.h"

//#include "config.h"
#include "Controller/appcontroller.h"
#include "View/appview.h"
#include "font_dop.h"

// Main code

HWND main_hwnd = nullptr;

LPDIRECT3DDEVICE9        g_pd3dDevice;
D3DPRESENT_PARAMETERS    g_d3dpp;
LPDIRECT3D9              g_pD3D;
static UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;

Controller controller_c;
View view_c;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return false;

    // Create the D3DDevice
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.MultiSampleQuality = D3DMULTISAMPLE_NONE;
    g_d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
     g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
      //g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;
    return true;
}


void CleanupDeviceD3D()
{
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
    if (g_pD3D) { g_pD3D->Release(); g_pD3D = nullptr; }
}

void ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();

    HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}

#include <dwmapi.h>

#pragma comment(lib, "dwmapi.lib")

int APIENTRY WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{

    // Create application window
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = instance;
    wc.lpszClassName = "CalculatorGui";


    RegisterClassEx(&wc);

  //  main_hwnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_LAYERED, ("ImGui Example"), NULL, WS_POPUP, 0, 0, 500, rc.bottom, NULL, NULL, wc.hInstance, NULL);

    main_hwnd = CreateWindowExA( WS_EX_LAYERED, "CalculatorGui", "CalculatorGui", WS_POPUP,
        0, 0, 1920, 1080, NULL, NULL, wc.hInstance, NULL);

    SetWindowPos(main_hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    SetLayeredWindowAttributes(main_hwnd, RGB(0, 0, 0), BYTE(255), LWA_ALPHA);



    {
         RECT client_area{};
         GetClientRect(main_hwnd, &client_area);

         RECT window_area{};
         GetWindowRect(main_hwnd, &window_area);

         POINT diff{};
         ClientToScreen(main_hwnd, &diff);

         const MARGINS margins{
             window_area.left + (diff.x - window_area.left),
             window_area.top + (diff.y - window_area.top), 
             client_area.right,
             client_area.bottom
         };

         DwmExtendFrameIntoClientArea(main_hwnd, &margins);
    }

     

 //   UpdateLayeredWindow(main_hwnd);
    // Initialize Direct3D
    if (!CreateDeviceD3D(main_hwnd))
    {
        CleanupDeviceD3D();
        UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ShowWindow(main_hwnd, SW_SHOWDEFAULT);
    UpdateWindow(main_hwnd);

   
   
    // Setup Dear ImGui context
    ImGui::CreateContext();




    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize.x = 1920;
    io.DisplaySize.y = 1080;



    // Setup Dear ImGui style

    ImGui::StyleColorsDark();

    ImFontConfig font_config;
    font_config.OversampleH = 1; //or 2 is the same
    font_config.OversampleV = 1;
    font_config.PixelSnapH = 1;

    static const ImWchar ranges[] =
    {
        0x0020, 0x00FF, // Basic Latin + Latin Supplement
        0x0400, 0x044F, // Cyrillic
        0,
    };


    view_c.fonts.main_font[0] = io.Fonts->AddFontFromMemoryTTF((void*)MuseoSansCyrl900, sizeof(MuseoSansCyrl900), 35.f, &font_config, ranges);
    view_c.fonts.main_font[1] = io.Fonts->AddFontFromMemoryTTF((void*)MuseoSansCyrl900, sizeof(MuseoSansCyrl900), 55.f, &font_config, ranges);
    view_c.fonts.main_font[2] = io.Fonts->AddFontFromMemoryTTF((void*)MuseoSansCyrl900, sizeof(MuseoSansCyrl900), 20.f, &font_config, ranges);
    view_c.fonts.main_font[3] = io.Fonts->AddFontFromMemoryTTF((void*)MuseoSansCyrl700, sizeof(MuseoSansCyrl700), 25.f, &font_config, ranges);
    view_c.fonts.main_font[4] = io.Fonts->AddFontFromMemoryTTF((void*)MuseoSansCyrl700, sizeof(MuseoSansCyrl700), 20.f, &font_config, ranges);
    view_c.fonts.main_font[5] = io.Fonts->AddFontFromMemoryTTF((void*)MuseoSansCyrl900, sizeof(MuseoSansCyrl900), 25.f, &font_config, ranges);
    view_c.fonts.sup_font = io.Fonts->AddFontFromMemoryTTF((void*)MuseoSansCyrl900, sizeof(MuseoSansCyrl900), 15.f, &font_config, ranges);


    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(main_hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    

    // Main loop
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {

   
   


        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            continue;
        }

        if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
        {
            g_d3dpp.BackBufferWidth = g_ResizeWidth;
            g_d3dpp.BackBufferHeight = g_ResizeHeight;
            g_ResizeWidth = g_ResizeHeight = 0;
            ResetDevice();
        }

       
        IDirect3DVertexDeclaration9* vertex_dec;
        g_pd3dDevice->GetVertexDeclaration(&vertex_dec);

        IDirect3DVertexShader9* vertex_shader;
        g_pd3dDevice->GetVertexShader(&vertex_shader);

        controller_c.on_update();

        // Start the Dear ImGui frame
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();

        ImGui::NewFrame();
        {
            controller_c.gui_controller(main_hwnd);
        }
        ImGui::EndFrame();

        g_pd3dDevice->SetVertexShader(vertex_shader);
        g_pd3dDevice->SetVertexDeclaration(vertex_dec);

        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x * clear_color.w * 255.0f), (int)(clear_color.y * clear_color.w * 255.0f), (int)(clear_color.z * clear_color.w * 255.0f), (int)(clear_color.w * 255.0f));
        g_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, NULL, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }

        HRESULT result = g_pd3dDevice->Present(nullptr, nullptr, nullptr, nullptr);

        // Handle loss of D3D9 device
        if (result == D3DERR_DEVICELOST)
            ResetDevice();


    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    DestroyWindow(main_hwnd);
    UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;

        g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
        g_ResizeHeight = (UINT)HIWORD(lParam);

        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }


    return DefWindowProc(hWnd, msg, wParam, lParam);

}