#pragma once
#include <iostream>
#include <sstream>

#include <cmath>
#include <numeric>

#include <Windows.h>
#include <conio.h>

#include <string>
#include <vector>

using namespace std;

struct DequeNode
{
	int data;
	DequeNode* next,* prev;
};

struct LongNumber
{
	DequeNode* first;
	DequeNode* last;
	bool isNegative;
};

class DequeInterraction
{
	LongNumber input;

public:

	void setInput(LongNumber& value);
	LongNumber getInput();

	void printLong(LongNumber& num);

	void InsertBegin(LongNumber& num, int value);
	void InsertEnd(LongNumber& num, int value);
	LongNumber Init();
	int getSize(LongNumber& num);

	int Compare(LongNumber& num1, LongNumber& num2); // 0 - "="      1 - num1>num2      -1 - num1<num2
	int CompareAbs(LongNumber num1, LongNumber num2);

	LongNumber Sum(LongNumber num1, LongNumber num2);
	LongNumber DecAbs(LongNumber num1, LongNumber num2);
	LongNumber Decision(LongNumber num1, LongNumber num2);
	LongNumber MultiplySingle(LongNumber& num, int value);
	LongNumber MultiplyLong(LongNumber& num1, LongNumber& num2);
};

void printQuit();