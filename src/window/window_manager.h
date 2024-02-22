/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */
#ifndef WINDOW_WINDOW_MANAGER_H_
#define WINDOW_WINDOW_MANAGER_H_
#include "../utils/macros.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <SDL2/SDL_ttf.h>

class WindowManager {

public:
  int m_width, m_height;

  HWND m_hwnd;

  SDL_Window *m_window;
  SDL_Renderer *m_renderer;

  bool create();

  bool make_window_transparent(SDL_Window *window, COLORREF color_key);

  TTF_Font *load_font(const char *file_name, int font_size);

  void send_events(HWND hwnd, int x, int y);

  bool set_window_transparency(COLORREF color);

  bool should_close(SDL_Event *event);

  void draw_rect(int x, int y, int w, int h, SDL_Color color);

  void cleanup();
};

#endif // WINDOW_WINDOW_MANAGER_H_