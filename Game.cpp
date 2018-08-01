#include "Character.h"
#include "Game.h"

Game::Game()
{
	this->playing = true;
	this->selection = 0;
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
	this->playing = true;
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
	Go(75, 1);
	if (status)
	{
		text = "               WIN       ";
		cout << text;
		Go(75, 2);
		cout << "                         ";
	}
	else
	{
		text = "               DEAD      ";
		cout << text;
		Go(75, 2);
		cout << "                         ";
	}
	SetTextAttribute(LIGHTGREEN);
	this->player.Sparkle();
	for (int i = 2; i > 0; i--)
	{
		Go(75, 1);
		cout << "               " << i << "         ";
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
	for (int i = 0; i < 9; i += 4)
	{
		Go(98, 17 + i);
		SetTextAttribute(DARKGRAY);
		cout << char(BOTTOMHALF);
		Go(99, 17 + i);
		SetTextAttribute(GREEN);
		cout << char(BOTTOMHALF);
	}

	SetTextAttribute(LIGHTGREEN);
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
	this->key = 7;

	while (TRUE)
	{
		this->key = Key(this->key);
		if (this->life != 0)
		{
			if (this->key == 5)
			{
				this->Exit(operation.native_handle());
				exit(0);
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
				}
				else if (key == 10)
				{
					this->Pause(operation.native_handle());
					this->life = 0;
					this->playing = true;
					this->Load(true);
					this->Start();
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
			else if (this->key == 5)
			{
				this->Exit(operation.native_handle());
				this->Menu();
			}
		}

		if (!this->playing)
		{
			if (this->PlayingMenu(this->key))
				switch (this->selection)
				{
				case 0:
				{
					this->Pause(operation.native_handle());
					this->Save();
					break;
				}
				case 1:
				{
					this->life = 0;
					this->playing = true;
					this->Load(true);
					this->Start();
					break;
				}
				case 2:
				{
					break;
				}
				case 3:
				{
					this->Exit(operation.native_handle());
					exit(0);
					break;
				}
				}
		}

		if (this->status++ == 0)
		{
			Sleep(50);
			this->Pause(operation.native_handle());
		}
	}
}

void Game::Load(bool sub)
{
	string name;

	if (sub)
		Go(47, 35);
	else
		Go(47, 25);
	cout << "FILE: ";
	cin >> name;

	ifstream file(name, ios::binary);
	if (!file.is_open())
	{
		if (sub)
			Go(47, 35);
		else
			Go(47, 25);
		for (int i = 37; i < 101; i++)
			cout << " ";
		if (sub)
			Go(47, 35);
		else
			Go(47, 25);
		cout << "INVALID FILE!";
		Sleep(1000);
		return;
	}
	else
	{
		int life, level, speed, acceleration;

		file.read((char*)&life, sizeof(int));
		file.read((char*)&level, sizeof(int));

		int quantity = level < 5 ? this->level : 5;
		vector<NPMC*> machine;
		vector<NPLC*> animal;

		acceleration = level > 5 ? (level - 5) * 2 : 0;
		speed = 20 - acceleration > 5 ? 20 - acceleration : 5;

		for (int i = 0; i < quantity; i++)
		{
			machine.push_back(new Car(1 + i * ((width - 6 * quantity) / quantity + 6), 27, speed, false));
			machine.push_back(new Car(1 + i * ((width - 6 * quantity) / quantity + 6), 19, speed, false));
		}

		speed = 25 - acceleration > 5 ? 25 - acceleration : 5;
		for (int i = 0; i < quantity; i++)
		{
			machine.push_back(new Truck((1 + ((width - 6 * quantity) / quantity + 6) / 2 + i * ((width - 6 * quantity) / quantity + 6)) % this->width, 23, speed, true));
		}

		speed = 40 - acceleration > 5 ? 40 - acceleration : 5;
		for (int i = 0; i < quantity; i++)
		{
			animal.push_back(new Snake((1 + ((width - 6 * quantity) / quantity + 6) / 2 + i * ((width - 6 * quantity) / quantity + 6)) % this->width, 7, speed, true));
			animal.push_back(new Snake((1 + ((width - 6 * quantity) / quantity + 6) / 2 + i * ((width - 6 * quantity) / quantity + 6)) % this->width, 15, speed, true));
		}

		speed = 30 - acceleration > 5 ? 30 - acceleration : 5;
		for (int i = 0; i < quantity; i++)
		{
			animal.push_back(new Bird(1 + i * ((width - 6 * quantity) / quantity + 6), 11, speed, false));
		}

		for (int i = 0; i < quantity * 3; i++)
		{
			file.read((char*)&animal[i]->x, sizeof(int));
			file.read((char*)&animal[i]->y, sizeof(int));
		}
		for (int i = 0; i < quantity * 3; i++)
		{
			file.read((char*)&machine[i]->x, sizeof(int));
			file.read((char*)&machine[i]->y, sizeof(int));
		}



		file.read((char*)&this->player.x, sizeof(int));
		file.read((char*)&this->player.y, sizeof(int));
		this->level = level;
		this->life = life;
		this->machine = machine;
		this->animal = animal;

	}
	file.close();

	Go(75, 1);
	cout << "               LOADING   ";
	Go(75, 2);
	cout << "                         ";
	for (int i = 0; i < 3; i++)
	{
		Go(97 + i, 1);
		cout << ".";
		Sleep(1000);
	}

	Go(47, 35);
	for (int i = 37; i < this->width + 1; i++)
	{
		cout << " ";
	}

	this->status = 0;
}

void Game::Save()
{
	string name;
	Go(47, 35);
	cout << "FILE: ";
	cin >> name;

	ofstream file(name, ios::binary);
	if (!file.is_open())
	{
		Go(47, 35);
		for (int i = 47; i < 101; i++)
			cout << " ";
		Go(47, 35);
		cout << "INVALID FILE";
		Sleep(1000);
		return;
	}
	else
	{
		file.write((char*)&this->life, sizeof(int));
		file.write((char*)&this->level, sizeof(int));
		for (unsigned i = 0; i < this->animal.size(); i++)
		{
			file.write((char*)&this->animal[i]->x, sizeof(int));
			file.write((char*)&this->animal[i]->y, sizeof(int));
		}
		for (unsigned i = 0; i < this->machine.size(); i++)
		{
			file.write((char*)&this->machine[i]->x, sizeof(int));
			file.write((char*)&this->machine[i]->y, sizeof(int));
		}
		file.write((char*)&this->player.x, sizeof(int));
		file.write((char*)&this->player.y, sizeof(int));
	}
	file.close();

	Go(75, 1);
	cout << "               SAVING    ";
	Go(75, 2);
	cout << "                         ";
	for (int i = 0; i < 3; i++)
	{
		Go(96 + i, 1);
		cout << ".";
		Sleep(1000);
	}

	Go(47, 35);
	for (int i = 47; i < 101; i++)
		cout << " ";

	Go(75, 1);
	cout << "PRESS [SPACE] TO CONTINUE";
	Go(75, 2);
	cout << "   PRESS [ESC] TO EXIT";

	Go(47, 35);
	cout << "   DONE";

	Sleep(1000);

	Go(37, 35);
	for (int i = 37; i < 101; i++)
		cout << " ";
}

void Game::Pause(HANDLE h)
{
	Go(75, 1);
	cout << "               PAUSE     ";
	Go(75, 2);
	cout << "                         ";
	ResumeThread(h);
	SuspendThread(h);
	this->playing = false;
}
void Game::Resume(HANDLE h)
{
	string text = "               PLAYING   ";
	Go(75, 1);
	cout << text;
	Go(75, 2);
	cout << "                         ";
	ResumeThread(h);
	this->playing = true;
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

	switch (int(rand() % 3))
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
	this->timer.Targer(target - 1);
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
	SetWindowSize(850, 750);
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
	string destination = "DESTINATION";
	Go(int((this->width - destination.length()) / 2 + 2), 5);
	cout << destination;

	Go(90, 1);
	cout << "PLAYING";
	Go(this->width / 2, 2);
	cout << this->level;


	for (int i = this->height; i < height + 8; i++)
	{
		Go(0, i);
		cout << char(186);
	}

	Go(0, this->height + 8);
	cout << char(200);

	for (int i = 0; i < this->width; i++)
		cout << char(205);
	cout << char(188);

	for (int i = this->height; i < this->height + 8; i++)
	{
		Go(this->width + 1, i);
		cout << char(186);
	}

	Go(0, this->height);
	cout << char(204);

	Go(0, this->height + 2);
	cout << char(204);

	for (int i = 1; i <= this->width; i++)
		cout << char(205);

	Go(this->width + 1, this->height);
	cout << char(185);

	Go(this->width + 1, this->height + 2);
	cout << char(185);

	this->PlayingMenu(-1);

	for (int i = 0; i < 9; i += 4)
	{
		Go(98, 17 + i);
		SetTextAttribute(DARKGRAY);
		cout << char(BOTTOMHALF);
		Go(99, 17 + i);
		SetTextAttribute(GREEN);
		cout << char(BOTTOMHALF);
	}

	SetTextAttribute(LIGHTGREEN);
	/*for (int i = 9; i < 9 + 6*4 ; i+=4)
	{
		Go(1, i);
		cout << "<" << char(BLOCK) << ">";
	}*/
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

	string title[] = { "NEW GAME", "LOAD GAME", "SETTINGS", "EXIT GAME" };
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
				this->Load(false);
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

bool Game::PlayingMenu(int key)
{
	if (key == 4)
		return true;

	switch (key)
	{
	case 0:
	{
		this->selection -= 1;
		if (this->selection == -1)
			this->selection = 3;
		break;
	}
	case 1:
	{
		this->selection += 1;
		break;
	}
	case 2:
	{
		this->selection -= 1;
		if (this->selection == -1)
			this->selection = 3;
		break;
	}
	case 3:
	{
		this->selection += 1;
		break;
	}
	}

	this->selection = this->selection % 4;

	bool menu = true;
	string title[] = { "SAVE GAME", "LOAD GAME", "SETTINGS", "EXIT GAME" };
	int location[4] = { 6, 30, 54, 78 };
	int n = sizeof(title) / sizeof(title[0]);

	DrawButton(location[this->selection], 39, 2, 20, LIGHTGREEN, title[this->selection]);
	for (int i = 0; i < n; i++)
	{
		if (i != this->selection)
			DrawButton(location[i], 39, 2, 20, WHITE, title[i]);
	}
	SetTextAttribute(LIGHTGREEN);

	return false;
}