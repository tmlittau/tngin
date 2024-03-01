#pragma once

#include <tngin/platform/window.h>
#include <raylib.h>

namespace TAL {
    class PlatformWindow : public Window {
        public:
            PlatformWindow();
            void OpenWindow(WindowData data) override;
            bool Update() override;

            ~PlatformWindow();
        private:

    };
}