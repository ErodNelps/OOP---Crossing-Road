#include "Character.h"
#include "NPC.h"

class Game
{
private:
	Player player;
	Timer timer;
	vector<NPMC*> machine;
	vector<NPLC*> animal;
	int life;
	int level;
	int height;
	int width;
	int key;
	int status;
	int selection;
	bool playing;
	bool sound;
	int bird;
	int snake;
	int settings;
	int carspeed;
	int truckspeed;
	int snakespeed;
	int birdspeed;
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
	bool Load(bool sub);
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
	void SetTimer();
	void UpdateTimer();
	void LoadingScreen();
	bool PlayingMenu(int key);
	void Mode(bool mode);
};