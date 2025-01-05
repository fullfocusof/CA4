#include "DequeInterraction.h"
#include "LongNumber.h"

void printQuit()
{
	cout << endl << endl << "Backspace - возврат в меню";

	int answ = _getch();
	bool press = false;

	while (!press)
	{
		if (answ == 8)
		{
			press = true;
			break;
		}
		else answ = _getch();
	}

	system("cls");
}

void DequeInterraction::setInput(LongNumber toSet)
{
	input = toSet;
}

LongNumber DequeInterraction::getInput()
{
	if (!input.isEmpty()) return input;
	else throw exception("Данные отсутствуют");
}

LongNumber DequeInterraction::Init()
{
	LongNumber result;

	string str;
	cout << "Введите длинное число: ";
	cin >> str;
	if (str[0] == '-') result.isNegative = true;
	for (int i = str.size() - 1; i >= 0; i--)
	{
		if (isdigit(str[i])) result.InsertEnd(str[i] - '0');
	}

	return result;
}