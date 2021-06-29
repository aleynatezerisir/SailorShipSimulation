#include <windows.h>  
#include <algorithm>
#include <time.h>
#include <stdio.h>
#include "chmat.h"
using namespace std;


#define IDI_ICON1 101
#define IDC_OPEN	3000
#define IDC_BUTTON1 3001
#define IDC_BUTTON2 3002
#define IDC_BUTTON3 3003
#define NUMBER_OF_SEMAPHORES 3
#define NUMBER_OF_THREAD 9

HINSTANCE hInst;   // current instance
HWND     hWnd, hEdit, HButton1, HButton2, HButton3, Hmainbmp;    //parent window
LPCTSTR lpszAppName = "GEN32";
LPCTSTR lpszTitle = "GENERIC32";
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HANDLE ghSemaphore;

int Arr_Left_cord[9][2];
int Arr_Left[9];
int Arr_Left_Goingto[3];

int Arr_Right_cord[9][2];
int Arr_Right[9];
int Arr_Right_Goingto[3];

int Arr_Center_cord[3][2];
int Arr_Center[3];


DWORD WINAPI myThread(LPVOID lpParam)
{
	CHMAT& m = *((CHMAT*)lpParam);
	DWORD dwWaitResult = WaitForSingleObject(ghSemaphore, INFINITE);
	while (true)
	{
		random_shuffle(begin(Arr_Left), end(Arr_Left));
		random_shuffle(begin(Arr_Right), end(Arr_Right));
		int b = 0;
		for (int s = 0; s < 9; s++) {
			m.printnumber(Arr_Left_cord[s][0], Arr_Left_cord[s][1], Arr_Left[s], 0x00ff0000, 0x000000);
		}
		for (int s = 0; s < 9; s++) {
			m.printnumber(Arr_Right_cord[s][0], Arr_Right_cord[s][1], Arr_Right[s], 0x00ff0000, 0x000000);
		}
		Sleep(350);
	}
	ReleaseSemaphore(ghSemaphore, 1, NULL);

	return true;
}

void LeftVSCenter() {
	int memory[3];
	memory[0] = Arr_Center[0];
	memory[1] = Arr_Center[1];
	memory[2] = Arr_Center[2];

	for (int k = 0; k < 3; k++) {
		Arr_Center[k] = 0;
	}

	int count = 0;

	if (count < 3 && Arr_Left[5] != 0)
	{
		Arr_Center[count] = Arr_Left[5];
		Arr_Left[5] = 0;
		count++;
	}
	if (count < 3 && Arr_Left[2] != 0)
	{
		Arr_Center[count] = Arr_Left[2];
		Arr_Left[2] = 0;
		count++;
	}
	if (count < 3 && Arr_Left[8] != 0)
	{
		Arr_Center[count] = Arr_Left[8];
		Arr_Left[8] = 0;
		count++;
	}

	if (count < 3 && Arr_Left[4] != 0)
	{
		Arr_Center[count] = Arr_Left[4];
		Arr_Left[4] = 0;
		count++;
	}
	if (count < 3 && Arr_Left[1] != 0)
	{
		Arr_Center[count] = Arr_Left[1];
		Arr_Left[1] = 0;
		count++;
	}
	if (count < 3 && Arr_Left[7] != 0)
	{
		Arr_Center[count] = Arr_Left[7];
		Arr_Left[7] = 0;
		count++;
	}

	if (count < 3 && Arr_Left[3] != 0)
	{
		Arr_Center[count] = Arr_Left[3];
		Arr_Left[3] = 0;
		count++;
	}
	if (count < 3 && Arr_Left[0] != 0)
	{
		Arr_Center[count] = Arr_Left[0];
		Arr_Left[0] = 0;
		count++;
	}
	if (count < 3 && Arr_Left[6] != 0)
	{
		Arr_Center[count] = Arr_Left[6];
		Arr_Left[6] = 0;
		count++;
	}

	for (int i = 0; i < 3; i++) {
		if (memory[i] != 0) {
			for (int j = 0; j < 9; j++) {
				if (Arr_Left[j] == 0) {
					Arr_Left[j] = memory[i];
					break;
				}
			}
		}
	}
}

