#include "DequeInterraction.h"


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
		else
		{
			answ = _getch();
		}
	}

	system("cls");
}

void DequeInterraction::setInput(LongNumber& value)
{
	input = value;
}

LongNumber DequeInterraction::getInput()
{
	return input;
}

void DequeInterraction::printLong(LongNumber& num)
{
	if (num.isNegative && num.last->data != 0) cout << "-";

	DequeNode* temp = num.last;
	while (temp != nullptr)
	{
		cout << temp->data;
		temp = temp->prev;
	}
}

LongNumber DequeInterraction::Init()
{
	string ex;
	cout << "Введите число" << endl;
	cin >> ex;

	LongNumber result;
	result.first = nullptr;
	result.last = nullptr;

	if (ex[0] == '-')
	{
		result.isNegative = true;
		ex = ex.substr(1);
	}
	else result.isNegative = false;

	ex.erase(0, ex.find_first_not_of('0'));
	if (ex.empty()) ex = "0";

	for (int i = 0; i < ex.size(); i++)
	{
		if (isdigit(ex[i])) LongNumber::InsertBegin(result, int(ex[i] - '0')); result.InsertBegin
		else break;
	}

	return result;
}

int DequeInterraction::Compare(LongNumber& num1, LongNumber& num2) // 0 - "="      1 - num1>num2      -1 - num1<num2
{
	int result = 0;

	if (num1.isNegative && !num2.isNegative) return -1;
	else if (!num1.isNegative && num2.isNegative) return 1;
	else
	{
		DequeNode* curNum1 = num1.first;
		DequeNode* curNum2 = num2.first;

		if (!num1.isNegative && !num2.isNegative)
		{
			while (curNum1 != nullptr && curNum2 != nullptr)
			{
				if (curNum1->data > curNum2->data) result = 1;
				else if (curNum1->data < curNum2->data) result = -1;
				curNum1 = curNum1->next;
				curNum2 = curNum2->next;
			}

			if (curNum1 != nullptr) result = 1;
			else if (curNum2 != nullptr) result = -1;
		}
		else if (num1.isNegative && num2.isNegative)
		{
			while (curNum1 != nullptr && curNum2 != nullptr)
			{
				if (curNum1->data > curNum2->data) result = -1;
				else if (curNum1->data < curNum2->data) result = 1;
				curNum1 = curNum1->next;
				curNum2 = curNum2->next;
			}

			if (curNum1 != nullptr) result = -1;
			else if (curNum2 != nullptr) result = 1;
		}
	}

	return result;
}

int DequeInterraction::CompareAbs(LongNumber num1, LongNumber num2)
{
	num1.isNegative = false;
	num2.isNegative = false;

	int result = 0;
	DequeNode* curNum1 = num1.first;
	DequeNode* curNum2 = num2.first;

	while (curNum1 != nullptr && curNum2 != nullptr)
	{
		if (curNum1->data > curNum2->data) result = 1;
		else if (curNum1->data < curNum2->data) result = -1;
		curNum1 = curNum1->next;
		curNum2 = curNum2->next;
	}

	if (curNum1 != nullptr) result = 1;
	else if (curNum2 != nullptr) result = -1;

	return result;
}

LongNumber DequeInterraction::Sum(LongNumber num1, LongNumber num2)
{
	LongNumber result;
	result.first = nullptr;
	result.last = nullptr;
	result.isNegative = false;

	if (num1.isNegative && num2.isNegative)
	{
		result.isNegative = true;
		num1.isNegative = false;
		num2.isNegative = false;
	}
	else if (num1.isNegative || num2.isNegative) return DecAbs(num1, num2);
	
	DequeNode* tempnum1 = num1.first, * tempnum2 = num2.first;

	int trans = 0, tempVal1, tempVal2;

	while (tempnum1 != nullptr || tempnum2 != nullptr || trans != 0)
	{
		if (tempnum1 != nullptr)
		{
			tempVal1 = tempnum1->data;
			tempnum1 = tempnum1->next;
		}
		else tempVal1 = 0;

		if (tempnum2 != nullptr)
		{
			tempVal2 = tempnum2->data;
			tempnum2 = tempnum2->next;
		}
		else tempVal2 = 0;

		InsertEnd(result, (tempVal1 + tempVal2 + trans) % 10);
		trans = (tempVal1 + tempVal2 + trans) / 10;
	}

	return result;
}

