#include <iostream>
#include <Windows.h>

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0)
    {
        // Block all key events
        return 1;
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

HHOOK hKeyboardHook;

int main()
{
    std::cout << R"(
 /$$   /$$                     /$$$$$$$  /$$                     /$$                          
| $$  /$$/                    | $$__  $$| $$                    | $$                          
| $$ /$$/   /$$$$$$  /$$   /$$| $$  \ $$| $$  /$$$$$$   /$$$$$$$| $$   /$$  /$$$$$$   /$$$$$$ 
| $$$$$/   /$$__  $$| $$  | $$| $$$$$$$ | $$ /$$__  $$ /$$_____/| $$  /$$/ /$$__  $$ /$$__  $$
| $$  $$  | $$$$$$$$| $$  | $$| $$__  $$| $$| $$  \ $$| $$      | $$$$$$/ | $$$$$$$$| $$  \__/
| $$\  $$ | $$_____/| $$  | $$| $$  \ $$| $$| $$  | $$| $$      | $$_  $$ | $$_____/| $$      
| $$ \  $$|  $$$$$$$|  $$$$$$$| $$$$$$$/| $$|  $$$$$$/|  $$$$$$$| $$ \  $$|  $$$$$$$| $$      
|__/  \__/ \_______/ \____  $$|_______/ |__/ \______/  \_______/|__/  \__/ \_______/|__/      
                     /$$  | $$                                                                
                    |  $$$$$$/                                                                
                     \______/                                                         

Closing this window will cause the keyboard to work again.
이 창을 닫으면 키보드가 다시 동작 합니다.
)" << std::endl;

    HINSTANCE hInstance = GetModuleHandle(NULL);

    hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, hInstance, 0);
    if (!hKeyboardHook)
    {
        std::cerr << "Failed to set keyboard hook." << std::endl;
        return 1;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hKeyboardHook);

    return 0;
}