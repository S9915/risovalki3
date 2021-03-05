#include <windows.h>
#include <math.h>
#include <tchar.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");

int APIENTRY WinMain(HINSTANCE This, HINSTANCE Prev, LPSTR cmd, int mode)
{
	HWND hWnd;
	MSG msg;
	WNDCLASS wc;

	wc.hInstance = This;
	wc.lpszClassName = WinName;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	if (!RegisterClass(&wc)) return 0;
	hWnd = CreateWindow(WinName, _T("Каркас Windows-приложения"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		HWND_DESKTOP,
		NULL,
		This,
		NULL);
	ShowWindow(hWnd, mode);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	} return 0;
}

BOOL WINAPI Elipse(HDC hdc, int x1, int y1, int x2, int y2);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    POINT pt[5] = { {0,100},{-59,-81},{95,31},{-95,31},{59,-81} };
    const int WIDTH = 400;
    const int HEIGHT = 300;
    static int sx, sy, i, k;
    static HBRUSH hBrush1, hBrush2;
    HRGN hRgn;
    int a, b, x_scr, y_scr; //Экранные координаты
    double x, h; //Физические координаты
    switch (message)
    {

    case WM_PAINT:
        hBrush1 = CreateSolidBrush(RGB(255, 0, 0));//Создание кисти
        hBrush2 = CreateSolidBrush(RGB(255, 255, 255));//Создание кисти
        hdc = BeginPaint(hWnd, &ps);
        //Установка режима
        SetMapMode(hdc, MM_ANISOTROPIC);
        //Установка логическиз размеров вывода, ось Y направлена вверх
        SetWindowExtEx(hdc, WIDTH, -HEIGHT, NULL);
        //Установка физических размеров окна
        SetViewportExtEx(hdc, sx, sy, NULL);
        //Установка начала координат
        SetViewportOrgEx(hdc, sx / 2, sy / 2, NULL);
        BeginPath(hdc);
        Ellipse(hdc, 100, 100, -100, -100);
        CloseFigure(hdc);
        EndPath(hdc);
        SelectObject(hdc, hBrush1);
        FillPath(hdc);

        BeginPath(hdc);
        Ellipse(hdc, 50, 50, -50, -50);
        CloseFigure(hdc);
        EndPath(hdc);
        SelectObject(hdc, hBrush2);
        SetPolyFillMode(hdc, WINDING);//Режим закрашивания "вся фигура"
        FillPath(hdc);
        EndPaint(hWnd, &ps);
        break;
    case WM_SIZE:
        sx = LOWORD(lParam);
        sy = HIWORD(lParam);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default: return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}