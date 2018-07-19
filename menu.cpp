#define _CRT_SECURE_NO_WARNINGS
#define WHITE 15
#define GREEN 2
#define RED 4
#define CYAN 3
#define YELLOW 14
#define LIGHTGREEN 10
#define LIGHTMAGNETA 13
#define LIGHTGRAY 7
#define DARKGRAY 8
#include <iostream>
#include <Windows.h>
#include <thread>
#include <conio.h>
#include <string>
#include <fstream>
#include <processthreadsapi.h>
#include <vector>
#pragma pack (push)
#pragma pack(1)
#pragma pack(pop)
enum status { UP, DOWN, LEFT, RIGHT, ENTER, ESC, TAB };
int lives = 2;
using namespace std;
void gotoxy(int x, int y)
{
	static HANDLE  h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

void setTextAttribute(int k)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);
}

void setWindowSize(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

								//MoveWindow(window_handle, x, y, width, height, redraw_window);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void drawborder(int x, int y, int width, int height, int color, string textinbutton)
{
	setTextAttribute(color);
	gotoxy(x - width, y - width);
	cout << char(218);	//  ┌

	for (int i = 0; i < height; i++)
		cout << char(196);	//  ─
	cout << char(191);	//  ┐

	for (int i = 1 - width; i <= width - 1; i++)
	{
		gotoxy(x - width, y + i);
		cout << char(179);	//  │ 
	}

	gotoxy(x - width, y + width);
	cout << char(192);

	for (int i = 0; i < height; i++)
		cout << char(196);	//  ─
	cout << char(217);	//  ┘

	for (int i = 1 - width; i <= width - 1; i++)
	{
		gotoxy(x + height + 1 - width, y + i);
		cout << char(179);	//  │ 
	}

	int center = (height - textinbutton.length()) / 2;
	gotoxy(x + center, y);
	cout << textinbutton;
}

status key(char a)
{
	if (a == -32 || a == 224)
	{
		a = _getch();
		switch (a)
		{
		case 72:return UP;
		case 75:return LEFT;
		case 77:return RIGHT;
		case 80:return DOWN;
		}
	}
	if (a == 13)
		return ENTER;
	if (a == 27)
		return ESC;
}

void drawgame(int x, int y, int width, int height, int color, string textinbutton)
{
	setTextAttribute(color);
	gotoxy(x - width, y - width);
	cout << char(201);	//  ┌

	for (int i = 0; i < height; i++)
		cout << char(205);	//  ─
	cout << char(187);	//  ┐

	for (int i = 1 - width; i <= width - 1; i++)
	{
		gotoxy(x - width, y + i);
		cout << char(186);	//  │ 
	}

	gotoxy(x - width, y + width);
	cout << char(200);

	for (int i = 0; i < height; i++)
		cout << char(205);	//  ─
	cout << char(188);	//  ┘

	for (int i = 1 - width; i <= width - 1; i++)
	{
		gotoxy(x + height + 1 - width, y + i);
		cout << char(186);	//  │ 
	}
	gotoxy(0, 3);
	cout << char(204);
	for (int i = 0; i < height; i++)
		cout << char(205);	//  ─
	gotoxy(height + 1, 3);
	cout << char(185);
	gotoxy(1, 1);
	cout << "LIVES: ";
	for (int i = 0; i < lives; i++)
	{
		cout << "A ";
	}
	int center = (height - textinbutton.length()) / 2;
	//gotoxy(x + center, y);
	gotoxy(center - 2, 1);
	cout << "CROSS THE ROAD";
}

void testscreen() {
	system("cls");
	setWindowSize(850, 600);
	drawgame(17, 17, 17, 100, LIGHTGREEN, " ");
}

void main()
{
	setWindowSize(900, 500);

	setTextAttribute(LIGHTMAGNETA);
	cout << "\n\n\n\n\n";
	cout << " ::::::  :::::::   ::::::   ::::::   ::::::  :::::::  ::::  :::  :::::: " << endl;
	cout << ":+:  :+: :+:  :+: :+:  :+: :+:  :+: :+:  :+:   :+:    :+:+  :+: :+:  :+:" << endl;
	cout << "+:+      +:+  +:+ +:+  +:+ +:+      +:+        +:+    :+:+  +:+ +:+      " << endl;
	cout << "+#+      +#+:+#:  +#+  +:+ +#++:+#+ +#++++#+   +#+    +#+++ +#+ :#:      " << endl;
	cout << "+#+      +#+  +#+ +#+  +#+      +#+      +#+   +#+    +#+  +#+# +#+ +#+#" << endl;
	cout << "#+#  #+# #+#  #+# #+#  #+# #+#  #+# #+#  #+#   #+#    #+#  +#+# #+#  #+#" << endl;
	cout << " ######  ###  ###  ######   ######   ######  #######  ###   ###  ###### " << endl;
	cout << "\n\n";
	cout << "\t\t:::::::   ::::::     :::    :::::::" << endl;
	cout << "\t\t:+:  :+: :+:  :+:   :+ +:   :+:  :+:" << endl;
	cout << "\t\t+:+  +:+ +:+  +:+  +:+ +:+  +:+  +:+" << endl;
	cout << "\t\t+#+:+#:  +#+  +:+ +#++:+#++ +#+  +:+" << endl;
	cout << "\t\t+#+  +#+ +#+  +#+ +#+   +#+ +#+  +#+" << endl;
	cout << "\t\t#+#  #+# #+#  #+# #+#   #+# #+#  #+#" << endl;
	cout << "\t\t###  ###  ######  ###   ### ####### " << endl;

	string tit[] = { "New game", "Load game", "Setting", "Exit game" };
	int n = sizeof(tit) / sizeof(tit[0]);
	drawborder(85, 5, 2, 22, LIGHTGREEN, tit[0]);
	int loca = 10;
	for (int i = 1; i < n; i++)
	{
		drawborder(85, loca, 2, 22, WHITE, tit[i]);
		loca += 5;
	}
	loca = 10;
	char c = _getch();
	while (1)
	{
		int state = key(c);
		if (state == DOWN || state == RIGHT)
		{
			if (loca < 20)
			{
				drawborder(85, loca, 2, 22, WHITE, tit[loca / 5 - 1]);
				loca += 5;
				drawborder(85, loca, 2, 22, LIGHTGREEN, tit[loca / 5 - 1]);
			}
			else {
				drawborder(85, loca, 2, 22, WHITE, tit[n - 1]);
				loca = 5;
				drawborder(85, loca, 2, 22, LIGHTGREEN, tit[0]);
			}
		}
		else if (state == UP || state == LEFT)
		{
			if (loca > 5)
			{
				drawborder(85, loca, 2, 22, WHITE, tit[loca / 5 - 1]);
				loca -= 5;
				drawborder(85, loca, 2, 22, LIGHTGREEN, tit[loca / 5 - 1]);
			}
			else {
				drawborder(85, loca, 2, 22, WHITE, tit[0]);
				loca = 20;
				drawborder(85, loca, 2, 22, LIGHTGREEN, tit[n - 1]);
			}
		}
		else if (state == ENTER)
		{
			switch (loca)
			{
			case 10:
			{
				testscreen();
				return;
			}
			case 15:
			{
				testscreen();
				return;
			}
			case 20:
			{
				testscreen();
				return;
			}
			case 25:
			{
				testscreen();
				return;
			}
			}
			c = _getch();
		}
		_getch();
	}
}

