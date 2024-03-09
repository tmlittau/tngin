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

            virtual float GetAspectRatio() const = 0;
            virtual void SetKeyCallback() = 0;
    };
}