LongNumber DequeInterraction::DecAbs(LongNumber num1, LongNumber num2)
{
	LongNumber result;
	result.first = nullptr;
	result.last = nullptr;
	result.isNegative = false;

	num1.isNegative = false;
	num2.isNegative = false;

	/*int compareResult = Compare(num1, num2);
	if (compareResult == 0)
	{
		result.isNegative = false;
		InsertEnd(result, 0);
		return result;
	}
	else if (compareResult == -1)
	{
		result.isNegative = true;
		swap(num1, num2);
	}*/

	DequeNode* curNum1 = num1.first;
	DequeNode* curNum2 = num2.first;
	int borrow = 0;

	while (curNum1 != nullptr || curNum2 != nullptr)
	{
		int curResult = borrow + (curNum1 != nullptr ? curNum1->data : 0) - (curNum2 != nullptr ? curNum2->data : 0);

		if (curResult < 0)
		{
			curResult += 10;
			borrow = -1;
		}
		else borrow = 0;

		InsertEnd(result, curResult);
		curNum1 = curNum1 != nullptr ? curNum1->next : nullptr;
		curNum2 = curNum2 != nullptr ? curNum2->next : nullptr;
	}

	while (result.last->prev != nullptr && result.last->data == 0)
	{
		DequeNode* temp = result.last;
		result.last = result.last->prev;
		result.last->next = nullptr;
		delete temp;
	}

	return result; // 1 + 2 -      1 - 2 +    1 - 2 -
}

LongNumber DequeInterraction::Decision(LongNumber num1, LongNumber num2)
{
	LongNumber result;
	result.first = nullptr;
	result.last = nullptr;
	result.isNegative = false;

	if (num1.isNegative && num2.isNegative)
	{
		result = DecAbs(num1, num2);
		result.isNegative = !result.isNegative;
		return result;
	}

	int compareResult = Compare(num1, num2);
	if (compareResult == 0)
	{
		result.isNegative = false;
		InsertEnd(result, 0);
		return result;
	}
	else if (compareResult == -1) 
	{
		result.isNegative = true;
		swap(num1, num2);
	}

	DequeNode* curNum1 = num1.first;
	DequeNode* curNum2 = num2.first;
	int borrow = 0;

	while (curNum1 != nullptr || curNum2 != nullptr)
	{
		int curResult = borrow + (curNum1 != nullptr ? curNum1->data : 0) - (curNum2 != nullptr ? curNum2->data : 0);

		if (curResult < 0)
		{
			curResult += 10;
			borrow = -1;
		}
		else borrow = 0;

		InsertEnd(result, curResult);
		curNum1 = curNum1 != nullptr ? curNum1->next : nullptr;
		curNum2 = curNum2 != nullptr ? curNum2->next : nullptr;
	}

	while (result.last->prev != nullptr && result.last->data == 0)
	{
		DequeNode* temp = result.last;
		result.last = result.last->prev;
		result.last->next = nullptr;
		delete temp;
	}

	return result;
}

LongNumber DequeInterraction::MultiplySingle(LongNumber& num, int value)
{
	LongNumber result;
	result.first = nullptr;
	result.last = nullptr;

	if (value == 0)
	{
		InsertEnd(result, 0);
		return result;
	}

	DequeNode* temp = num.first;
	int trans = 0, tempNum;

	while (temp != nullptr || trans != 0)
	{
		if (temp != nullptr)
		{
			tempNum = temp->data;
			temp = temp->next;
		}
		else
		{
			tempNum = 0;
		}

		InsertEnd(result, (tempNum * value + trans) % 10);
		trans = (trans + tempNum * value) / 10;
	}

	return result;
}

LongNumber DequeInterraction::MultiplyLong(LongNumber& num1, LongNumber& num2)
{
	LongNumber result;
	result.first = nullptr;
	result.last = nullptr;	

	DequeNode* tempnum2 = num2.first;
	int digitCount = 0;

	while (tempnum2 != nullptr)
	{
		LongNumber tempResult = MultiplySingle(num1, tempnum2->data);
		for (int i = 0; i < digitCount; i++)
		{
			InsertBegin(tempResult, 0);
		}
		
		result = Sum(result, tempResult);
		digitCount++;
		tempnum2 = tempnum2->next;
	}

	result.isNegative = num1.isNegative != num2.isNegative;

	return result;
}

void DequeInterraction::Divide(LongNumber& dividend, LongNumber& divisor, LongNumber& quotient, LongNumber& remainder) 
{
	if (divisor.first == nullptr) throw invalid_argument("Деление на ноль");

	remainder = dividend;
	quotient.first = quotient.last = nullptr;
	while (remainder >= divisor)
	{
		remainder =  remainder - divisor;
		// Увеличиваем счетчик в частном
	}

	// Удаляем лишние нули из частного
	// Удаляем лишние нули из остатка
}