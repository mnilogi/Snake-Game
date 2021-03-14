#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height,std::size_t kmsperframe)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(1, static_cast<int>(grid_width) - 1),//setting the range of column/row in acc to the boundary
      random_h(1, static_cast<int>(grid_height) - 1){
  boundary = new Boundary();
  spl_food = new Spl_food();
  //initialize boundary
  boundary->Top_row(0);//coordinates
  boundary->Bot_row(grid_height - 1);
  boundary->Lft_col(0);
  boundary->Rgt_col(grid_width - 1);
  PlaceFood();
  no_frm_spl_actv = 10000 / kmsperframe;//Total no of frames required to count 10s
}
Game::~Game()
{
  delete boundary;
  delete spl_food;
}
void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food ,boundary, spl_food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y) && !boundary->BoundaryCell(x, y) && !(x == spl_food->x && y == spl_food->y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::PlaceSplFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y) && !boundary->BoundaryCell(x, y) && !(food.x == x && y == food.y)) {
      spl_food->x = x;
      spl_food->y = y;
      spl_food->exists = true;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update(boundary);//also make sure snake doesnt touch the boundary otherwise it would die

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    int_score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
  if(spl_food->x == new_x && new_y == spl_food->y && spl_food->exists == true)
  {
    score += 5;
    frm_ctr = 0;
    spl_food->exists = false;
    int_score = 0;
    snake.GrowBody();
  }
  //check if score is multiple of 10
  if(int_score > 0 && int_score % 5 == 0 && spl_food->exists == false)
  {
    PlaceSplFood();
  }
  //check the frm_ctr value
  if(spl_food->exists == true)
    frm_ctr++;
  if(frm_ctr == no_frm_spl_actv)
  {
    spl_food->exists = false;
    frm_ctr = 0;
    int_score = 0;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }