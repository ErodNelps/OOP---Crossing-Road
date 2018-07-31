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
	void SetTimer();
	void UpdateTimer();
	void LoadingScreen();
};