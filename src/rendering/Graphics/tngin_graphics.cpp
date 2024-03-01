#include "tngin_graphics.h"

#include "graphics_types.h"
#include "graphics_utils.h"

#include <iostream>

namespace TAL {

    void TNGINGraphics::Init() {
        // Init Graphics 
    }

    void TNGINGraphics::Shutdown() {
        // Shutdown
    }

    void TNGINGraphics::RenderFrame() {
        // Render a frame using raylib
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
            DrawText("WAIT for 2 SECONDS...", 290, 220, 20, GRAY);

        EndDrawing();   
    }

}