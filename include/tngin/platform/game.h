#pragma once

#include <string>

namespace TAL {
    class Game {
    public:
        Game();
        explicit Game(std::string windowTitle);

        virtual ~Game(); 

        // method to run main game
        void Run();
    protected:
        virtual void Update(float deltaTime) {};
        virtual void PhysicsUpdate(float deltaTime) {};

    private:
        void initializeServices();
        void shutdownServices();

    public:

    private:
        std::string _title;
        bool _running;
    };

    extern Game* CreateGame();
}