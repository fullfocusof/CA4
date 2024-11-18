#include "DequeInterraction.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_BACKSPACE 8

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void GoToXY(short x, short y)
{
	SetConsoleCursorPosition(hStdOut, { x, y });
}

void ConsoleCursorVisible(bool show, short size)
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show;
	structCursorInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

int main()
{
	setlocale(LC_ALL, "ru");
	SetConsoleTitle(L"Размещения и сочетания");
	ConsoleCursorVisible(false, 100);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);

	DequeInterraction test;

	int active_menu = 0;
	int keyInput;
	bool exitProg = false;

	while (!exitProg)
	{
		int x = 40, y = 12;
		GoToXY(x, y);

		vector<string> menu =
		{
			"Ввод длинного числа",
			"Вывод данных",
			"Сравнение двух длинных чисел",
			"Сложение двух длинных чисел",
			"Вычитание двух длинных чисел",
			"Умножение длинного числа",
			"Умножение двух длинных чисел",
			"Деление с остатком двух длинных чисел",
			"Возведение в степень длинного числа",
			"Выход"
		};

		for (int i = 0; i < menu.size(); i++)
		{
			if (i == active_menu)
			{
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			}
			else
			{
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			}

			GoToXY(x, y++);
			cout << menu[i] << endl;
		}

		keyInput = _getch();
		switch (keyInput)
		{
			case KEY_ESC:
				exit(0);

			case KEY_UP:
			{
				if (active_menu > 0)
				{
					active_menu--;
				}
			}
			break;

			case KEY_DOWN:
			{
				if (active_menu < menu.size() - 1)
				{
					active_menu++;
				}
			}
			break;

			case KEY_ENTER:
			{
				switch (active_menu)
				{
					case 0:
					{
						system("cls");

						LongNumber mainInput = test.Init();
						test.setInput(mainInput);
						cout << endl << "Успешный ввод";
						
						printQuit();
					}
					break;

					case 1:
					{
						system("cls");

						LongNumber mainInput = test.getInput();
						test.printLong(mainInput);

						printQuit();
					}
					break;

					case 2:
					{
						system("cls");

						LongNumber forCompare = test.Init();
						LongNumber mainInput = test.getInput();

						system("cls");
						test.printLong(mainInput);
						switch (test.Compare(mainInput, forCompare))
						{
							case -1:
							{
								cout << " < ";
								
							}
							break;

							case 1:
							{
								cout << " > ";
							}
							break;

							case 0:
							{
								cout << " = ";
							}
							break;

							default:
							{
								cerr << "Ошибка при сравнении";
							}
							break;
						}
						test.printLong(forCompare);
							
						printQuit();
					}
					break;

					case 3:
					{
						system("cls");

						LongNumber forSum = test.Init();
						LongNumber mainInput = test.getInput();
						LongNumber sum = test.Sum(mainInput, forSum);

						system("cls");
						test.printLong(mainInput); cout << " + "; test.printLong(forSum); cout << " = "; test.printLong(sum);
						
						printQuit();
					}
					break;

					case 4:
					{
						system("cls");

						LongNumber forDec = test.Init();
						LongNumber mainInput = test.getInput();
						LongNumber diff = test.Decision(mainInput, forDec);

						system("cls");
						test.printLong(mainInput); cout << " - "; test.printLong(forDec); cout << " = "; test.printLong(diff);

						printQuit();
					}
					break;

					case 5:
					{
						system("cls");

						int mp;
						cout << "Введите множитель: ";
						cin >> mp;
						LongNumber mainInput = test.getInput();
						LongNumber prod = test.MultiplySingle(mainInput, mp);

						system("cls");
						test.printLong(mainInput); cout << " * " << mp << " = "; test.printLong(prod);

						printQuit();
					}
					break;

					case 6:
					{
						system("cls");

						LongNumber forMp = test.Init();
						LongNumber mainInput = test.getInput();
						LongNumber prod = test.MultiplyLong(mainInput, forMp);

						system("cls");
						test.printLong(mainInput); cout << " * "; test.printLong(forMp); cout << " = "; test.printLong(prod);

						printQuit();
					}
					break;

					case 7:
					{
						system("cls");



						printQuit();
					}
					break;

					case 8:
					{
						system("cls");



						printQuit();
					}
					break;

					case 9:
					{
						exitProg = true;
					}
					break;
				}
			}
			break;
		}
	}
}