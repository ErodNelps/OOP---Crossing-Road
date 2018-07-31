#ifndef _HEADER_H_
#define _HEADER_H_
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

using namespace std;

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

enum status { UP, DOWN, LEFT, RIGHT, ENTER, ESC, TAB, TRASH, SPACE, SAVE , LOAD};

class Coordinate
{
private:
	int x;
	int y;
public:
	Coordinate(int x, int y) { this->x = x; this->y = y; };
	bool operator ==(const Coordinate& sub)
	{
		return this->x == sub.x && this->y == sub.y;
	}
};

class Character
{
public:
	int x;
	int y;
	vector<int> space;
public:
	Character() { this->space.push_back(6); this->space.push_back(6); };
	void virtual Appear() = 0;
	void Disappear();
	vector<Coordinate> Space();
	void Sparkle();

};

class Player : public Character
{
private:
	bool status;
public:
	Player() {};
	void Appear();
	void Update(int x, int y, int width, int height);
	bool Win();
	void Reset(int width, int height);
};

class Timer : public Character
{
private:
	int time;
	int countdown;
	bool status;
	int chance;
public:
	Timer();
	void DrawSignal();
	void SetUp(bool status, int countdown);
	void Targer(int target);
	void Disappear();
	void Appear();
	bool Update();
	bool Status();
	bool CountDown();
	int Chance();
};

void Go(int x, int y);
void SetTextAttribute(int k);
void SetWindowSize(int width, int height);
void DrawButton(int x, int y, int width, int height, int color, string textinbutton);
void DrawBorder(int x, int y, int width, int height, int color);
void ClearScreen();
void HideCursor();
status Key(char a);
#endif