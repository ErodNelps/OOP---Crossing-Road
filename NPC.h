#include "Character.h"

class NPC : public Character
{
protected:
	bool move;
	int speed;
	int max;
	bool go;
public:
	NPC(int x, int y, int max, bool go);
	void virtual Move();
	void virtual Appear() = 0;
	bool virtual Speed();
	void virtual SetSpeed(int speed);
	void virtual Update(int max);
};

class NPMC : public NPC
{
public:
	NPMC(int x, int y, int max, bool go) : NPC(x, y, max, go) {};
	void virtual Appear() = 0;
};

class NPLC : public NPC
{
public:
	NPLC(int x, int y, int max, bool go) : NPC(x, y, max, go) {};
	void virtual Appear() = 0;
};

class Car : public NPMC
{
public:
	Car(int x, int y, int max, bool go) : NPMC(x, y, max, go) {};
	void Appear();
};

class Truck : public NPMC
{
public:
	Truck(int x, int y, int max, bool go) : NPMC(x, y, max, go) {};
	void Appear();
	void Disappear();
};

class Snake : public NPLC
{
public:
	Snake(int x, int y, int max, bool go) : NPLC(x, y, max, go) {};
	void Appear();
};

class Bird : public NPLC
{
public:
	Bird(int x, int y, int max, bool go) : NPLC(x, y, max, go) {};
	void Appear();
};