void RightVSCenter() {
	int memory[3];
	memory[0] = Arr_Center[0];
	memory[1] = Arr_Center[1];
	memory[2] = Arr_Center[2];

	for (int k = 0; k < 3; k++) {
		Arr_Center[k] = 0;
	}

	int count = 0;

	if (count < 3 && Arr_Right[3] != 0)
	{
		Arr_Center[count] = Arr_Right[3];
		Arr_Right[3] = 0;
		count++;
	}
	if (count < 3 && Arr_Right[0] != 0)
	{
		Arr_Center[count] = Arr_Right[0];
		Arr_Right[0] = 0;
		count++;
	}
	if (count < 3 && Arr_Right[6] != 0)
	{
		Arr_Center[count] = Arr_Right[6];
		Arr_Right[6] = 0;
		count++;
	}
	if (count < 3 && Arr_Right[4] != 0)
	{
		Arr_Center[count] = Arr_Right[4];
		Arr_Right[4] = 0;
		count++;
	}
	if (count < 3 && Arr_Right[1] != 0)
	{
		Arr_Center[count] = Arr_Right[1];
		Arr_Right[1] = 0;
		count++;
	}
	if (count < 3 && Arr_Right[7] != 0)
	{
		Arr_Center[count] = Arr_Right[7];
		Arr_Right[7] = 0;
		count++;
	}
	if (count < 3 && Arr_Right[5] != 0)
	{
		Arr_Center[count] = Arr_Right[5];
		Arr_Right[5] = 0;
		count++;
	}
	if (count < 3 && Arr_Right[2] != 0)
	{
		Arr_Center[count] = Arr_Right[2];
		Arr_Right[2] = 0;
		count++;
	}
	if (count < 3 && Arr_Right[8] != 0)
	{
		Arr_Center[count] = Arr_Right[8];
		Arr_Right[8] = 0;
		count++;
	}

	for (int i = 0; i < 3; i++) {
		if (memory[i] != 0) {
			for (int j = 0; j < 9; j++) {
				if (Arr_Right[j] == 0) {
					Arr_Right[j] = memory[i];
					break;
				}
			}
		}
	}
}

void fillLeft() {
	srand(time(NULL));
	for (int i = 0; i < 9; i++) {
		bool a = true;
		if (i == 0) Arr_Left[i] = rand() % 9 + 1;
		while (a == true && i != 0) {
			Arr_Left[i] = rand() % 9 + 1;
			for (int j = 0; j < i; j++) {
				if (Arr_Left[i] == Arr_Left[j])
				{
					a = true;
					break;
				}
				else a = false;
			}
		}
	}
	for (int i = 0; i < 9; i++) {
		Arr_Right[i] = 0;
	}
	Arr_Right[1] = 7;
	Arr_Right[7] = 2;
	for (int i = 0; i < 3; i++) {
		Arr_Center[i] = 0;
	}
	//Arr_Left[4] = 0;
}

void setNumberCoordinates() {
	for (int i = 0; i < 9; i++)
	{
		if (i < 3) {
			Arr_Left_cord[i][0] = 250 + i * 30;  // X
			Arr_Left_cord[i][1] = 350;// Y
		}
		else if (i > 2 && i < 6)
		{
			Arr_Left_cord[i][0] = 250 + (i - 3) * 30;  // X
			Arr_Left_cord[i][1] = 320;  // Y
		}
		else
		{
			Arr_Left_cord[i][0] = 250 + (i - 6) * 30;  // X
			Arr_Left_cord[i][1] = 290;// Y
		}
	}
	for (int i = 0; i < 9; i++)
	{
		if (i < 3) {
			Arr_Right_cord[i][0] = 620 + i * 30;  // X
			Arr_Right_cord[i][1] = 350;// Y
		}
		else if (i > 2 && i < 6)
		{
			Arr_Right_cord[i][0] = 620 + (i - 3) * 30;  // X
			Arr_Right_cord[i][1] = 320;  // Y
		}
		else
		{
			Arr_Right_cord[i][0] = 620 + (i - 6) * 30;  // X
			Arr_Right_cord[i][1] = 290;// Y
		}
	}
	Arr_Center_cord[0][0] = 360;
	Arr_Center_cord[0][1] = 320;

	Arr_Center_cord[1][0] = 380;
	Arr_Center_cord[1][1] = 320;

	Arr_Center_cord[2][0] = 400;
	Arr_Center_cord[2][1] = 320;

}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine, int nCmdShow)
{
	MSG      msg;
	WNDCLASSEX wc;
	HMENU MainMenu, FileMenu;
	MainMenu = CreateMenu();
	FileMenu = CreatePopupMenu();
	AppendMenu(FileMenu, MF_STRING, IDC_OPEN, "Open");
	AppendMenu(MainMenu, MF_POPUP, (UINT_PTR)FileMenu, "FILE");

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wc.lpszMenuName = lpszAppName;
	wc.lpszClassName = lpszAppName;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hIconSm = (HICON)LoadImage(hInstance, lpszAppName,
		IMAGE_ICON, 16, 16,
		LR_DEFAULTCOLOR);

	if (!RegisterClassEx(&wc))
		return(FALSE);

	hInst = hInstance;
	hWnd = CreateWindowEx(0, lpszAppName,
		lpszTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		1368, 768,
		NULL,
		MainMenu,
		hInstance,
		NULL
	);


	if (!hWnd)
		return(FALSE);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return(msg.wParam);
}




LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

	case WM_CREATE:
	{

		hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "Edit", "", WS_CHILD | WS_VISIBLE |
			ES_AUTOVSCROLL | ES_MULTILINE | ES_WANTRETURN | WS_VSCROLL, 1070, 25, 250, 250, hWnd, NULL, hInst, NULL);
		HButton1 = CreateWindowEx(NULL, "BUTTON", "BUTTON1", WS_CHILD | WS_VISIBLE | SS_CENTER,
			2, 2, 80, 20, hWnd, (HMENU)IDC_BUTTON1, hInst, NULL);
		HButton2 = CreateWindowEx(NULL, "BUTTON", "STOP", WS_CHILD | WS_VISIBLE | SS_CENTER,
			162, 2, 80, 20, hWnd, (HMENU)IDC_BUTTON2, hInst, NULL);
		Hmainbmp = CreateWindowEx(NULL, "STATIC", "", WS_CHILD | WS_VISIBLE | SS_BITMAP | WS_THICKFRAME, 1, 23, 600, 500, hWnd, NULL, hInst, NULL);
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_OPEN:
		{
			OPENFILENAME ofn;

			char szFile[260];
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hWnd;
			ofn.lpstrFile = szFile;
			//
			// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
			// use the contents of szFile to initialize itself.
			//
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = NULL;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			GetOpenFileName(&ofn);
		}
		break;
		case IDC_BUTTON1:
		{
			CHMAT m(800, 700, CHMAT_INT);
			fillLeft();
			setNumberCoordinates();
			ghSemaphore = CreateSemaphore(
				NULL,
				NUMBER_OF_SEMAPHORES,
				NUMBER_OF_THREAD,
				NULL
			);
			using namespace std;
			unsigned int myCounter = 0;
			DWORD myThreadID;
			HANDLE myHandle = CreateThread(0, 0, myThread, &m, 0, &myThreadID);
			Rectangle(m, 330, 200, 10, 250, 0x00ff0000, true);
			Rectangle(m, 600, 200, 10, 250, 0x00ff0000, true);
			Rectangle(m, 350, 200, 240, 250, 0x00ffee, true);

			for (int i = 0; i < 160; i++)
			{
				Rectangle(m, 350, 200, 240, 250, 0x00ffee, true);
				Rectangle(m, 350 + i, 305, 80, 40, 0x00ff0000, true);
				for (int s = 0; s < 3; s++) {
					m.printnumber(Arr_Center_cord[s][0] + i, Arr_Center_cord[s][1], Arr_Center[s], 0x000000, 0x00ff0000);
				}
				SendMessage(Hmainbmp, STM_SETIMAGE, 0, (LPARAM)m.HBitmap);
				Sleep(10);
				if (i == 159)
				{
					RightVSCenter();
					for (int j = 0; j < 150; j++)
					{
						Rectangle(m, 350, 200, 240, 250, 0x00ffee, true);
						Rectangle(m, 500 - j, 305, 80, 40, 0x00ff0000, true);
						for (int s = 2; s > -1; s--) {
							m.printnumber(Arr_Center_cord[s][0] + 150 - j, Arr_Center_cord[s][1], Arr_Center[s], 0x000000, 0x00ff0000);
						}
						SendMessage(Hmainbmp, STM_SETIMAGE, 0, (LPARAM)m.HBitmap);
						Sleep(10);
					}
					LeftVSCenter();
					i = 0;
				}
			}
		}

		break;
		case IDC_BUTTON2: {
			exit(-1);
		}

		default:
			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return(DefWindowProc(hWnd, uMsg, wParam, lParam));
	}

	return(0L);
}

