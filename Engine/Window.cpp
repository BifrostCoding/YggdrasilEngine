#include "Window.h"
#include <Common/Keyboard.h>

namespace yggdrasil
{
namespace app
{
CWindow::CWindow(common::TApplicationData& applicationData, std::function<void()> renderCallback)
  : m_applicationData(applicationData)
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
  wc.hInstance     = m_applicationData.m_hinstance;
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

  m_applicationData.m_hwnd = CreateWindowEx(
    NULL,
    wndClassName,
    TEXT("Yggdrasil"),
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT,
    m_applicationData.m_width,
    m_applicationData.m_height,
    NULL,
    NULL,
    m_applicationData.m_hinstance,
    NULL
  );

  if (!m_applicationData.m_hwnd)
  {
    return ERROR_RESULT("Error creating window");
  }

  ShowWindow(m_applicationData.m_hwnd, true);
  UpdateWindow(m_applicationData.m_hwnd);

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
  DestroyWindow(m_applicationData.m_hwnd);
}

//static
LRESULT CALLBACK CWindow::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch (msg)
  {
    case WM_KEYDOWN:
    {
      if (wParam == VK_ESCAPE)
      {
        PostQuitMessage(0);
        return 0;
      }

      input::CKeyboard::OnKeyDown((unsigned int)wParam);
      break;
    }
    case WM_KEYUP:
    {
      input::CKeyboard::OnKeyUp((unsigned int)wParam);
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