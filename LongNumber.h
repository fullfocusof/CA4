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

class LongNumber
{
	vector<int> num;

public:

	bool isNegative;

	void Print();
	void Clear();

	void InsertBegin(int value);
	void InsertEnd(int value);
	int getLength();

	bool isEmpty();
	bool operator==(LongNumber& other);
	bool operator!=(LongNumber& other);
	bool operator<(LongNumber& other);
	bool operator>(LongNumber& other);
	bool operator<=(LongNumber& other);
	bool operator>=(LongNumber& other);

	LongNumber operator-() const;
	LongNumber operator+(const LongNumber& other) const;
	LongNumber operator-(const LongNumber& other) const;
	LongNumber operator*(const LongNumber& other) const;
	pair<LongNumber, LongNumber> divide(LongNumber& first, LongNumber& other);
	LongNumber getPow(long long pow);
	LongNumber gcd(LongNumber& other);
};