#include "Header.h"

vector<Coordinate> Character::Space()
{
	vector<Coordinate> space;
	for (unsigned i = 0; i < this->space.size(); i++)
	{
		for (int j = 0; j < this->space[i]; j++)
		{
			Coordinate sub(this->x + j, this->y + i);
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
NPC::NPC(int x, int y, int distance, int max)
{
	this->x = x;
	this->y = y;
	this->distance = distance;
	this->monitor = this->distance;
	this->max = max;
	this->speed = this->max;
}
void NPC::Move()
{
	switch (this->Distance())
	{
	case TRUE:
	{
		this->x += 1;
		break;
	}
	case FALSE:
	{
		this->x -= this->distance - 1;
		break;
	}
	}
}
bool NPC::Distance()
{
	this->monitor--;
	if (this->monitor == 0)
	{
		this->monitor = this->distance;
		return false;
	}

	return true;
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

void Character::Disappear()
{
	Go(this->x, this->y);

	cout << "      ";

	Go(this->x, this->y + 1);

	cout << "      ";
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

	cout << " " << char(BOTTOMHALF) << "  " << char(BOTTOMHALF) << " ";

	Go(this->x, this->y + 1);

	cout << char(TOPHALF) << " " << char(BLOCK) << char(BLOCK) << " " << char(TOPHALF);

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

	cout << char(BOTTOMHALF) << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BOTTOMHALF);

	Go(this->x, this->y + 1);

	cout << " " << "O" << "  " << "O" << " ";
}

void Truck::Appear()
{
	Go(this->x, this->y);

	cout << "  " << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BLOCK);

	Go(x, y + 1);

	cout << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BLOCK) << char(BLOCK);
}

void Bird::Appear()
{
	Go(this->x, this->y);

	cout << " " << char(BOTTOMHALF) << "  " << char(BOTTOMHALF) << " ";

	Go(x, y + 1);

	cout << char(TOPHALF) << " " << char(BLOCK) << char(BLOCK) << " " << char(TOPHALF);
}

void Snake::Appear()
{
	Go(this->x, this->y);

	cout << " " << char(BOTTOMHALF)<< char(BOTTOMHALF) << "  " << char(BOTTOMHALF);

	Go(x, y + 1);

	cout << char(TOPHALF) << "  " << char(TOPHALF) << char(TOPHALF) << " ";
}
