#include "Character.h"
#include "Game.h"

Game::Game()
{
	this->life = 2;
	this->level = 1;
	this->width = 100;
	this->height = 34;
	this->key = 6;
	this->status = 1;
	this->Allocate();
	this->player.Reset(this->width, this->height);
	
}
void Game::NewGame()
{
	PlaySound(NULL, NULL, 0);
	this->life = 2;
	this->level = 1;
	this->width = 100;
	this->height = 34;
	this->key = 6;
	this->status = 1;
	this->Allocate();
	this->player.Reset(this->width, this->height);
}

void Game::Allocate()
{
	int quantity, acceleration, speed;

	this->machine.clear();
	this->animal.clear();
	this->player.Reset(this->width, this->height);

	quantity = this->level < 5 ? this->level : 5;
	acceleration = this->level > 5 ? (this->level - 5) * 2 : 0;

	speed = 10 - acceleration > 5 ? 10 - acceleration : 5;
	for (int i = 0; i < quantity; i++)
	{
		this->machine.push_back(new Car(1 + i * ((width - 6 * quantity) / quantity + 6), 27, speed, false));
		this->machine.push_back(new Car(1 + i * ((width - 6 * quantity) / quantity + 6), 19, speed, false));
	}

	speed = 5 - acceleration > 5 ? 5 - acceleration : 5;
	for (int i = 0; i < quantity; i++)
	{
		this->machine.push_back(new Truck((1 + ((width - 6 * quantity) / quantity + 6) / 2 + i * ((width - 6 * quantity) / quantity + 6)) % this->width, 23, speed, true));
	}

	speed = 15 - acceleration > 5 ? 15 - acceleration : 5;
	for (int i = 0; i < quantity; i++)
	{
		this->animal.push_back(new Snake((1 + ((width - 6 * quantity) / quantity + 6) / 2 + i * ((width - 6 * quantity) / quantity + 6)) % this->width, 7, speed, true));
		this->animal.push_back(new Snake((1 + ((width - 6 * quantity) / quantity + 6) / 2 + i * ((width - 6 * quantity) / quantity + 6)) % this->width, 15, speed, true));
	}

	speed = 20 - acceleration > 5 ? 20 - acceleration : 5;
	for (int i = 0; i < quantity; i++)
	{
		this->animal.push_back(new Bird(1 + i * ((width - 6 * quantity) / quantity + 6), 11, speed, false));
	}
}

void Game::ResetLevel(bool status)
{
	this->DeleteObjects();
	if (status)
	{
		this->level++;
		Go(this->width / 2, 2);
		cout << "Level " << this->level;
	}
	else
	{
		Go(1, 1);
		cout << "LIVES: ";
		for (int i = 0; i < 2; i++)
		{
			if (i < this->life)
				cout << char(BLOCK) << " ";
			else
				cout << "  ";
		}
	}
	this->Allocate();
	this->CreateObjects();
	Go(90, 1);
	cout << "PLAYING   ";
}

Player Game::Player()
{
	return this->player;
}

vector<NPMC*> Game::NPMCs()
{
	return this->machine;
}

vector<NPLC*> Game::NPLCs()
{
	return this->animal;
}

void Game::Reset(bool status)
{
	this->key = 6;
	string text;
	SetTextAttribute(RED);
	Go(90, 1);
	if (status)
	{
		text = "WIN       ";
		cout << text;
	}
	else
	{
		text = "DEAD      ";
		cout << text;
	}
	SetTextAttribute(LIGHTGREEN);
	this->player.Sparkle();
	for (int i = 2; i > 0; i--)
	{
		Go(90, 1);
		cout << "   " << i << "   ";
		Sleep(500);
	}

	string destination = "DESTINATION";
	Go(int((this->width - destination.length()) / 2 + 2), 5);
	cout << destination;

	if (status)
	{
		this->ResetLevel(true);
		this->key = 8;
	}
	if (!status)
	{
		this->life--;
		if (this->life != 0)
			this->ResetLevel(false);
		this->key = 8;
		this->key = true;
	}
	
	Go(0, 6);
	cout << char(204);
	for (int i = 0; i < this->width; i++)
	{
		cout << char(205);
	}
	cout << char(185);
	for (int i = 1; i < this->width + 1; i++)
	{
		Go(i, 4);
		cout << char(186);
		Go(i, 5);
		cout << char(186);
	}

	if (this->life == 0)
	{
		this->DeleteObjects();
		SetTextAttribute(CYAN);
		text = "PRESS [ENTER] TO START A NEW GAME";
		Go(int((this->width - text.length()) / 2 + 2), this->height / 2);
		cout << text;

		text = "PRESS [ESC] TO GET BACK TO MENU";
		Go(int((this->width - text.length()) / 2 + 2), this->height / 2 + 1);
		cout << text;
		SetTextAttribute(LIGHTGREEN);
	}
}

