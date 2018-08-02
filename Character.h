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
#include <SFML\Audio.hpp>
#pragma pack (push)
#pragma pack(1)
#pragma pack(pop)
#pragma comment(lib,"winmm.lib")

enum status { UP, DOWN, LEFT, RIGHT, ENTER, ESC, TAB, TRASH, SPACE, SAVE , LOAD};

class MusicManage {
	MusicManage() = default;

	static MusicManage* instance;
	sf::Music music;
public:
	static MusicManage* getInstance() {
		if (instance == nullptr)
			instance = new MusicManage;
		return instance;
	}
	sf::Music& getMusicObj() {
		return music;
	}
	bool openFromFile(std::string location) {
		return music.openFromFile(location);
	}
};

#define MusicPlayer MusicManage::getInstance()->getMusicObj()

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
	Character(vector<int> space) { this->space = space; };
	void virtual Appear() = 0;
	void virtual Disappear();
	vector<Coordinate> virtual Space();
	void virtual Sparkle();
};

class Player : public Character
{
private:
	bool status;
public:
	Player() { this->space[0] = 3; this->space[1] = 3; };
	void Appear();
	void Disappear();
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