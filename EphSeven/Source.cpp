#include <Windows.h>
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main()
{
    // Register a hotkey with the F7 key
    if (!RegisterHotKey(NULL, 1, 0, VK_F7))
    {
        return 1;
    }

    // Message loop to handle hotkey messages
    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0) != 0)
    {
        if (msg.message == WM_HOTKEY)
        {
            // Get the handle of the foreground window
            HWND hForeground = GetForegroundWindow();

            // Toggle the window's topmost property
            BOOL isTopMost = (BOOL)GetWindowLongPtr(hForeground, GWL_EXSTYLE) & WS_EX_TOPMOST;
            SetWindowPos(hForeground, isTopMost ? HWND_NOTOPMOST : HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        }
    }
}