void Game::Exit(HANDLE h)
{
	ClearScreen();
	this->life = 0;
	DWORD thread;
	GetExitCodeThread(h, &thread);
	TerminateThread(h, thread);
	return;
}

void Game::Operation()
{
	this->CreateObjects();

	while (this->life!= 0)
	{
		if (this->key < 7)
			this->UpdatePlayer(this->key);
		this->key = 7;
		this->SetTimer();
		if (this->timer.Status())
			this->UpdateTimer();
		this->UpdateNPLCs();
		this->UpdateNPMCs();
		if (this->player.Win())
			this->Reset(true);
		if (!this->Status())
			this->Reset(false);
		Sleep(50);
 	}

	return;
}
void Game::Start()
{
	this->DrawGame(LIGHTGREEN, "CROSSING ROAD");

	thread operation(bind(&Game::Operation,this));

	while (TRUE)
	{
		this->key = Key(this->key);
		if (this->life!= 0)
		{
			if (this->key == 5)
			{
				this->Exit(operation.native_handle());
				this->Menu();
			}
			else
			{
				if (key == 6)
					this->Pause(operation.native_handle());
				else if (key == 8)
					this->Resume((HANDLE)operation.native_handle());
				else if (key == 9)
				{
					this->Pause(operation.native_handle());
					this->Save();
					this->Resume((HANDLE)operation.native_handle());
				}
			}
		}
		else
		{
			if (this->key == 4)
			{
				this->NewGame();
				this->Start();
			}
			else if(this->key == 5)
			{
				this->Exit(operation.native_handle());
				this->Menu();
			}
		}
		if (this->status++ == 0)
		{
			Sleep(50);
			this->Pause(operation.native_handle());
		}
	}
}

void Game::Load()//string filename
{
	this->status = 0;
	ifstream save("Save.bin", ios::binary);
	if (!save.is_open())
	{
		cout << "Can't open save file! File might got corrupted!\n";
		return;
	}
	else 
	{
		save.read((char*)&this->life, sizeof(int));
		save.read((char*)&this->level, sizeof(int));
		save.read((char*)&this->player.x, sizeof(int));
		save.read((char*)&this->player.y, sizeof(int));
		for (unsigned i = 0; i < this->animal.size(); i++)
		{
			save.read((char*)&this->animal[i]->x, sizeof(int));
			save.read((char*)&this->animal[i]->y, sizeof(int));
		}
		for (unsigned i = 0; i < this->machine.size(); i++)
		{
			save.read((char*)&this->machine[i]->x, sizeof(int));
			save.read((char*)&this->machine[i]->y, sizeof(int));
		}
	}
	save.close();
}

void Game::Save()//string filename
{
	ofstream save("Save.bin", ios::binary);
	if (!save.is_open())
	{
		cout << "Can't open save file! File might got corrupted!\n";
		return;
	}
	else {
		save.write((char*)&this->life, sizeof(int));
		save.write((char*)&this->level, sizeof(int));
		save.write((char*)&this->player.x, sizeof(int));
		save.write((char*)&this->player.y, sizeof(int));
		for (unsigned i = 0; i < this->animal.size(); i++)
		{
			save.write((char*)&this->animal[i]->x, sizeof(int));
			save.write((char*)&this->animal[i]->y, sizeof(int));
		}
		for (unsigned i = 0; i < this->machine.size(); i++)
		{
			save.write((char*)&this->machine[i]->x, sizeof(int));
			save.write((char*)&this->machine[i]->y, sizeof(int));
		}
	}
	save.close();
	Go(90, 1);
	cout << "SAVING";
	for (int i = 0; i < 3; i++)
	{
		Go(96 + i, 1);
		cout << ".";
		Sleep(1000);
	}
}

void Game::Pause(HANDLE h)
{
	string text = "PAUSE     ";
	Go(90, 1);
	cout << text;
	SuspendThread(h);
}

void Game::Resume(HANDLE h)
{
	string text = "PLAYING   ";
	Go(90, 1);
	cout << text;
	ResumeThread(h);
}

