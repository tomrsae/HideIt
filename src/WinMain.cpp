#include "ExtProcess.h"

LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
void OnKeyDown(WPARAM);
void RegisterHotkeys(HWND&);
void ResetExtProcess();

HideIt::ExtProcess extProcess = HideIt::ExtProcess();

enum KeyID {
	ONE		= 1,
	TWO		= 2,
	THREE	= 3,
	FOUR	= 4,
	FIVE	= 5,
	SIX		= 6
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("HideIt");

	HWND		hwnd;
	MSG			msg;
	WNDCLASS	wndclass;

	wndclass.lpfnWndProc = MainWndProc;
	wndclass.hInstance = hInstance;
	wndclass.lpszClassName = szAppName;

	RegisterClass(&wndclass);

	hwnd = CreateWindow(szAppName,
		TEXT("Hide-It"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hwnd, SW_HIDE);
	UpdateWindow(hwnd);

	RegisterHotkeys(hwnd);
	MessageBox(hwnd, "Hide-It is now open. Use 'CTRL + SHIFT + I' to see keybinds.", "Hide-It", MB_OK | MB_ICONINFORMATION);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (msg.message == WM_HOTKEY)
		{
			OnKeyDown(msg.wParam);
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

void OnKeyDown(WPARAM wParam)
{
	int exitConfirmation = 0;

	switch (wParam)
	{
	case KeyID::ONE:		// BIND PROCESS
		ResetExtProcess();
		extProcess = HideIt::ExtProcess(GetForegroundWindow());
		return;
	case KeyID::TWO:		// DECREASE OPACITY
		extProcess.decreaseOpacity();
		return;
	case KeyID::THREE:		// INCREASE OPACITY
		extProcess.increaseOpacity();
		return;
	case KeyID::FOUR:		// HIDE
		extProcess.toggleHide();
		return;
	case KeyID::FIVE:
		exitConfirmation = MessageBox(NULL, "Are you sure you want to exit Hide-It?", "Terminate Process?", MB_YESNOCANCEL);

		if (exitConfirmation == IDYES)
			exit(0);
		return;
	case KeyID::SIX:
		MessageBox(
			NULL,
			"Hide-It is active.\nThis software requires you to bind a process before doing actions to it. Please refer to the keybinds below.\n\nKeybinds:\nCTRL + |: Binds new process\n|: Decreases opacity\nSHIFT + |: Increases opacity\nALT + |: Hides/Shows process, as well as taskbar icon\nCTRL + SHIFT + |: Terminates Hide-It",
			"Hide-It Keybinds",
			MB_OK | MB_ICONINFORMATION);
		return;

	default:	// Do nothing if any other key is pressed
		return;
	}
}

void RegisterHotkeys(HWND &programProcess)
{
	// Functionality Hotkeys
	RegisterHotKey(programProcess, KeyID::ONE, MOD_CONTROL | MOD_NOREPEAT, 0xDC);				// CTRL + |
	RegisterHotKey(programProcess, KeyID::TWO, MOD_NOREPEAT, 0xDC);								// |
	RegisterHotKey(programProcess, KeyID::THREE, MOD_SHIFT | MOD_NOREPEAT, 0xDC);				// SHIFT + |
	RegisterHotKey(programProcess, KeyID::FOUR, MOD_ALT | MOD_NOREPEAT, 0xDC);					// ALT + |
	RegisterHotKey(programProcess, KeyID::FIVE, MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT, 0xDC);	// CTRL + SHIFT + |

	// UI Hotkey
	RegisterHotKey(programProcess, KeyID::SIX, MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT, 0x49);	// CTRL + SHIFT + I
}

void ResetExtProcess()
{
	if (extProcess.isHidden())
	{
		extProcess.toggleHide();
	}

	if (extProcess.getOpacity() != 100)
	{
		extProcess.resetOpacity();
	}
}