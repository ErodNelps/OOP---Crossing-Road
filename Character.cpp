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
#define TOPHALF 223
#define BOTTOMHALF 220
#define BLOCK 219
#include <iostream>
#include <Windows.h>
#include <thread>
#include <conio.h>
#include <string>
#include <fstream>
#include <processthreadsapi.h>
#include <vector>
#include <chrono>

using namespace std;

//Intruction:
// Copy 3 dong code replace vào phần bên dưới để in ra nhân vật theoys muốn, mỗi lớp sẽ có một hàm PrintCharacter() riêng,
//lớp CAnimal và CVehicle cũng có nhưng chỉ để trống thôi
// Bird
//  cout << " " << char(BOTTOMHALF) << "  " << char(BOTTOMHALF) << " ";
//  gotoxy(x, y + 1);
//  cout << char(TOPHALF) << " " << char(BLOCK) << char(BLOCK) << " " << char(TOPHALF);
//

// Snake
//	cout << " " << char(BOTTOMHALF)<< char(BOTTOMHALF) << "  " << char(BOTTOMHALF);
//  gotoxy(x, y + 1);
//	cout << char(TOPHALF) << "  " << char(TOPHALF) << char(TOPHALF) << " ";

// Car
//	cout << char(BOTTOMHALF) << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BOTTOMHALF);
//  gotoxy(x, y + 1);
//	cout << " " << "O" << "  " << "O" << " ";

// Truck
//	cout << "  " << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BLOCK);
//  gotoxy(x, y + 1);
//	cout << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BLOCK);

// CHỉ cần lấy hàm run() và print(), đổi tên tùy thích, nhớ lấy các hằng số BLOCK, TOPHALF, BOTTOMHALF
void gotoxy(int x, int y)
{
	static HANDLE  h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

void print(int x, int y)
{
	//replace code here
	cout << char(BOTTOMHALF) << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BOTTOMHALF);
	gotoxy(x, y + 1);
	
	cout << " " << "O" << "  " << "O" << " ";
}

void run()
{
	srand(time(0));
	for (int i = 0; i < 100; i++)
	{
		gotoxy(i, 3);
		print(i, 3);
		this_thread::sleep_for(chrono::milliseconds(50));
		gotoxy(i, 3);
		cout << "      ";
		gotoxy(i, 4);
		cout << "      ";
	}
	
}

void main()
{
	run();
}