void Game::UpdatePlayer(int move)
{
	this->player.Disappear();
	
	switch (move)
	{
	case 0:
	{
		this->player.Update(0, 1, this->width, this->height);
		break;
	}
	case 1:
	{
		this->player.Update(0, -1, this->width, this->height);
		break;
	}
	case 2:
	{
		this->player.Update(-1, 0, this->width, this->height);
		break;
	}
	case 3:
	{
		this->player.Update(1, 0, this->width, this->height);
		break;
	}
	}

	this->player.Appear();
}
void Game::UpdateNPMCs() 
{
	for (unsigned i = 0; i < this->machine.size(); i++)
	{
		if (this->machine[i]->Speed() == true)
		{
			this->machine[i]->Disappear();
			this->machine[i]->Move();
			this->machine[i]->Appear();
		}
	}
}
void Game::UpdateNPLCs()
{
	for (unsigned i = 0; i < this->animal.size(); i++)
	{
		if (this->animal[i]->Speed() == true)
		{
			this->animal[i]->Disappear();
			this->animal[i]->Move();
			this->animal[i]->Appear();
		}
	}
}

bool Game::Status()
{
	vector<Coordinate> player;
	vector<Coordinate> object;

	player = this->player.Space();

	for (unsigned i = 0; i < this->machine.size(); i++)
	{
		object = this->machine[i]->Space();
		for (unsigned k = 0; k < player.size(); k++)
		{
			for (unsigned l = 0; l < object.size(); l++)
			{
				if (player[k] == object[l])
					return false;
			}
		}
	}

	for (unsigned i = 0; i < this->animal.size(); i++)
	{
		object = this->animal[i]->Space();
		for (unsigned k = 0; k < player.size(); k++)
		{
			for (unsigned l = 0; l < object.size(); l++)
			{
				if (player[k] == object[l])
					return false;
			}
		}
	}

	player.clear();
	object.clear();

	return true;
}

void Game::DeleteObjects()
{
	this->player.Disappear();
	this->timer.Disappear();
	this->timer.SetUp(false, 0);

	for (unsigned i = 0; i < this->machine.size(); i++)
	{
		this->machine[i]->Disappear();
	}

	for (unsigned i = 0; i < this->animal.size(); i++)
	{
		this->animal[i]->Disappear();
	}
}
void Game::CreateObjects()
{
	this->player.Appear();

	for (unsigned i = 0; i < this->machine.size(); i++)
	{
		this->machine[i]->Appear();
	}

	for (unsigned i = 0; i < this->animal.size(); i++)
	{ 
		this->animal[i]->Appear();
	}
}
void Game::SetTimer()
{
	if (this->timer.Status())
		return;
	int target;
	srand(unsigned(time(0)));

	if ((rand() % 1000) > this->timer.Chance())
		return;

	switch (int(rand() % 5))
	{
	case 0:
	{
		target = 27;
		break;
	}
	case 1:
	{
		target = 23;
		break;
	}
	case 2:
	{
		target = 19;
		break;
	}
	case 3:
	{
		target = 15;
		break;
	}
	case 4:
	{
		target = 11;
		break;
	}
	case 5:
	{
		target = 7;
		break;
	}
	}

	for (unsigned i = 0; i < this->machine.size(); i++)
	{
		if (this->machine[i]->y == target)
			this->machine[i]->SetSpeed(100);
	}

	for (unsigned i = 0; i < this->animal.size(); i++)
	{
		if (this->animal[i]->y == target)
			this->animal[i]->SetSpeed(100);
	}

	this->timer.SetUp(true, 100);
	this->timer.Targer(target + 2);
	this->timer.Appear();
}

void Game::UpdateTimer()
{
	if (this->timer.Status() && this->timer.CountDown())
	{
		if (!this->timer.Update())
			return;
		this->timer.Disappear();
		this->timer.Appear();
	}
}

