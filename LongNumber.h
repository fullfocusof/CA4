#pragma once
#include "DequeInterraction.h"

class LongNumber
{
public:
	DequeNode* first;
	DequeNode* last;
	bool isNegative;

	void InsertBegin(LongNumber& num, int value);
	void InsertEnd(LongNumber& num, int value);
	int getLength();

	bool operator==(LongNumber& other);
	bool operator!=(LongNumber& other);
	bool operator<(LongNumber& other);
	bool operator>(LongNumber& other);
	bool operator<=(LongNumber& other);
	bool operator>=(LongNumber& other);

	LongNumber operator+(const LongNumber& other) const;
	LongNumber operator-(const LongNumber& other) const;
	LongNumber operator*(const LongNumber& other) const;
	LongNumber operator/(const LongNumber& other) const;
};