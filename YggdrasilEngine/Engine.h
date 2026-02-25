#pragma once

#include "EngineGlobals.h"

namespace yggdrasil
{
class CEngine
{
public:

  CEngine(HINSTANCE hInstance, int showCmd);
  virtual ~CEngine() = default;

  CEngine(const CEngine&) = delete;

  TResult Initialize(EFramework Renderer);
  void Render();
  int Start();
  void Stop() const;

  HWND GetHwnd() const;
  HINSTANCE GetHInstance() const;

private:

  TResult InitializeWindow();
  TResult Initialize3DFramework(EFramework framework);

  static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

  HWND m_hwnd;
  HINSTANCE m_hInstance;
  int m_showCmd;
  //CTimer m_timer;
};
}