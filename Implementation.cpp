#include "Header.h"

void Go(int x, int y)
{
	static HANDLE  h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { short(x), short(y) };
	SetConsoleCursorPosition(h, c);
}

void SetTextAttribute(int k)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);
}

void SetWindowSize(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);

								
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void DrawBorder(int x, int y, int width, int height, int color, string textinbutton)
{
	SetTextAttribute(color);
	Go(x - width, y - width);
	cout << char(218);

	for (int i = 0; i < height; i++)
		cout << char(196);
	cout << char(191);

	for (int i = 1 - width; i <= width - 1; i++)
	{
		Go(x - width, y + i);
		cout << char(179);
	}

	Go(x - width, y + width);
	cout << char(192);

	for (int i = 0; i < height; i++)
		cout << char(196);
	cout << char(217);

	for (int i = 1 - width; i <= width - 1; i++)
	{
		Go(x + height + 1 - width, y + i);
		cout << char(179);
	}

	int center = (height - textinbutton.length()) / 2;
	Go(x + center, y);
	cout << textinbutton;
}

status Key(char a)
{
	a = _getch();
	switch (a)
	{
	case 72: return UP;
	case 75: return LEFT;
	case 77: return RIGHT;
	case 80: return DOWN;
	case 13: return ENTER;
	case 27: return ESC;
	case 9: return TAB;
	case 32: return SPACE;
	case 115: return SAVE;
	}
	return TRASH;
}