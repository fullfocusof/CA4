#include "LongNumber.h"

void LongNumber::Print()
{
	if (isNegative) cout << "-";
	for (int i = num.size() - 1; i >= 0; i--)
	{
		cout << num[i];
	}
}

void LongNumber::Clear()
{
	isNegative = false;
	num.clear();
}

void LongNumber::InsertBegin(int value)
{
	num.insert(num.begin(), value);
}

void LongNumber::InsertEnd(int value)
{
	num.push_back(value);
}

int LongNumber::getLength()
{
	return num.size();
}

bool LongNumber::isEmpty()
{
	return num.empty();
}

bool LongNumber::operator==(LongNumber& other)
{
	return (isNegative == other.isNegative) && (num == other.num);
}

bool LongNumber::operator!=(LongNumber& other)
{
	return !(*this == other);
}

bool LongNumber::operator<(LongNumber& other)
{
	if (isNegative != other.isNegative) return isNegative;
	if (num.size() != other.num.size()) return (isNegative) ? (num.size() > other.num.size()) : (num.size() < other.num.size());
	for (int i = num.size() - 1, j = other.num.size() - 1; i >= 0, j >= 0; i--, j--)
	{
		if (num[i] != other.num[i]) return (isNegative) ? (num[i] > other.num[i]) : (num[i] < other.num[i]);
	}
	return false;
}

bool LongNumber::operator>(LongNumber& other)
{
	return other < *this;
}

bool LongNumber::operator<=(LongNumber& other)
{
	return !(*this > other);
}

bool LongNumber::operator>=(LongNumber& other)
{
	return !(*this < other);
}

LongNumber LongNumber::operator-() const
{
	LongNumber result = *this;
	result.isNegative = !result.isNegative;
	return result;
}

LongNumber LongNumber::operator+(const LongNumber& other) const
{
	if (isNegative == other.isNegative) 
	{
		LongNumber result;
		int carry = 0;
		int maxSize = max(num.size(), other.num.size());
		for (int i = 0; i < maxSize || carry; i++) 
		{
			int sum = carry;
			if (i < num.size()) sum += num[i];
			if (i < other.num.size()) sum += other.num[i];
			result.InsertEnd(sum % 10);
			carry = sum / 10;
		}
		result.isNegative = isNegative;
		return result;
	}
	else return (*this - (-other));
}

LongNumber LongNumber::operator-(const LongNumber& other) const
{
	if (isNegative != other.isNegative) return *this + (-other);

	LongNumber result;
	bool resultNegative = false;

	LongNumber left = *this; left.isNegative = false;
	LongNumber right = other; right.isNegative = false;
	if (left <= right) resultNegative = !isNegative;
	else resultNegative = isNegative;

	LongNumber minuend = left < right ? right : left;
	LongNumber subtrahend = left < right ? left : right;

	int borrow = 0;
	int maxSize = minuend.getLength();
	for (int i = 0; i < maxSize; ++i) 
	{
		int minuendDigit = minuend.num[i];
		int subtrahendDigit = (i < subtrahend.getLength()) ? subtrahend.num[i] : 0;
		int diff = minuendDigit - subtrahendDigit - borrow;
		if (diff < 0) 
		{
			diff += 10;
			borrow = 1;
		}
		else borrow = 0;
		result.InsertEnd(diff);
	}

	while (result.num.size() > 1 && result.num.back() == 0) result.num.pop_back();
	result.isNegative = resultNegative;
	return result;
}

LongNumber LongNumber::operator*(const LongNumber& other) const
{
	LongNumber result;
	result.num.resize(num.size() + other.num.size(), 0);

	for (int i = 0; i < num.size(); ++i) 
	{
		for (int j = 0; j < other.num.size(); ++j) 
		{
			result.num[i + j] += num[i] * other.num[j];
			if (result.num[i + j] >= 10) 
			{
				result.num[i + j + 1] += result.num[i + j] / 10;
				result.num[i + j] %= 10;
			}
		}
	}

	while (result.num.size() > 1 && result.num.back() == 0) result.num.pop_back();
	result.isNegative = isNegative != other.isNegative && result.num.back() != 0;
	return result;
}

pair<LongNumber, LongNumber> LongNumber::divide(LongNumber& other)
{
	if (other.num.back() == 0 && other.num.size() == 1) throw exception("Деление на ноль");

	LongNumber result;
	result.isNegative = false;

	LongNumber left = *this; left.isNegative = false;
	LongNumber right = other; right.isNegative = false;

	LongNumber zero;
	zero.isNegative = false;
	zero.InsertEnd(0);

	if (left < right)
	{
		result.InsertEnd(0);
		return make_pair(result, *this);
	}
	else if (left == right)
	{
		result.InsertEnd(1);
		return make_pair(result, zero);
	}
	else
	{
		LongNumber inc;
		inc.isNegative = false;
		inc.InsertEnd(1);

		result.InsertEnd(0);
		while (left >= right)
		{
			left = left - right;
			result = result + inc;
		}

		LongNumber remainder = left;
		remainder.isNegative = false;
		if (remainder.num.front() != 0 && remainder.num.size() >= 1)
		{
			if ((isNegative && other.isNegative) || isNegative)
			{
				left = *this; left.isNegative = false;
				result = result + inc;
				remainder = result * right - left;
			}
		}

		result.isNegative = isNegative != other.isNegative && result.num.back() != 0;
		return make_pair(result, remainder);
	}
}

LongNumber LongNumber::getPow(long long pow)
{
	if (pow < 0) throw exception("Степень не может быть отрицательной");

	LongNumber result;
	result.InsertEnd(1);

	LongNumber base = *this;

	while (pow != 0)
	{
		if ((pow & 1) != 0) result = result * base;
		base = base * base;
		pow >>= 1;
	}

	return result;
}