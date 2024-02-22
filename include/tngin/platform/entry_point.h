#pragma once

#include <tngin/service_locator.h>

#include <tngin/platform/game.h>

int main(int argc, char** argv) {
    // Create Game
    auto* aGame = TAL::CreateGame();

    // Run the application
    aGame->Run();

    // once it's done, delete the game
    delete aGame;
}