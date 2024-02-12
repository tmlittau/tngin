# TNGIN Game Engine

## Usage
To use this Engine library you have to provide a Game class based on the libraries Game class.

The Game Class currently contains two Update methods: Game::Update(float deltaTime) and Game::PhysicsUpdate(float deltaTime). Both methods take in deltaTime.

The methods should be overwritten by the User and implemented, based on the needs of the Game.

Here is a simple example of how the Game class can be used:

```cpp
#include <iostream>

#include <tngin/platform/entry_point.h>
#include <tngin/platform/game.h>

class TGame : public Game {
    public:
        explicit TGame(std::string title) : Game(std::move(title)) {
            std::cout << "Hello from TGame!" << std::endl;
        }
    protected:
        void Update(float deltaTime) override {
            std::cout << "Updating TGame!" << std::endl;
        }
        void PhysicsUpdate(float deltaTime) override {
            std::cout << "Physics Updating TGame!" << std::endl;
        }
};

// Runtime
Game* CreateGame() {
    return new TGame("TNGIN Game");
}
```
