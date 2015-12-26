//�������� ������� �� ������ ����� ������ ���� �����������
//��������� ����, � ��������� �������� ���������� ���������� ����� ����.
//��� ��������� ������� ����������� ��� ���� ���� � ���������������
//����������(�������� 7 ����).���� ������ ���� ����������� ��������
//��� ������� ������� ���� ������ ����������� � �������� �������.

#include "stdafx.h"
#include "Win32.h"
#include "Resource.h"
#include <time.h>

#define MAX_LOADSTRING 100
#define ID_FIRSTCHILD	100
#define ID_SECONDCHILD	101
#define ID_THIRDCHILD	102

// ���������� ����������:
HINSTANCE hInst;									// ������� ���������
WCHAR szTitle[MAX_LOADSTRING];						// ����� ������ ���������
WCHAR szWindowClass[MAX_LOADSTRING];				// ��� ������ �������� ����
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildProc(HWND, UINT, WPARAM, LPARAM);
HWND hmain;
HWND mass_p[7];
int counter;
wchar_t name;

// ��������� ���������� �������, ���������� � ���� ������ ����:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	srand(time(NULL));
	// TODO: ���������� ��� �����.

	// ������������� ���������� �����
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WIN32, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ��������� ������������� ����������:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32));

	MSG msg;

	// ���� ��������� ���������:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

//  �������: MyRegisterClass()
//  ����������: ������������ ����� ����.
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WIN32);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	return RegisterClassExW(&wcex);
}
//   �������: InitInstance(HINSTANCE, int)
//   ����������: ��������� ��������� ���������� � ������� ������� ����.
//   �����������:
//   � ������ ������� ���������� ���������� ����������� � ���������� ����������, � �����
//    ��������� � ��������� �� ����� ������� ���� ���������.
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // ��������� ���������� ���������� � ���������� ����������

	hmain = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hmain)
	{
		return FALSE;
	}

	ShowWindow(hmain, nCmdShow);
	UpdateWindow(hmain);

	return TRUE;
}

//  �������: WndProc(HWND, UINT, WPARAM, LPARAM)
//  ����������:  ������������ ��������� � ������� ����.
//  WM_COMMAND � ���������� ���� ����������
//  WM_PAINT � ���������� ������� ����
//  WM_DESTROY � ��������� ��������� � ������ � ���������

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// ��������� ����� � ����:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: �������� ���� ����� ��� ����������, ������������ HDC...
		EndPaint(hWnd, &ps);
		SetWindowText(hWnd, L"1");
	}
	break;

	case WM_DESTROY:
		if (hWnd == hmain)
		{
			PostQuitMessage(0);
		}
		else
		{
			DestroyWindow(hWnd);
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);

	case WM_MOUSEMOVE:
	{
		int new_x = rand() % 1066;
		int new_y = rand() % 478;
		int Width = rand() % 100 + 200;
		int Height = rand() % 100 + 200;
		MoveWindow(hWnd, new_x, new_y, Width, Height, TRUE);
	}
	break;

	case WM_CLOSE:
	{
		if (IDOK == MessageBox(hWnd, L"Exit programm?", L"Close",
			MB_OKCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2))
			SendMessage(hWnd, WM_DESTROY, NULL, NULL);
	}
	break;

	case WM_LBUTTONUP:
	{
		if (counter < 7)
		{
			mass_p[counter] = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInst, nullptr);
			ShowWindow(mass_p[counter], 1);
			counter++;
		}
	}

	break;
	case WM_RBUTTONUP:
	{
		SetWindowText(hWnd, L"Changed Title");
	}
	case  WM_CHAR:
	{
		if (counter > 0)
		{
			DestroyWindow(mass_p[counter - 1]);
			counter--;
		}
	}
	break;
	}
	return 0;
}

// ���������� ��������� ��� ���� "� ���������".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
