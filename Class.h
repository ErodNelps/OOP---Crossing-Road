#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <thread>
#include <conio.h>


using namespace std;

class CPEOPLE {
	int mX, mY;
	bool mState; //Trạng thái sống chết
public:
	CPEOPLE();
	void Up(int);
	void Left(int);
	void Right(int);
	void Down(int);
	bool isImpact(const CVEHICLE*&);
	bool isImpact(const CANIMAL*&);
	bool isFinish();
	bool isDead();
};

class CVEHICLE {
	int mX, mY;
public:
	virtual void Move(int, int);
	//…
};

class CTRUCK : public CVEHICLE {
public:
	//…
};

class CCAR : public CVEHICLE {
public:
	//…
};

class CANIMAL {
	int mX, mY;
public:
	virtual void Move(int, int);
	virtual void Tell();
};

class CDINAUSOR : public CANIMAL {
public:
	//…
};

class CBIRD : public CANIMAL {
public:
	//…
};

class CGAME {
	CTRUCK* axt;
	CCAR* axh;
	CDINAUSOR* akl;
	CBIRD* ac;
	CPEOPLE cn;
public:
	CGAME(); //Chuẩn bị dữ liệu cho tất cả các đối tượng
	void drawGame(); //Thực hiện vẽ trò chơi ra màn hình sau khi có dữ liệu
	~CGAME(); // Hủy tài nguyên đã cấp phát
	CPEOPLE getPeople();//Lấy thông tin người
	CVEHICLE* getVehicle();//Lấy danh sách các xe
	CANIMAL* getAnimal(); //Lấy danh sách các thú
	void resetGame(); // Thực hiện thiết lập lại toàn bộ dữ liệu như lúc đầu
	void exitGame(HANDLE); // Thực hiện thoát Thread
	void startGame(); // Thực hiện bắt đầu vào trò chơi
	//void loadGame(istream& is); // Thực hiện tải lại trò chơi đã lưu
	//void saveGame(istream& is); // Thực hiện lưu lại dữ liệu trò chơi
	void pauseGame(HANDLE); // Tạm dừng Thread
	void resumeGame(HANDLE); //Quay lai Thread
	void updatePosPeople(char); //Thực hiện điều khiển di chuyển của CPEOPLE
	void updatePosVehicle(); //Thực hiện cho CTRUCK & CCAR di chuyển
	void updatePosAnimal();//Thực hiện cho CDINAUSOR & CBIRD di chuyển
};