#include "Window.h"

namespace yggdrasil
{
namespace app
{
CWindow::CWindow(common::TWindowData& windowData, std::function<void()> renderCallback)
  : m_windowData(windowData)
  , m_renderCallback(renderCallback)
{
}

common::TResult CWindow::Initialize()
{
  LPCTSTR wndClassName = TEXT("application");

  WNDCLASSEX wc{};

  wc.cbSize        = sizeof(WNDCLASSEX);
  wc.style         = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc   = WndProc;
  wc.cbClsExtra    = NULL;
  wc.cbWndExtra    = NULL;
  wc.hInstance     = m_windowData.m_hinstance;
  wc.hIcon         = LoadIcon(NULL, IDI_WINLOGO);
  wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wc.lpszMenuName  = NULL;
  wc.lpszClassName = wndClassName;
  wc.hIconSm       = LoadIcon(NULL, IDI_WINLOGO);

  if (!RegisterClassEx(&wc))
  {
    return ERROR_RESULT("Error registering class");
  }

  m_windowData.m_hwnd = CreateWindowEx(
    NULL,
    wndClassName,
    TEXT("Yggdrasil"),
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT,
    m_windowData.m_width,
    m_windowData.m_height,
    NULL,
    NULL,
    m_windowData.m_hinstance,
    NULL
  );

  if (!m_windowData.m_hwnd)
  {
    return ERROR_RESULT("Error creating window");
  }

  ShowWindow(m_windowData.m_hwnd, m_windowData.m_showCmd);
  UpdateWindow(m_windowData.m_hwnd);

  return common::TResult();
}

void CWindow::DoWindowMessageLoop()
{
  MSG msg;
  ZeroMemory(&msg, sizeof(MSG));

  while (true)
  {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
      {
        break;
      }

      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else
    {
      m_renderCallback();
    }
  }
}

void CWindow::Destroy() const
{
  DestroyWindow(m_windowData.m_hwnd);
}

//static
LRESULT CALLBACK CWindow::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch (msg)
  {
    case WM_KEYDOWN:
    {
      //CKeyboard::OnKeyDown((unsigned int)wParam);
      break;
    }
    case WM_KEYUP:
    {
      //CKeyboard::OnKeyUp((unsigned int)wParam);
      break;
    }
    case WM_DESTROY:
    {
      PostQuitMessage(0);
      return 0;
    }
  }

  return DefWindowProc(hwnd, msg, wParam, lParam);
}
}
}