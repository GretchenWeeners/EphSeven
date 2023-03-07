#include <Windows.h> // Windows API header

// Add linker directives to specify subsystem and entry point
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main()
{
    // Register a hotkey with the F7 key using RegisterHotKey() function
    // Parameters: HWND hWnd - Handle to the window that will receive hotkey messages (NULL means the application's message queue)
    //             int id - Identifier of the hotkey
    //             UINT fsModifiers - Modifier keys (0 means no modifiers)
    //             UINT vk - Virtual key code of the hotkey (VK_F7 means F7 key)
    if (!RegisterHotKey(NULL, 1, 0, VK_F7))
    {
        // If the hotkey registration fails, return 1
        return 1;
    }

    // Message loop to handle hotkey messages
    MSG msg = { 0 }; // Declare and initialize a MSG struct variable
    while (GetMessage(&msg, NULL, 0, 0) != 0) // Retrieve and process messages until WM_QUIT is received
    {
        if (msg.message == WM_HOTKEY) // If the message is a hotkey message
        {
            // Get the handle of the foreground window using GetForegroundWindow() function
            HWND hForeground = GetForegroundWindow();

            // Toggle the window's topmost property using GetWindowLongPtr() and SetWindowPos() functions
            // GetWindowLongPtr() retrieves information about the specified window (hForeground) using the specified index (GWL_EXSTYLE)
            // WS_EX_TOPMOST is a style constant that specifies that the window should be placed above all non-topmost windows
            // The result of GetWindowLongPtr() is bitwise ANDed with WS_EX_TOPMOST to check if the window is already topmost
            BOOL isTopMost = (BOOL)GetWindowLongPtr(hForeground, GWL_EXSTYLE) & WS_EX_TOPMOST;

            // SetWindowPos() changes the size, position, and Z order of the specified window
            // Parameters: HWND hWnd - Handle to the window to move (hForeground)
            //             HWND hWndInsertAfter - Handle to the window to precede the positioned window in the Z order
            //                                    (isTopMost ? HWND_NOTOPMOST : HWND_TOPMOST) means the window should be either
            //                                    not topmost or topmost depending on the value of isTopMost
            //             int X, int Y - Position of the window (0, 0 means no change)
            //             int cx, int cy - Size of the window (0, 0 means no change)
            //             UINT uFlags - SWP_NOMOVE and SWP_NOSIZE flags to prevent the window from being moved or resized
            SetWindowPos(hForeground, isTopMost ? HWND_NOTOPMOST : HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        }
    }

    // Return 0 on successful exit
    return 0;
}
