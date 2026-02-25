#include "Engine.h"

namespace yggdrasil
{
CEngine::CEngine(HINSTANCE hInstance, int showCmd)
  : m_hwnd(nullptr)
  , m_hInstance(hInstance)
  , m_showCmd(showCmd)
{
}

common::TResult CEngine::Initialize(rhi::EFramework framework)
{
  common::TResult result = InitializeWindow();

  if (result.IsError())
    return result;

  return Initialize3DFramework(framework);
}

//static
LRESULT CALLBACK CEngine::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
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

common::TResult CEngine::InitializeWindow()
{
  LPCTSTR wndClassName = TEXT("mainwindow");

  WNDCLASSEX wc{};

  wc.cbSize        = sizeof(WNDCLASSEX);
  wc.style         = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc   = WndProc;
  wc.cbClsExtra    = NULL;
  wc.cbWndExtra    = NULL;
  wc.hInstance     = m_hInstance;
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

  m_hwnd = CreateWindowEx(
    NULL,
    wndClassName,
    TEXT("Yggdrasil"),
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT,
    common::WIDTH,
    common::HEIGHT,
    NULL,
    NULL,
    m_hInstance,
    NULL
  );

  if (!m_hwnd)
  {
    return ERROR_RESULT("Error creating window");
  }

  ShowWindow(m_hwnd, m_showCmd);
  UpdateWindow(m_hwnd);

  return common::TResult();
}

common::TResult CEngine::Initialize3DFramework(rhi::EFramework framework)
{
  return common::TResult();
}

int CEngine::Start() {

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
      Render();
    }
  }

  return (int)msg.wParam;
}

void CEngine::Stop() const
{
  DestroyWindow(m_hwnd);
}

void CEngine::Render()
{
}

HWND CEngine::GetHwnd() const
{
  return m_hwnd;
}

HINSTANCE CEngine::GetHInstance() const
{
  return m_hInstance;
}
}