void Game::DrawGame(int color, string text)
{
	ClearScreen();
	SetWindowSize(850, 600);
	HideCursor();
	SetTextAttribute(color);
	Go(0, 0);
	cout << char(201);

	for (int i = 0; i < this->width; i++)
		cout << char(205);
	cout << char(187);

	for (int i = 1; i <= this->height; i++)
	{
		Go(0, i);
		cout << char(186);
	}

	Go(0, this->height);
	cout << char(200);

	for (int i = 0; i < this->width; i++)
		cout << char(205);
	cout << char(188);

	for (int i = 1; i <= this->height - 1; i++)
	{
		Go(this->width + 1, i);
		cout << char(186);
	}
	Go(0, 3);
	cout << char(204);
	for (int i = 0; i < this->width; i++)
		cout << char(205);
	Go(this->width + 1, 3);
	cout << char(185);
	Go(0, 6);
	cout << char(204);
	for (int i = 0; i < this->width; i++)
	{
		cout << char(205);
	}
	cout << char(185);
	for (int i = 1; i < this->width + 1; i++)
	{
		Go(i, 4);
		cout << char(186);
		Go(i, 5);
		cout << char(186);
	}
	Go(1, 1);
	cout << "LIVES: ";
	for (int i = 0; i < this->life; i++)
	{
		cout << char(BLOCK) << " ";
	}
	int center = int((this->width - text.length()) / 2);
	Go(center + 2, 1);
	cout << text;
	
	string destination = "DESTINATION";
	Go(int((this->width - destination.length()) / 2 + 2), 5);
	cout << destination;

	Go(90, 1);
	cout << "PLAYING";
	Go(this->width / 2, 2);
	cout <<"Level " <<  this->level;
	for (int i = 9; i < 9 + 6*4 ; i+=4)
	{
		Go(1, i);
		cout << "<" << char(BLOCK) << ">";
	}
}

void Game::Menu()
{
	SetWindowSize(900, 500);
	ClearScreen();
	bool menu = TRUE;
	PlaySound(TEXT("FunMenu.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	SetTextAttribute(LIGHTMAGNETA);
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

	string title[] = { "New game", "Load game", "Setting", "Exit game" };
	int n = sizeof(title) / sizeof(title[0]);
	DrawButton(85, 5, 2, 22, LIGHTGREEN, title[0]);
	int location = 10;
	for (int i = 1; i < n; i++)
	{
		DrawButton(85, location, 2, 22, WHITE, title[i]);
		location += 5;
	}
	
	location = 5;
	char c = ' ';
	while (menu)
	{

		int state = Key(c);
		if (state == DOWN || state == RIGHT)
		{
			if (location < 20)
			{
				DrawButton(85, location, 2, 22, WHITE, title[location / 5 - 1]);
				location += 5;
				DrawButton(85, location, 2, 22, LIGHTGREEN, title[location / 5 - 1]);
			}
			else {
				DrawButton(85, location, 2, 22, WHITE, title[n - 1]);
				location = 5;
				DrawButton(85, location, 2, 22, LIGHTGREEN, title[0]);
			}
		}
		else if (state == UP || state == LEFT)
		{
			if (location > 5)
			{
				DrawButton(85, location, 2, 22, WHITE, title[location / 5 - 1]);
				location -= 5;
				DrawButton(85, location, 2, 22, LIGHTGREEN, title[location / 5 - 1]);
			}
			else {
				DrawButton(85, location, 2, 22, WHITE, title[0]);
				location = 20;
				DrawButton(85, location, 2, 22, LIGHTGREEN, title[n - 1]);
			}
		}
		else if (state == ENTER)
		{
			switch (location)
			{
			case 5:
			{
				this->NewGame();
				this->Start();
				menu = FALSE;
				return;
			}
			case 10:
			{
				this->Load();
				this->Start();
				menu = FALSE;
				return;
			}
			case 15:
			{
				menu = FALSE;
				return;
			}
			case 20:
			{
				exit(0);
			}
			}
		}
		else if (state == ESC)
			exit(0);
	}
}
void Game::LoadingScreen()
{
	ClearScreen();
	HideCursor();
	int x = 34;
	int count = x;
	int y = 12;
	int width = 50;
	Go(x, y - 2);
	SetTextAttribute(LIGHTGREEN);
	for (int i = 1; i <= 50; i++)
	{
		DrawBorder(x, y, 1, width, LIGHTGREEN);
		Go(x, y - 2);
		cout << "Loading...";
		Go(x, y);
		for (int j = 1; j <= i; j++)
		{
			cout << char(219);
		}
		Go(x + 11, y - 2);
		cout << 2 * i << "%";
		Go(x + 16, y - 2);
		cout << "                                        ";
		Go(x + 16, y - 2);
		if (i > 1 && i < 20)
			cout << "\tCreating Temporary files";
		else if (i > 20 && i < 40)
			cout << "\tAccessing Main Memory";
		else if (i > 40 && i < 49)
			cout << "\tHacking System";
		else cout << "\tCompleted";
		Sleep(60);
	}
	Sleep(700);
}