#include "Update.h"

Update* Update::getInstance() {
    static Update instance;
    return &instance;
}

void Update::setMainWindow(HWND p_main_window) {
    if (p_main_window) {
        a_main_window = p_main_window;
    }
}

void Update::triggerMainWindow() {
    if (a_main_window) {
        PostMessage(a_main_window, WM_APP + 1, 0, 0);
    }
}