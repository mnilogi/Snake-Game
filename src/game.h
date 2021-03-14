#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "boundary.h"
#include "spl_food.h"
class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, std::size_t kmsperframe);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  ~Game();
 private:
  Snake snake;
  SDL_Point food;
  Boundary *boundary;
  Spl_food *spl_food;//Object for Special food
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  int no_frm_spl_actv;//clock for spl food
  int frm_ctr{0};//frm_ctr for spl food
  int int_score{0};//intermediate score
  void PlaceFood();
  void PlaceSplFood();
  void Update();
};

#endif