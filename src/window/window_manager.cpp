/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */
#include "window_manager.h"

// TODO: better error solutions
bool WindowManager::create() {

  HWND target_window = FindWindowA(NULL, WINDOW_NAME);

  if (!target_window)
    return false;

  this->m_hwnd = target_window;
  this->m_width = GetSystemMetrics(SM_CXSCREEN);
  this->m_height = GetSystemMetrics(SM_CYSCREEN);

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SPDLOG_ERROR("Failed to initialize SDL: {}", SDL_GetError());
    return false;
  }

  m_window = SDL_CreateWindow("Infestation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_VULKAN);

  if (!m_window) {
    SPDLOG_ERROR("Failed to create SDL window: {}", SDL_GetError());
    return false;
  }

  m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

  if (!m_renderer) {
    SPDLOG_ERROR("Failed to create SDL renderer: {}", SDL_GetError());
    return false;
  }

  return true;
}

bool WindowManager::make_window_transparent(SDL_Window *window, COLORREF color_key) {
  SDL_SetRenderDrawColor(m_renderer, 255, 0, 255, 255);
  SDL_RenderClear(m_renderer);
  SDL_SysWMinfo wmInfo;
  SDL_VERSION(&wmInfo.version);
  SDL_GetWindowWMInfo(window, &wmInfo);
  HWND hWnd = wmInfo.info.win.window;

  SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);

  return SetLayeredWindowAttributes(hWnd, color_key, 0, LWA_COLORKEY);
}

TTF_Font *WindowManager::load_font(const char *file_name, int font_size) {

  TTF_Font *font = TTF_OpenFont(file_name, font_size);
  if (!font)
    SPDLOG_ERROR("FAILED TO LOAD FONT {}", TTF_GetError());

  return font;
}

void WindowManager::send_events(HWND hwnd, int x, int y) {
  LPARAM params = MAKELPARAM(x, y);
  // sample test
  SendMessage(hwnd, WM_LBUTTONDOWN, MK_LBUTTON, params);
  SendMessage(hwnd, WM_LBUTTONUP, 0, params);
}

bool WindowManager::set_window_transparency(COLORREF color) {

  SDL_SysWMinfo wmInfo;
  SDL_VERSION(&wmInfo.version);
  SDL_GetWindowWMInfo(this->m_window, &wmInfo);
  HWND target_hwnd = wmInfo.info.win.window;

  SetWindowLong(target_hwnd, GWL_EXSTYLE, GetWindowLong(target_hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);

  return SetLayeredWindowAttributes(target_hwnd, color, 0, LWA_COLORKEY);
}

bool WindowManager::should_close(SDL_Event *event) {

  bool quit = false;

  while (SDL_PollEvent(event) != 0) {
    if (event->type == SDL_QUIT) {
      quit = true;
    }
  }
  return quit;
}

void WindowManager::draw_rect(int x, int y, int w, int h, SDL_Color color) {
  SDL_Rect rect = {x, y, w, h};

  SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);

  SDL_RenderFillRect(this->m_renderer, &rect);
  //SDL_RenderDrawRect(this->m_renderer, &rect);
}

void WindowManager::cleanup() {
  if (m_renderer) {
    SDL_DestroyRenderer(m_renderer);
    m_renderer = nullptr;
  }

  if (m_window) {
    SDL_DestroyWindow(m_window);
    m_window = nullptr;
  }

  SDL_Quit();
}