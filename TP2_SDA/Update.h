#pragma once
#include <Windows.h>

class Update {
private:
    HWND a_main_window = nullptr;

    Update() = default;
    ~Update() = default;

public:
    static Update* getInstance();
    void setMainWindow(HWND p_main_window);
    void triggerMainWindow();
};
