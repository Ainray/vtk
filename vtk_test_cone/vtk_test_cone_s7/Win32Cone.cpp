#include<windows.h>
#include"vtk_test.h"

static HANDLE hinst;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int PASCAL WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPSTR /* lpszCmdParam */, int nCmdShow)
{
  static char szAppName[] = "Win32Cone";
  HWND        hwnd ;
  MSG         msg ;
  WNDCLASS    wndclass ;

  if (!hPrevInstance)
  {
    wndclass.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wndclass.lpfnWndProc   = WndProc ;
    wndclass.cbClsExtra    = 0 ;
    wndclass.cbWndExtra    = 0 ;
    wndclass.hInstance     = hInstance;
    wndclass.hIcon         = LoadIcon(nullptr,IDI_APPLICATION);
    wndclass.hCursor       = LoadCursor (nullptr, IDC_ARROW);
    wndclass.lpszMenuName  = nullptr;
    wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndclass.lpszClassName = szAppName;
    RegisterClass (&wndclass);
  }

  hinst = hInstance;
  hwnd = CreateWindow ( szAppName,
                        "Draw Window",
                        WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        400,
                        480,
                        nullptr,
                        nullptr,
                        hInstance,
                        nullptr);
  ShowWindow (hwnd, nCmdShow);
  UpdateWindow (hwnd);
  while (GetMessage (&msg, nullptr, 0, 0))
  {
    TranslateMessage (&msg);
    DispatchMessage (&msg);
  }
  return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  static HWND ewin;
  static VTKCone *theVTKApp;

  switch (message)
  {
    case WM_CREATE:
    {
      ewin = CreateWindow("button","Exit",
                          WS_CHILD | WS_VISIBLE | SS_CENTER,
                          0,400,400,60,
                          hwnd,(HMENU)2,
                          (HINSTANCE)vtkGetWindowLong(hwnd,vtkGWL_HINSTANCE),
                          nullptr);
      theVTKApp = new VTKCone(hwnd);
      return 0;
    }

    case WM_COMMAND:
      switch (wParam)
      {
        case 2:
          PostQuitMessage (0);
          delete theVTKApp;
          theVTKApp = nullptr;
          break;
      }
      return 0;

    case WM_DESTROY:
      PostQuitMessage (0);
      delete theVTKApp;
      theVTKApp = nullptr;
      return 0;
  }
  return DefWindowProc (hwnd, message, wParam, lParam);
}

