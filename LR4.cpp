#include "DequeInterraction.h"
#include "LongNumber.h"

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

						printQuit();
					}
					break;

					case 1:
					{
						system("cls");

						LongNumber mainInput = test.getInput();
						mainInput.Print();

						printQuit();
					}
					break;

					case 2:
					{
						system("cls");

						try
						{
							LongNumber forCompare = test.Init();
							LongNumber mainInput = test.getInput();
							if (mainInput > forCompare)
							{
								mainInput.Print(); cout << " > "; forCompare.Print();
							}
							else if (mainInput == forCompare)
							{
								mainInput.Print(); cout << " = "; forCompare.Print();
							}
							else if (mainInput < forCompare)
							{
								mainInput.Print(); cout << " < "; forCompare.Print();
							}
							else throw exception("Ошибка сравнения");

						}
						catch (const exception& ex)
						{
							cout << ex.what();
						}

						printQuit();
					}
					break;

					case 3:
					{
						system("cls");
						
						LongNumber forSum = test.Init();
						LongNumber mainInput = test.getInput();
						LongNumber sum = mainInput + forSum;
						system("cls");
						mainInput.Print(); cout << " + "; forSum.Print(); cout << " = "; sum.Print();

						printQuit();
					}
					break;

					case 4:
					{
						system("cls");

						LongNumber forDec = test.Init();
						LongNumber mainInput = test.getInput();
						LongNumber dec = mainInput - forDec;
						system("cls");
						mainInput.Print(); cout << " - "; forDec.Print(); cout << " = "; dec.Print();

						printQuit();
					}
					break;

					case 5:
					{
						system("cls");

						LongNumber forMp = test.Init();
						LongNumber mainInput = test.getInput();
						LongNumber mp = mainInput * forMp;
						system("cls");
						mainInput.Print(); cout << " * "; forMp.Print(); cout << " = "; mp.Print();

						printQuit();
					}
					break;

					case 6:
					{
						system("cls");

						try
						{
							LongNumber forDiv = test.Init();
							LongNumber mainInput = test.getInput();
							pair<LongNumber, LongNumber> divPair = mainInput.divide(forDiv);
							system("cls");
							mainInput.Print(); cout << " / "; forDiv.Print(); cout << " = "; divPair.first.Print(); cout << endl;
							cout << "Остаток: "; divPair.second.Print();
						}
						catch (const exception& ex)
						{
							cout << ex.what();
						}
						
						printQuit();
					}
					break;

					case 7:
					{
						system("cls");

						try
						{
							long long forPow;
							cout << "Введите степень: ";
							cin >> forPow;
							LongNumber mainInput = test.getInput();
							LongNumber powed = mainInput.getPow(forPow);
							system("cls");
							mainInput.Print(); cout << " ^ " << forPow << " = "; powed.Print();
						}
						catch (const exception& ex)
						{
							cout << ex.what();
						}
		
						printQuit();
					}
					break;

					case 8:
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