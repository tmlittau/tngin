#pragma once

#include <string>

namespace TAL {
    typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;
    class Game {
    public:
        Game();
        explicit Game(std::string windowTitle);

        virtual ~Game(); 

        // method to run main game
        void Run();
    protected:
        virtual void Update() {};
        virtual void PhysicsUpdate(float deltaTime) {};

    private:
        void initializeServices();
        void shutdownServices();

    public:
        GameScreen _gameState;

    private:
        std::string _windowTitle;
        bool _running;
    };

    extern Game* CreateGame();
}