#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<tchar.h>
#include<string.h>
#define ID_DOWN 101
#define ID_COMBOBOX 102
char szAppName[] = ("Chast3Zadanie22");
HINSTANCE hInstance;
HDC hdc;
PAINTSTRUCT ps;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hWnd;
	WNDCLASSEX wc;
	MSG msg;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDC_ARROW);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(46, 139, 87));
	wc.lpszMenuName = 0;
	wc.lpszClassName = szAppName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&wc)) return FALSE;

	hWnd = CreateWindow(szAppName, "Chast3Zadanie22", WS_OVERLAPPEDWINDOW, 100, 100, 300, 530, (HWND)NULL, (HMENU)NULL,
		hInstance, (LPSTR)NULL);
	if (!hWnd) return FALSE;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return ((int)msg.wParam);
}
LPCSTR arr[10] = { "Строка 1", "Строка 2", "Строка 3" , "Строка 4" , "Строка 5" , "Строка 6" , "Строка 7" , "Строка 8" , "Строка 9", "Строка 10" };
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LPCSTR Buff;
	int i, k;
	static HWND hCombo, hButton, hPole;
	switch (uMsg) {
	case WM_CREATE:
		hdc = GetDC(hwnd);
		hButton = CreateWindow("Button", "Вниз", WS_VISIBLE | WS_CHILD | WS_BORDER, 130, 80, 70, 25, hwnd, (HMENU)ID_DOWN, hInstance, NULL);
		hCombo = CreateWindow("ComboBox", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST | CBS_HASSTRINGS, 10, 80, 100, 200, hwnd, (HMENU)ID_COMBOBOX, hInstance, NULL);
		for (i = 0; i < 10; i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 1, (LPARAM)arr[i]);
		}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_DOWN:
			i = SendMessage(hCombo, CB_GETCURSEL, 0, 0L);
			k = i + 1;
			Buff = arr[i];
			arr[i] = arr[i + 1];
			arr[i + 1] = Buff;
			SendMessage(hCombo, CB_RESETCONTENT, 0, 0L);
			for (i = 0; i < 10; i++)
			{
				SendMessage(hCombo, CB_ADDSTRING, 1, (LPARAM)arr[i]);
			}
			SendMessage(hCombo, CB_SETCURSEL, k, 0L);
			i = SendMessage(hCombo, CB_GETCURSEL, 0, 0L);
			if (i == 9) 
			{
				MessageBox(hCombo, LPCSTR("Строка последняя в списке, кнопка заблокирована"), NULL, MB_OK);
				EnableWindow(hButton, 0);
			}
			else EnableWindow(hButton, 1);
			return 0;
		case ID_COMBOBOX:
			if (HIWORD(wParam) == CBN_SELENDOK) {
				i = SendMessage(hCombo, CB_GETCURSEL, 0, 0L);
				if (i == 9) EnableWindow(hButton, 0);
				else EnableWindow(hButton, 1);
			}
		}

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}
