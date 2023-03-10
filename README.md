# Snake-Game

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## Description of the Project

The Capstone project chosen is "Snake-Game" and is improved with added features to it.
The features added to the base version of this game are-
* The game now has a restricted boundary which confines the game only inside that boundary and if snake touches the boundary it will die.
* The game now has a provision to improve the scoring with the help of special food which boosts the score by 5 points and is accessible only at times and is active only for a period of 10seconds.

## Code structure

<img src="code_struct"/>

## Output of the program

<img src="output"/>

## Rubric points addressed
----
* The project demonstrates an understanding of C++ functions and control structures.
  * game.h, line 34
  * boundary.h, line 20
  * renderer.cpp, line 79
* The project uses Object Oriented Programming techniques.
  * boundary.h
  * spl_food.h
* Classes use appropriate access specifiers for class members.
  * boundary.h
  * spl_food.h
* Overloaded functions allow the same function to operate on different parameters.
  * boundary.h line 12,16
  * boundary.h line 13,17 and so on
* Classes encapsulate behavior.
  * boundary.h
    class Boundary->Boundary Cell(x,y) is able to determine if the point intersects with the boundary
* The project makes use of references in function declarations.
  * Examples of pass-by-ref
    Renderer.h line 15
* The project uses destructors appropriately.
  * game.cpp line 22,23
