#pragma once

#include <string>

namespace TAL {
    struct WindowData {
        std::string title;
        int width, height;

    };

    class Window {
        public:
            virtual void OpenWindow(WindowData data) = 0;
            virtual bool Update() = 0;

            virtual float GetWidth() const = 0;
            virtual float GetHeight() const = 0;
            virtual void SetKeyCallback() = 0;
            virtual void SetCursorCallback() = 0;
    };
}