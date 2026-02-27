#include "Application.h"

namespace yggdrasil
{
CApplication::CApplication(HINSTANCE hInstance, int showCmd)
  : m_hwnd(nullptr)
  , m_hInstance(hInstance)
  , m_showCmd(showCmd)
{
}

common::TResult CApplication::Initialize(common::TWindowData& windowData, rhi::EBackend backend)
{
  common::TResult result = InitializeWindow(windowData);

  if (result.IsError())
    return result;

  windowData.m_hwnd = m_hwnd;

  m_pRHI = rhi::CreateInstance(backend);

  if (m_pRHI == nullptr)
    return ERROR_RESULT("Can't create RHI instance");

  result = m_pRHI->Initialize(windowData);

  rhi::TVertexShaderDesc desc;
  desc.m_filename = "VS_StaticMesh.cso";

  std::unique_ptr<rhi::IVertexShader> vertexShader;
  result = m_pRHI->CreateVertexShader(desc, vertexShader);

  rhi::TInputLayoutDesc inputDesc{};
  inputDesc.m_vertexType = rhi::EVertexType::StaticMesh;

  std::unique_ptr<rhi::IInputLayout> inputLayout;
  result = m_pRHI->CreateInputLayout(inputDesc, vertexShader.get(), inputLayout);

  return result;
}

//static
LRESULT CALLBACK CApplication::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
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

common::TResult CApplication::InitializeWindow(const common::TWindowData& windowData)
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
    windowData.m_width,
    windowData.m_height,
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

int CApplication::Start() {

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

void CApplication::Stop() const
{
  DestroyWindow(m_hwnd);
}

void CApplication::Render()
{
  m_timer.Update();

  float deltaTime = m_timer.GetDeltaTime();
}

HWND CApplication::GetHwnd() const
{
  return m_hwnd;
}

HINSTANCE CApplication::GetHInstance() const
{
  return m_hInstance;
}
}