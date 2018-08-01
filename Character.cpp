#include "Character.h"
#include "NPC.h"
vector<Coordinate> Character::Space()
{
	vector<Coordinate> space;
	for (unsigned i = 0; i < this->space.size(); i++)
	{
		for (int j = 0; j < this->space[i]; j++)
		{
			Coordinate sub((this->x + j) % 100, this->y + i);
			space.push_back(sub);
		}
	}

	return space;
}

void Character::Sparkle()
{
	for (int i = 0; i < 4; i++)
	{
		this->Disappear();
		Sleep(500);
		this->Appear();
		Sleep(500);
	}
}
NPC::NPC(int x, int y, int max, bool go)
{
	this->x = x;
	this->y = y;
	this->max = max;
	this->speed = this->max;
	this->go = go;
}

void NPC::Move()
{
	if (this->go)
	{
		this->x++;
		if (this->x == 101)
			this->x = 1;
	}
	else
	{
		this->x--;
		if (this->x == 0)
			this->x = 100;
	}
}

bool NPC::Speed()
{
	this->speed--;
	if (this->speed == 1)
	{
		this->speed = this->max;
		return true;
	}
	
	return false;
}
void NPC::SetSpeed(int speed)
{
	this->speed = speed;
}
void Character::Disappear()
{
	Go(this->x, this->y);

	if (this->x == 96)
	{
		cout << "     ";
		Go(this->x, this->y + 1);
		cout << "     ";
		Go(1, this->y);
		cout << " ";
		Go(1, this->y + 1);
		cout << " ";
	}
	else if (this->x == 97)
	{
		cout << "    ";
		Go(this->x, this->y + 1);
		cout << "    ";
		Go(1, this->y);
		cout << "  ";
		Go(1, this->y + 1);
		cout << "  ";
	}
	else if (this->x == 98)
	{
		cout << "   ";
		Go(this->x, this->y + 1);
		cout << "   ";
		Go(1, this->y);
		cout << "   ";
		Go(1, this->y + 1);
		cout << "   ";
	}
	else if (this->x == 99)
	{
		cout << "  ";
		Go(this->x, this->y + 1);
		cout << "  ";
		Go(1, this->y);
		cout << "    ";
		Go(1, this->y + 1);
		cout << "    ";
	}
	else if (this->x == 100)
	{
		cout << " ";
		Go(this->x, this->y + 1);
		cout << " ";
		Go(1, this->y);
		cout << "     ";
		Go(1, this->y + 1);
		cout << "     ";
	}
	else
	{
		cout << "      ";
		Go(this->x, this->y + 1);
		cout << "      ";
	}
}
bool Player::Win()
{
	if (this->y == 4)
		return true;
	return false;
}
void Player::Appear()
{
	Go(this->x, this->y);
	cout << " " << char(153) << " ";

	//cout << " " << char(BOTTOMHALF) << "  " << char(BOTTOMHALF) << " ";

	Go(this->x, this->y + 1);
	cout << char(213) << char(BLOCK) << char(184);
	//cout << char(TOPHALF) << " " << char(BLOCK) << char(BLOCK) << " " << char(TOPHALF);

}
void Player::Reset(int width, int height)
{
	this->status = true;
	this->x = (width - 1) / 2;
	this->y = height - 2;
}
void Player::Update(int x, int y, int width, int height)
{
	this->x += x;

	if (this->x + this->space[0] >= width + 2 || this->x <= 0)
		this->x -= x;

	this->y -= y;

	if (this->y + int(this->space.size()) >= height + 1 || this->y <= 3)
		this->y += y;
}

void Car::Appear()
{
	Go(this->x, this->y);

	if (this->x == 96)
	{
		cout << char(BOTTOMHALF) << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BLOCK);
		Go(this->x, this->y + 1);
		cout << " " << "O" << "  " << "O";
		Go(1, this->y);
		cout << char(BOTTOMHALF);
		Go(1, this->y + 1);
		cout << " ";
	}
	else if (this->x == 97)
	{
		cout << char(BOTTOMHALF) << char(BLOCK) << char(BLOCK) << char(BLOCK);
		Go(this->x, this->y + 1);
		cout << " " << "O" << "  ";
		Go(1, this->y);
		cout << char(BLOCK) << char(BOTTOMHALF);
		Go(1, this->y + 1);
		cout << "O"<< " ";
	}
	else if (this->x == 98)
	{
		cout << char(BOTTOMHALF) << char(BLOCK) << char(BLOCK);
		Go(this->x, this->y + 1);
		cout << " " << "O" << " ";
		Go(1, this->y);
		cout << char(BLOCK) << char(BLOCK) << char(BOTTOMHALF);
		Go(1, this->y + 1);
		cout << " " << "O" << " ";
	}
	else if (this->x == 99)
	{
		cout << char(BOTTOMHALF) << char(BLOCK);
		Go(this->x, this->y + 1);
		cout << " " << "O";
		Go(1, this->y);
		cout << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BOTTOMHALF);
		Go(1, this->y + 1);
		cout << "  " << "O" << " ";
	}
	else if (this->x == 100)
	{
		cout << char(BOTTOMHALF);
		Go(this->x, this->y + 1);
		cout << " ";
		Go(1, this->y);
		cout << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BOTTOMHALF);
		Go(1, this->y + 1);
		cout << "O" << "  " << "O" << " ";
	}
	else
	{
		cout << char(BOTTOMHALF) << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BOTTOMHALF);

		Go(this->x, this->y + 1);

		cout << " " << "O" << "  " << "O" << " ";
	}
}

