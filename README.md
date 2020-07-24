# Breakout

This is my Submission for my C++ Capstone Project of Udacity.

It is a simple implementation of the so loved Breakout game.
Your goal is to destroy all blocks with the ball.
The balls should not touch the bottom.
You are the paddle, with which you can deflect the balls.

If a ball touches the bottom it disappears.
If no balls are left, you will loose.

The Blocks can destroyed when they are hitted by the balls multiple times.
If all blocks are destroyed you will win.

Look out for power up blocks.

## Linux installation

gcc version 9.1 or above is needed
and some libraries have to be installed
 - sudo apt install cmake libsdl2-dev libsdl2-image-dev
 
## Build steps

 - mkdir build && cd build
 - cmake ..
 - make
 
## Run

  - ./breakout
  
## Code structure

The whole source code is in the Breakout folder.

### Class structure

![alt text](https://github.com/SachioKuro/Breakout/blob/master/breakout_structure.PNG?raw=true)

## Rubric Points, which are addressed

### Compiling and Testing (All Rubric Points REQUIRED)

- The submission must compile and run.
  - YES
  
### Loops, Functions, I/O

- The project demonstrates an understanding of C++ functions and control structures.
  - YES (Everywhere)
- The project reads data from a file and process the data, or the program writes data to a file.
  - YES (Breakout/LevelLoader.cpp -> bool LevelLoader::LoadLevel(Game* game, std::string const& level, std::vector<GameObject*> &gos))
- The project accepts user input and processes the input.
  - YES (Breakout/Controller.cpp -> void Breakout::Controller::HandleInput(bool& running, GameObject* game_object))
  
### Object Oriented Programming

- The project uses Object Oriented Programming techniques.
  - YES (Everywhere, see class structure)
- Classes use appropriate access specifiers for class members.
  - YES (Most of the fields are set to private with public getters and setters for some of them)
- Class constructors utilize member initialization lists.
  - YES (throughout the code I made heavy use of initialization lists)
- Classes abstract implementation details from their interfaces.
  - I think YES in most cases
- Classes encapsulate behavior.
  - YES (Everywhere)
- Classes follow an appropriate inheritance hierarchy.
  - YES (Ball inherit from MovableGameObject which inherit from GameObject; Paddle and Block inherit from GameObject; Block_Ball inherit from Block; 
  Composition is used within Game.cpp, which has Renderer, Controller and Physics; MovableGameObject and GameObject are virtual classes and overridden methods are marked as such)
- Overloaded functions allow the same function to operate on different parameters.
  - YES (Renderer and Physics makes use of overloaded functions)
- Derived class functions override virtual base class functions.
  - YES (Ball, Paddle, Block, Block_Ball overrides the methods Render, Updete and OnDestroy)
- Templates generalize functions in the project.
  - YES (Renderer.hpp)

### Memory Management

- The project makes use of references in function declarations.
  - YES (In LevelLoader and Physics, the vectors are passed as a reference)
- The project uses destructors appropriately.
  - YES (Game.cpp uses the destructor to delete the unmanaged paddle, balls and blocks)
