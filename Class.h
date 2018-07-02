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


void gotoxy(int x, int y);
void setTextAttribute(int k);
void menu();


using namespace std;

class CPEOPLE {
	int mX, mY;
	bool mState; //Trạng thái sống chết
public:
	CPEOPLE();
	Control();
	bool isImpact(const CVEHICLE*&);
	bool isImpact(const CANIMAL*&);
	bool isFinish();
	bool isDead();
};

class CVEHICLE {
	int mX, mY;
public:

	virtual void Move();
};

class CTRUCK : public CVEHICLE {
public:
	void Move()

};

class CCAR : public CVEHICLE {
public:
	//…
};

class CANIMAL {
	int mX, mY;
public:
	virtual void Move(int X, int Y) {
	};
	virtual void Tell();
};

class CDINAUSOR : public CANIMAL {
public:
	//…
};

class CBIRD : public CANIMAL {
public:
	//…
};

class CGAME {
	int width;
	int height;
	CTRUCK* axt;
	CCAR* axh;
	CDINAUSOR* akl;
	CBIRD* ac;
	CPEOPLE cn;
public:
	CGAME(int width, int height)
	{
		this->width = width;
		this->height = height;
	}//Chuẩn bị dữ liệu cho tất cả các đối tượng
	void drawGame(int x, int y, int width, int height, int color, string textinbutton); //Thực hiện vẽ trò chơi ra màn hình sau khi có dữ liệu
	~CGAME(); // Hủy tài nguyên đã cấp phát
	CPEOPLE getPeople();//Lấy thông tin người
	CVEHICLE* getVehicle();//Lấy danh sách các xe
	CANIMAL* getAnimal(); //Lấy danh sách các thú
	void resetGame(); // Thực hiện thiết lập lại toàn bộ dữ liệu như lúc đầu
	void exitGame(HANDLE); // Thực hiện thoát Thread
	void startGame(); // Thực hiện bắt đầu vào trò chơi
	void loadGame(istream& is); // Thực hiện tải lại trò chơi đã lưu
	void saveGame(istream& is); // Thực hiện lưu lại dữ liệu trò chơi
	void pauseGame(HANDLE h) {
		SuspendThread(h);
	} // Tạm dừng Thread
	void resumeGame(HANDLE h) {
		ResumeThread(h);
	}; //Quay lai Thread
	void updatePosPeople(char); //Thực hiện điều khiển di chuyển của CPEOPLE
	void updatePosVehicle(); //Thực hiện cho CTRUCK & CCAR di chuyển
	void updatePosAnimal();//Thực hiện cho CDINAUSOR & CBIRD di chuyển
};

CPEOPLE CGAME::getPeople()
{
	return cn;
}

CVEHICLE* CGAME::getVehicle()
{
}

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



void CGAME::drawGame(int x, int y, int width, int height, int color, string textinbutton)
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

void CGAME::saveGame(istream &is)
{
	fstream save;
	save.open("Savefile.txt", fstream::out);
	save << "..." << endl;
}

void CGAME::loadGame(istream &is)
{
	fstream load;
	load.open("Savefile.txt", fstream::in);
}

void menu()
{
	setTextAttribute(3);
	cout << " ::::::  :::::::   ::::::   ::::::   ::::::  :::::::  ::::  :::  :::::: " << endl;
	cout << ":+:  :+: :+:  :+: :+:  :+: :+:  :+: :+:  :+:   :+:    :+:+  :+: :+:  :+:" << endl;
	cout << "+:+      +:+  +:+ +:+  +:+ +:+      +:+        +:+    :+:+  +:+ +:+      " << endl;
	cout << "+#+      +#+:+#:  +#+  +:+ +#++:+#+ +#++++#+   +#+    +#+++ +#+ :#:      " << endl;
	cout << "+#+      +#+  +#+ +#+  +#+      +#+      +#+   +#+    +#+  +#+# +#+ +#+#" << endl;
	cout << "#+#  #+# #+#  #+# #+#  #+# #+#  #+# #+#  #+#   #+#    #+#  +#+# #+#  #+#" << endl;
	cout << " ######  ###  ###  ######   ######   ######  #######  ###   ###  ###### " << endl;

	cout << ":::::::   ::::::     :::    :::::::" << endl;
	cout << ":+:  :+: :+:  :+:   :+ +:   :+:  :+:" << endl;
	cout << "+:+  +:+ +:+  +:+  +:+ +:+  +:+  +:+" << endl;
	cout << "+#+:+#:  +#+  +:+ +#++:+#++ +#+  +:+" << endl;
	cout << "+#+  +#+ +#+  +#+ +#+   +#+ +#+  +#+" << endl;
	cout << "#+#  #+# #+#  #+# #+#   #+# #+#  #+#" << endl;
	cout << "###  ###  ######  ###   ### ####### " << endl;
}