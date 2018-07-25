void LoadingScreeen() {
	int x = 35;
	int count = x;
	int y = 12;
	int width = 40;
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
	/*for (int i = 1; i <= 50; i++)
	{
		system("cls");
		cout << "\n\n\n\n\t\t\t\t   Loading " << '\n' << '\t' << '\t';
		for (int j = 1; j <= i; j++)
			cout << char(219);
		cout << "\n\n\t " << 2 * i << "%";
		if (i > 1 && i < 20)
			cout << "\n\n\tCreating Temporary files";
		else if (i > 20 && i<40)
			cout << "\n\n\tAccessing Main Memory";
		else if (i >40 && i<48)
			cout << "\n\n\tAccessing Cache";
		else cout << "\n\n\tComplete. Press Enter to Continue ";
		this_thread::sleep_for(chrono::milliseconds(100));
	}
	_getch();*/
}
