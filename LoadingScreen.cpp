void LoadingScreeen() {
	int x = 35;
	int count = x;
	int y = 12;
	int width = 40;
	int p;
	gotoxy(x, y - 2);
	setTextAttribute(LIGHTGREEN);
	for (int i = 1; i <= 40; i++)
	{
		system("cls");
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
		if (i > 1 && i < 20)
			cout << "\tCreating Temporary files";
		else if (i > 20 && i < 30)
			cout << "\tAccessing Main Memory";
		else if (i > 30 && i < 38)
			cout << "\tHacking System";
		else cout << "\tCompleted";
		this_thread::sleep_for(chrono::milliseconds(70));
	}
}
