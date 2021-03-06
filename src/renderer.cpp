#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}


Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food , Boundary *boundary , Spl_food const *spl_food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;//width = 
  block.h = screen_height / grid_height;//height = 20 pix
  SDL_Rect block1;
  block1.w = screen_width;//width = 640pix
  block1.h = screen_height / grid_height;//height = 20 pix
  SDL_Rect block2;
  block2.w = screen_width / grid_width;//width = 20pix
  block2.h = screen_height;//height = 640 pix
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  SDL_SetRenderDrawColor(sdl_renderer, 0xC0, 0xC0, 0xC0, 0xFF);
  //draw 1st row
  block1.x = boundary->Lft_col();
  block1.y = boundary->Top_row();
  SDL_RenderFillRect(sdl_renderer, &block1);
  //draw 2nd row
  block1.x = boundary->Lft_col();
  block1.y = (boundary->Bot_row()) * (block1.h);
  SDL_RenderFillRect(sdl_renderer, &block1);  
  //draw 1st column
  block2.x = boundary->Lft_col();
  block2.y = boundary->Top_row();
  SDL_RenderFillRect(sdl_renderer, &block2);
  //draw  2nd column
  block2.x = (boundary->Rgt_col()) * (block2.w);
  block2.y = boundary->Top_row();
  SDL_RenderFillRect(sdl_renderer, &block2);
  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);
  //Render Spl food
  if(spl_food->exists == true){
      SDL_SetRenderDrawColor(sdl_renderer, 0xCC, 0x00, 0x66, 0xFF);
  block.x = spl_food->x * block.w;
  block.y = spl_food->y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);}
  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
