#include "LongNumber.h"

void LongNumber::InsertBegin(LongNumber& num, int value)
{
	DequeNode* temp = new DequeNode;
	temp->data = value;
	temp->next = num.first;
	temp->prev = nullptr;

	if (num.first == nullptr) num.last = temp;
	else num.first->prev = temp;

	num.first = temp;
}

void LongNumber::InsertEnd(LongNumber& num, int value)
{
	DequeNode* temp = new DequeNode;
	temp->data = value;
	temp->next = nullptr;
	temp->prev = num.last;

	if (num.last == nullptr) num.first = temp;
	else num.last->next = temp;

	num.last = temp;
}

int LongNumber::getLength()
{
	int cnt = 0;

	while (this->first != nullptr)
	{
		cnt++;
		this->first = this->first->next;
	}

	return cnt;
}

bool LongNumber::operator==(LongNumber& other)
{
	if (this->isNegative != other.isNegative) return false;
	if (this->getLength() != other.getLength()) return false;

	DequeNode* current1 = this->first;
	DequeNode* current2 = other.first;

	while (current1 != nullptr) 
	{
		if (current1->data != current2->data) return false;
		current1 = current1->next;
		current2 = current2->next;
	}
	return true;
}

bool LongNumber::operator!=(LongNumber& other)
{
	return !(*this == other);
}

bool LongNumber::operator>(LongNumber& other)
{
	if (this->isNegative && !other.isNegative) return false; // num1 �������������, num2 �������������
	if (!this->isNegative && other.isNegative) return true; // num1 �������������, num2 �������������

	if (this->getLength() > other.getLength()) return !this->isNegative; // ������� � �������������
	if (this->getLength() < other.getLength()) return this->isNegative; // ������� � �������������

	DequeNode* current1 = this->first;
	DequeNode* current2 = other.first;
	while (current1 != nullptr) 
	{
		if (current1->data > current2->data) return !this->isNegative; // num1 ������
		if (current1->data < current2->data) return this->isNegative; // num2 ������
		current1 = current1->next;
		current2 = current2->next;
	}
	return false; // ��� �����
}

bool LongNumber::operator<(LongNumber& other)
{
	return !(*this >= other);
}

bool LongNumber::operator<=(LongNumber& other)
{
	return (*this < other) || (*this == other);
}

bool LongNumber::operator>=(LongNumber& other)
{
	return (*this > other) || (*this == other);
}

LongNumber LongNumber::operator+(const LongNumber& other) const
{
	LongNumber result;
	result.first = result.last = nullptr;

	// ���� ��� ����� �������������
	if (this->isNegative && other.isNegative) 
	{
		result.isNegative = true;
		// �������� �������
		// ...
	}
	// ���� ���� ����� �������������
	else if (this->isNegative || other.isNegative) 
	{
		// ��������� �������� �������
		// ...
	}
	// ���� ��� ����� �������������
	else 
	{
		int carry = 0;
		DequeNode* current1 = this->last;
		DequeNode* current2 = other.last;

		while (current1 != nullptr || current2 != nullptr || carry != 0) 
		{
			int sum = carry;
			if (current1 != nullptr) 
			{
				sum += current1->data;
				current1 = current1->prev;
			}
			if (current2 != nullptr) 
			{
				sum += current2->data;
				current2 = current2->prev;
			}
			InsertBegin(result, sum % 10); // ��������� ����� � ������
			carry = sum / 10; // �������
		}
	}

	RemoveLeadingZeros(result);
	return result;
}

LongNumber LongNumber::operator-(const LongNumber& other) const
{
	return LongNumber();
}

LongNumber LongNumber::operator*(const LongNumber& other) const
{
	return LongNumber();
}

LongNumber LongNumber::operator/(const LongNumber& other) const
{
	return LongNumber();
}
