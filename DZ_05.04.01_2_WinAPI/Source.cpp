#include<Windows.h>
#include<tchar.h>

static TCHAR WindowsClass[] = L"win32app";
static TCHAR Title[] = L"MyApp";
HINSTANCE hinst;

#define ID_BUTTON1 1001
#define ID_EDIT1 1002
#define ID_EDIT2 1003

HWND button1, edit1, edit2;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hinstance;
	wcex.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	/*wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);*/
	wcex.hbrBackground = CreateSolidBrush(RGB(150, 70, 150));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = WindowsClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, L"Call faild!", L"MyApp", NULL);
		return 1;
	}

	hinst = hinstance;

	HWND hWnd = CreateWindow(
		WindowsClass,
		Title,
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		800,
		500,
		NULL,
		NULL,
		hinst,
		NULL);

	if (!hWnd)
	{
		MessageBox(NULL, L"Create window faild!", L"MyApp", NULL);
		return 1;
	}
	SetTimer(hWnd, 1, 100, NULL);
	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return(int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;
	TCHAR text1[50];
	TCHAR text2[50];
	TCHAR temp[50];
	
	switch (message)
	{

	case WM_COMMAND:

	case BN_CLICKED:
	
		if (LOWORD(wParam) == ID_BUTTON1)
		{
			SendMessage(edit1, WM_GETTEXT, sizeof(text1), (LPARAM)text1);
			SendMessage(edit2, WM_GETTEXT, sizeof(text2), (LPARAM)text2);
			wcscpy_s(temp, 49, text1);
			SendMessage(edit1, WM_SETTEXT, sizeof(text2), (LPARAM)text2);
			SendMessage(edit2, WM_SETTEXT, sizeof(temp), (LPARAM)temp);
			MessageBox(hWnd, L"Заменено", L"", MB_OK);
		}

		

		break;

	case WM_CREATE:
				
		edit1 = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			L"edit",
			L"",
			WS_CHILD | WS_VISIBLE,
			10,		/*координаты по X*/
			10,								/*координаты по Y*/
			500,				/*Ширина окошка*/
			20,
			hWnd,
			(HMENU)ID_EDIT1,
			hinst,
			NULL);

		edit2 = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			L"edit",
			L"",
			WS_CHILD | WS_VISIBLE,
			10,		/*координаты по X*/
			40,								/*координаты по Y*/
			500,				/*Ширина окошка*/
			20,
			hWnd,
			(HMENU)ID_EDIT1,
			hinst,
			NULL);


		button1 = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			L"button",
			L"Заменить",
			WS_CHILD | WS_VISIBLE,
			10,		/*координаты по X*/
			80,						/*координаты по Y*/
			80,						/*Ширина окошка*/
			25,
			hWnd,
			(HMENU)ID_BUTTON1,
			hinst,
			NULL);

		

		break;

	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}