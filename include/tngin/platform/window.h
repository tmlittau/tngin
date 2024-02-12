#pragma once

#include <string>

struct WindowData {
    std::string title;
    int width, height;

};

class Window {
    public:
        virtual void OpenWindow(WindowData data) = 0;
        virtual bool Update() = 0;
};