void Truck::Appear()
{
	Go(this->x, this->y);

	if (this->x == 96)
	{
		cout << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BLOCK) << " ";
		Go(this->x, this->y + 1);
		cout << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BLOCK);
		Go(1, this->y);
		cout << " ";
		Go(1, this->y + 1);
		cout << char(BLOCK);
	}
	else if (this->x == 97)
	{
		cout << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BLOCK);
		Go(this->x, this->y + 1);
		cout << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BLOCK);
		Go(1, this->y);
		cout << "  ";
		Go(1, this->y + 1);
		cout << char(BLOCK) << char(BLOCK);
	}
	else if (this->x == 98)
	{
		cout << char(BLOCK) << char(BLOCK) << char(BLOCK);
		Go(this->x, this->y + 1);
		cout << char(BLOCK) << char(BLOCK) << char(BLOCK);
		Go(1, this->y);
		cout << char(BLOCK) << "  ";
		Go(1, this->y + 1);
		cout << char(BLOCK) << char(BLOCK) << char(BLOCK);
	}
	else if (this->x == 99)
	{
		cout << char(BLOCK) << char(BLOCK);
		Go(this->x, this->y + 1);
		cout << char(BLOCK) << char(BLOCK);
		Go(1, this->y);
		cout << char(BLOCK) << char(BLOCK) << "  ";
		Go(1, this->y + 1);
		cout << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BLOCK);
	}
	else if (this->x == 100)
	{
		cout << char(BLOCK);
		Go(this->x, this->y + 1);
		cout << char(BLOCK);
		Go(1, this->y);
		cout << char(BLOCK) << char(BLOCK) << char(BLOCK) << "  ";
		Go(1, this->y + 1);
		cout << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BLOCK);
	}
	else
	{
		cout << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BLOCK) << "  ";

		Go(x, y + 1);

		cout << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BLOCK);
	}
}

void Bird::Appear()
{
	Go(this->x, this->y);

	if (this->x == 96)
	{
		cout << " " << char(BOTTOMHALF) << "  " << char(BOTTOMHALF);
		Go(this->x, this->y + 1);
		cout << char(TOPHALF) << " " << char(BLOCK) << char(BLOCK) << " ";
		Go(1, this->y);
		cout <<" ";
		Go(1, this->y + 1);
		cout << char(TOPHALF);
	}
	else if (this->x == 97)
	{
		cout << " " << char(BOTTOMHALF) << "  ";
		Go(this->x, this->y + 1);
		cout << char(TOPHALF) << " " << char(BLOCK) << char(BLOCK);
		Go(1, this->y);
		cout << char(BOTTOMHALF) << " ";
		Go(1, this->y + 1);
		cout << " " << char(TOPHALF);
	}
	else if (this->x == 98)
	{
		cout << " " << char(BOTTOMHALF) << " ";
		Go(this->x, this->y + 1);
		cout << char(TOPHALF) << " " << char(BLOCK);
		Go(1, this->y);
		cout << " " << char(BOTTOMHALF) << " ";
		Go(1, this->y + 1);
		cout << char(BLOCK) << " " << char(TOPHALF);
	}
	else if (this->x == 99)
	{
		cout << " " << char(BOTTOMHALF);
		Go(this->x, this->y + 1);
		cout << char(TOPHALF) << " ";
		Go(1, this->y);
		cout << "  " << char(BOTTOMHALF) << " ";
		Go(1, this->y + 1);
		cout << char(BLOCK) << char(BLOCK) << " " << char(TOPHALF);
	}
	else if (this->x == 100)
	{
		cout << " ";
		Go(this->x, this->y + 1);
		cout << char(TOPHALF);
		Go(1, this->y);
		cout << char(BOTTOMHALF) << "  " << char(BOTTOMHALF) << " ";
		Go(1, this->y + 1);
		cout << " " << char(BLOCK) << char(BLOCK) << " " << char(TOPHALF);
	}
	else
	{
		cout << " " << char(BOTTOMHALF) << "  " << char(BOTTOMHALF) << " ";
		Go(x, y + 1);
		cout << char(TOPHALF) << " " << char(BLOCK) << char(BLOCK) << " " << char(TOPHALF);
	}
}

