#ifndef _HEADER_H
#define _HEADER_H
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

enum status { UP, DOWN, LEFT, RIGHT, ENTER, ESC, TAB, TRASH, SPACE, SAVE };
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

class NPC : public Character
{
protected:
	bool move;
	int speed;
	int max;
	int distance;
	int monitor;
public:
	NPC(int x, int y, int distance, int max);
	void Move();
	void virtual Appear() = 0;
	bool Speed();
	bool Distance();
};

class NPMC : public NPC
{
public:
	NPMC(int x, int y, int distance, int max) : NPC(x, y, distance, max) {};
	void virtual Appear() = 0;
};

class NPLC : public NPC
{
public:
	NPLC(int x, int y, int distance, int max) : NPC(x, y, distance, max) {};
	void virtual Appear() = 0;
};

class Car : public NPMC
{
public:
	Car(int x, int y, int distance, int max) : NPMC(x, y, distance, max) {};
	void Appear();
};

class Truck : public NPMC
{
public:
	Truck(int x, int y, int distance, int max) : NPMC(x, y, distance, max) {};
	void Appear();
};

class Snake : public NPLC
{
public:
	Snake(int x, int y, int distance, int max) : NPLC(x, y, distance, max) {};
	void Appear();
};

class Bird : public NPLC
{
public:
	Bird(int x, int y, int distance, int max) : NPLC(x, y, distance, max) {};
	void Appear();
};
class Game
{
private:
	Player player;
	vector<NPMC*> machine;
	vector<NPLC*> animal;
	int life;
	int level;
	int height;
	int width;
	int key;
	int status;
public:
	Game();
	void DrawGame(int color, string text);
	void Menu();
	Player Player();
	vector<NPMC*> NPMCs();
	vector<NPLC*> NPLCs();
	void Reset(bool status);
	void Exit(HANDLE);
	void Start();
	void Operation();
	void Load();
	void Save();
	void Pause(HANDLE h);
	void Resume(HANDLE h);
	void UpdatePlayer(int move);
	void UpdateNPMCs();
	void UpdateNPLCs();
	void DeleteObjects();
	void CreateObjects();
	bool Status();
	void ResetLevel(bool status);
	void Allocate();
	void NewGame();
};

void Go(int x, int y);
void SetTextAttribute(int k);
void SetWindowSize(int width, int height);
void DrawBorder(int x, int y, int width, int height, int color, string textinbutton);
status Key(char a);
#endif
