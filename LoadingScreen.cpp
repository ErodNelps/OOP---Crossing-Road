void LoadingScreeen() {
	int x = 35;
	int count = x;
	int y = 12;
	int width = 50;
	gotoxy(x, y - 2);
	setTextAttribute(LIGHTGREEN);
	for (int i = 1; i <= 50; i++)
	{
		drawborder(x, y, 1, width, LIGHTGREEN, " ");
		gotoxy(x, y - 2);
		cout << "Loading...";
		gotoxy(x, y);
		for (int j = 1; j <= i; j++)
		{
			cout << char(219);
		}
		gotoxy(x + 11, y - 2);
		cout << 2 * i << "%";
		gotoxy(x, y + 2);
		cout << "                                        ";
		gotoxy(x, y + 2);
		if (i > 1 && i < 20)
			cout << "\tCreating Temporary files";
		else if (i > 20 && i < 30)
			cout << "\tAccessing Main Memory";
		else if (i > 40 && i < 48)
			cout << "\tHacking System";
		else cout << "\tCompleted";
		this_thread::sleep_for(chrono::milliseconds(70));
	}
	this_thread::sleep_for(chrono::milliseconds(700));
}

void ClearScreen() {
    COORD topLeft  = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(console, topLeft);
}
