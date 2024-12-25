#pragma once
#include <iostream>
#include <sstream>

#include <cmath>
#include <numeric>

#include <Windows.h>
#include <conio.h>

#include <string>
#include <vector>

#include "LongNumber.h"

using namespace std;

struct DequeNode
{
	int data;
	DequeNode* next,* prev;
};

class DequeInterraction
{
	LongNumber input;

public:

	void setInput(LongNumber& value);
	LongNumber getInput();

	void printLong(LongNumber& num);

	LongNumber Init();
	LongNumber Sum(LongNumber num1, LongNumber num2);
	LongNumber DecAbs(LongNumber num1, LongNumber num2);
	LongNumber Decision(LongNumber num1, LongNumber num2);
	LongNumber MultiplySingle(LongNumber& num, int value);
	LongNumber MultiplyLong(LongNumber& num1, LongNumber& num2);
	void Divide(LongNumber& dividend, LongNumber& divisor, LongNumber& quotient, LongNumber& remainder);
};

void printQuit();