#include "platform_window.h"

namespace TAL {
    PlatformWindow::PlatformWindow() {}

    void PlatformWindow::OpenWindow(WindowData data) {
        InitWindow(data.width, data.height, data.title.c_str());

        SetTargetFPS(60);
    }

    bool PlatformWindow::Update() {
        
        return WindowShouldClose();
    }

    PlatformWindow::~PlatformWindow() {
        CloseWindow();
    }
}