void Snake::Appear()
{
	Go(this->x, this->y);

	if (this->x == 96)
	{
		cout << " " << char(BOTTOMHALF) << char(BOTTOMHALF) << "  ";
		Go(this->x, this->y + 1);
		cout << char(TOPHALF) << "  " << char(TOPHALF) << char(TOPHALF);
		Go(1, this->y);
		cout << char(BOTTOMHALF);
		Go(1, this->y + 1);
		cout << " ";
	}
	else if (this->x == 97)
	{
		cout << " " << char(BOTTOMHALF) << char(BOTTOMHALF) << " ";
		Go(this->x, this->y + 1);
		cout << char(TOPHALF) << "  " << char(TOPHALF);
		Go(1, this->y);
		cout << " " << char(BOTTOMHALF);
		Go(1, this->y + 1);
		cout << char(TOPHALF) << " ";
	}
	else if (this->x == 98)
	{
		cout << " " << char(BOTTOMHALF) << char(BOTTOMHALF);
		Go(this->x, this->y + 1);
		cout << char(TOPHALF) << "  ";
		Go(1, this->y);
		cout << "  " << char(BOTTOMHALF);
		Go(1, this->y + 1);
		cout << char(TOPHALF) << char(TOPHALF) << " ";
	}
	else if (this->x == 99)
	{
		cout << " " << char(BOTTOMHALF);
		Go(this->x, this->y + 1);
		cout << char(TOPHALF) << " ";
		Go(1, this->y);
		cout << char(BOTTOMHALF) << "  " << char(BOTTOMHALF);
		Go(1, this->y + 1);
		cout << " " << char(TOPHALF) << char(TOPHALF) << " ";
	}
	else if (this->x == 100)
	{
		cout << " ";
		Go(this->x, this->y + 1);
		cout << char(TOPHALF);
		Go(1, this->y);
		cout << char(BOTTOMHALF) << char(BOTTOMHALF) << "  " << char(BOTTOMHALF);
		Go(1, this->y + 1);
		cout << "  " << char(TOPHALF) << char(TOPHALF) << " ";
	}
	else
	{
		cout << " " << char(BOTTOMHALF) << char(BOTTOMHALF) << "  " << char(BOTTOMHALF);
		Go(x, y + 1);
		cout << char(TOPHALF) << "  " << char(TOPHALF) << char(TOPHALF) << " ";
	}
}
Timer::Timer()
{
	this->x = 98;
	this->status = false;
	this->chance = 100;
}
void Timer::Targer(int target)
{
	this->y = target;
	this->status = true;
}
void Timer::Disappear()
{
	Go(this->x, this->y - 1);
	SetTextAttribute(DARKGRAY);
	cout << char(BOTTOMHALF);

	Go(this->x + 1, this->y - 1);
	SetTextAttribute(GREEN);
	cout << char(BOTTOMHALF);

	SetTextAttribute(LIGHTGREEN);
	Go(this->x - 1, this->y);
	cout << "    ";
}
void Timer::Appear()
{
	Go(this->x, this->y - 1);
	SetTextAttribute(RED);
	cout << char(BOTTOMHALF);

	Go(this->x + 1, this->y - 1);
	SetTextAttribute(DARKGRAY);
	cout << char(BOTTOMHALF);

	SetTextAttribute(LIGHTGREEN);
	Go(this->x - 1, this->y);
	cout << "<0" << this->time << ">";
}
bool Timer::Update()
{
	this->time = this->countdown / 20;
	if (this->countdown == 0)
	{
		this->status = false;
		this->chance = 100;
		this->Disappear();
	}
	return this->status;
}
void Timer::SetUp(bool status, int countdown)
{
	this->status = status;
	this->countdown = countdown;
	this->time = countdown / 20;
}
bool Timer::Status()
{
	return this->status;
}
bool Timer::CountDown()
{
	this->countdown--;
	if (this->countdown % 20 == 0)
		return true;
	return false;
}
int Timer::Chance()
{
	return ++this->chance;
}