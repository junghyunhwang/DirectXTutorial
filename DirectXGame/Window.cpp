#include "Window.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg) 
	{
	case WM_CREATE:
	{
		// Event fired when the window is created
		// collected here..
		Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
		// .. and then stored for later lookup
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
		window->setHWND(hwnd);
		window->onCreate();
		break;
	}
	case WM_DESTROY:
	{
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->onDestroy();
		::PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
}

bool Window::init()
{
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = L"MyWindowClass";
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;

	if (!RegisterClassEx(&wc))
	{
		return false;
	}

	mHwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"DirectX Application",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, NULL, this);

	if (!mHwnd)
	{
		return false;
	}

	ShowWindow(mHwnd, SW_SHOW);
	UpdateWindow(mHwnd);

	mIsRun = true;

	return true;
}

bool Window::broadcast()
{
	MSG msg;

	onUpdate();

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Sleep(0);

	return true;
}

bool Window::isRun()
{
	return mIsRun;
}

RECT Window::getClientWindowRect()
{
	RECT rc;
	GetClientRect(mHwnd, &rc);

	return rc;
}

void Window::setHWND(HWND hWnd)
{
	mHwnd = hWnd;
}

void Window::onDestroy()
{
	mIsRun = false;
}

bool Window::release()
{
	if (DestroyWindow(mHwnd))
	{
		return false;
	}

	return true;
}
